#include "renderer.h"

static void INITIALIZE_VECTOR2(vec2* arr, int max_n, float default_x, float default_y) {
  for(int positions_in_arr = 0; positions_in_arr < max_n; positions_in_arr++) {
    arr[positions_in_arr][0] = default_x;
    arr[positions_in_arr][1] = default_y;
  }
};

void init_bricks(Renderer* rnd) {
  float TEXTURE_X = 0, TEXTURE_Y = 1;
  float TEXTURE_CELL_SIZE = 16;
  float IMAGE_SIZE = 32;

  float DEFAULT_QUAD_MESH[24] = {
    -0.2f, -0.2f,  TEXTURE_X * TEXTURE_CELL_SIZE / IMAGE_SIZE,        TEXTURE_Y * TEXTURE_CELL_SIZE / IMAGE_SIZE,
     0.2f, -0.2f, (TEXTURE_X + 1) * TEXTURE_CELL_SIZE / IMAGE_SIZE,   TEXTURE_Y * TEXTURE_CELL_SIZE / IMAGE_SIZE,
     0.2f,  0.2f, (TEXTURE_X + 1) * TEXTURE_CELL_SIZE / IMAGE_SIZE,  (TEXTURE_Y + 1) * TEXTURE_CELL_SIZE / IMAGE_SIZE,

    -0.2f, -0.2f,  TEXTURE_X * TEXTURE_CELL_SIZE / IMAGE_SIZE,        TEXTURE_Y * TEXTURE_CELL_SIZE / IMAGE_SIZE,
    -0.2f,  0.2f,  TEXTURE_X * TEXTURE_CELL_SIZE / IMAGE_SIZE,       (TEXTURE_Y + 1) * TEXTURE_CELL_SIZE / IMAGE_SIZE,
     0.2f,  0.2f, (TEXTURE_X + 1) * TEXTURE_CELL_SIZE / IMAGE_SIZE,  (TEXTURE_Y + 1) * TEXTURE_CELL_SIZE / IMAGE_SIZE
  };


  shader_create(&rnd->vertex, "./shader.vert", GL_VERTEX_SHADER);
  shader_create(&rnd->fragment, "./shader.frag", GL_FRAGMENT_SHADER);
  program_create(&rnd->prog, &rnd->vertex, &rnd->fragment);
  layout_create_and_bind(&rnd->default_lyt);


  vrtxbuffer_create(&rnd->instanced_pos, rnd->RENDER_QUAD_MAX_COUNT * sizeof(vec2), NULL, GL_DYNAMIC_DRAW);
  layout_enable_and_set_vertex_attrib_pointer(1, 2, GL_FLOAT, sizeof(vec2), (void*)0);
  glVertexAttribDivisor(1, 1);


  vrtxbuffer_create(&rnd->vbo, sizeof(DEFAULT_QUAD_MESH), DEFAULT_QUAD_MESH, GL_STATIC_DRAW);
  layout_enable_and_set_vertex_attrib_pointer(0, 2, GL_FLOAT, sizeof(vec4), (void*)0);
  layout_enable_and_set_vertex_attrib_pointer(2, 2, GL_FLOAT, sizeof(vec4), (void*)(sizeof(vec2)));

  texture_create(&rnd->texture_atlas, "atlas.png", GL_RGBA, GL_RGBA);

  rnd->vbo.unbind(&rnd->vbo);
  rnd->instanced_pos.unbind(&rnd->instanced_pos);
  layout_unbind(&rnd->default_lyt);


  vec2 *positions = calloc(rnd->RENDER_QUAD_MAX_COUNT, sizeof(vec2));
  INITIALIZE_VECTOR2(positions, rnd->RENDER_QUAD_MAX_COUNT, -1.9f, -0.4f);
  for(int index = 0; index < rnd->RENDER_QUAD_MAX_COUNT; index++) {
    if(!index == 0)
      positions[index][0] = positions[index - 1][0] + 0.4;
    else
      positions[index][0] += 0.4;
    positions[index][1] = -0.8f;
  }

  rnd->positions = calloc(rnd->RENDER_QUAD_MAX_COUNT, sizeof(vec2));
  memcpy(rnd->positions, positions, rnd->RENDER_QUAD_MAX_COUNT * sizeof(vec2));

  for (int i = 0; i < rnd->RENDER_QUAD_MAX_COUNT; ++i) {
    printf("Instance %d: Position (%f, %f)\n", i, rnd->positions[i][0], rnd->positions[i][1]);
  }

  free(positions);
}

void render_bricks(Renderer *data) {
  data->texture_atlas.Bind(&data->texture_atlas);
  data->prog.UseProgram(&data->prog);
  glm_ortho(-data->aspect_ratio, data->aspect_ratio, -1.0f, 1.0f, -1.0f, 1.0f, data->projection);
  glUniformMatrix4fv( glGetUniformLocation(data->prog.handle, "projection"), 1, GL_FALSE, (float*)data->projection );
  layout_bind(&data->default_lyt);

  vrtxbuffer_setdata(&data->instanced_pos, 0, data->RENDER_QUAD_MAX_COUNT * sizeof(vec2), data->positions);
  glDrawArraysInstanced(GL_TRIANGLES, 0, 6, data->RENDER_QUAD_MAX_COUNT);
}

void bricks_unbind(Renderer *data) {
  layout_unbind(&data->default_lyt);
  data->prog.Unbind(&data->prog);
  data->texture_atlas.Unbind(&data->texture_atlas);
}
