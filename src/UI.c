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
};

