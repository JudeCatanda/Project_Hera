#include "UI.h"

void create_cursor(cursor *cur) {
  float cursor_data[24] = {
     -0.1f, -0.1f, 0.0f, 0.0f,
      0.1f, -0.1f, 1.0f, .0f,
      0.1f,  0.1f,  1.0f, 1.0f,

     -0.1f, -0.1f, 0.0f, 0.0f,
     -0.1f,  0.1f, 0.0, 1.0f,
      0.1f,  0.1f, 1.0f, 1.0f
  };

  shader_create(&cur->vertex, "./assets/shaders/ui.shader.cursor.vert", GL_VERTEX_SHADER);
  shader_create(&cur->fragment, "./assets/shaders/ui.shader.cursor.frag", GL_FRAGMENT_SHADER);
  program_create(&cur->program, &cur->vertex, &cur->fragment);

  layout_create_and_bind(&cur->layouts);
  vrtxbuffer_create(&cur->mesh, sizeof(cursor_data), cursor_data, GL_STATIC_DRAW);

  layout_enable_and_set_vertex_attrib_pointer(0, 2, GL_FLOAT, sizeof(vec4), (void*)0);
  layout_enable_and_set_vertex_attrib_pointer(1, 2, GL_FLOAT, sizeof(vec4), (void*)(sizeof(vec2)));

  texture_create(&cur->cursor_texture, "./assets/ui/arrow.png", GL_RGBA, GL_RGBA);

  cur->mesh.unbind(&cur->mesh);
  layout_unbind(&cur->layouts);
}

void render_cursor(cursor *cur) {
  // plr->player_texture.Bind(&plr->player_texture);
  // plr->program.UseProgram(&plr->program);
  // layout_bind(&plr->player_layouts);
  // configure_projection(plr, plr->aspect_ratio);
  // glDrawArrays(GL_TRIANGLES, 0, 6);
  cur->cursor_texture.Bind(&cur->cursor_texture);
  cur->program.UseProgram(&cur->program);
  layout_bind(&cur->layouts);

  glm_ortho(-cur->aspect_ratio, cur->aspect_ratio, -1.0f, 1.0f, -1.0f, 1.0f, cur->projection); // works! but not changing camera pos

  glDrawArrays(GL_TRIANGLES, 0, 6);

  glUniformMatrix4fv(glGetUniformLocation(cur->program.handle, "projection"), 1, GL_FALSE, (float *)cur->projection);

  cur->cursor_uniform_position_location = glGetUniformLocation(cur->program.handle, "new_pos");
  glUniform2fv(cur->cursor_uniform_position_location, 1, (float*)cur->cursor_position);
}

void cursor_unbind(cursor* cur) {
  layout_unbind(&cur->layouts);
  cur->program.Unbind(&cur->program);
  cur->cursor_texture.Unbind(&cur->cursor_texture);
}

Character characters_to_render[128];

void load_font(const char* font_path) {
    // Initialize FreeType
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        fprintf(stderr, "Could not init FreeType Library\n");
        exit(1);
    }

    // Load font face
    FT_Face face;
    if (FT_New_Face(ft, font_path, 0, &face)) {
        fprintf(stderr, "Failed to load font\n");
        exit(1);
    }

    // Set font size
    FT_Set_Pixel_Sizes(face, 0, 48);

    // Disable byte-alignment restriction for textures
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Loop through first 128 ASCII characters
    for (unsigned char c = 0; c < 128; c++) {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            fprintf(stderr, "Failed to load Glyph\n");
            continue;
        }

        // Generate texture for glyph
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED, // We use RED channel for monochrome texture
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Store character information
        characters_to_render[c] = (Character){
            .textureID = texture,
            .width = face->glyph->bitmap.width,
            .height = face->glyph->bitmap.rows,
            .bearingX = face->glyph->bitmap_left,
            .bearingY = face->glyph->bitmap_top,
            .advance = face->glyph->advance.x
        };
    }

    // Clean up
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void render_text(const char* text, float x, float y, float scale, GLuint VAO, GLuint VBO, GLuint shader) {
    // Activate corresponding render state
    glUseProgram(shader);
    glUniform3f(glGetUniformLocation(shader, "textColor"), 0.0f, 0.0f, 0.0f); // Set text color (white)

    // Bind the VAO
    glBindVertexArray(VAO);

    // Iterate through all characters in the text string
    for (const char* c = text; *c; c++) {
        Character ch = characters_to_render[*c]; // Get the character info

        // Calculate the position and size for the character's quad
        float xpos = x + ch.bearingX * scale;
        float ypos = y - (ch.height - ch.bearingY) * scale;
        float w = ch.width * scale;
        float h = ch.height * scale;

        // Update the VBO for the character's quad vertices
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };

        // Bind texture for this character
        glBindTexture(GL_TEXTURE_2D, ch.textureID);

        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        // Render quad for the current character
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Advance to the next character's position
        x += (ch.advance >> 6) * scale; // Bitshift by 6 to get the value in pixels
    }

    // Unbind the VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
};
