#include "bricks.h"

extern void INITIALIZE_VECTOR2(vec2 *arr, int max_n, float default_x, float default_y);

void create_bricks(brick *THE_BRICKS) {
  if(THE_BRICKS->maximum_brick_x == 0 && THE_BRICKS->maximum_brick_y == 0) {
    fprintf(stderr, "maximum_brick_? is 0\n");
  }
  THE_BRICKS->BRICKS_COUNT = THE_BRICKS->maximum_brick_x + THE_BRICKS->maximum_brick_y;
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


  shader_create(&THE_BRICKS->vertex_, "./shader.vert", GL_VERTEX_SHADER);
  shader_create(&THE_BRICKS->fragment_, "./shader.frag", GL_FRAGMENT_SHADER);
  program_create(&THE_BRICKS->_default_p, &THE_BRICKS->vertex_, &THE_BRICKS->fragment_);
  layout_create_and_bind(&THE_BRICKS->_default);


  vrtxbuffer_create(&THE_BRICKS->instanced_positions_buffer, THE_BRICKS->BRICKS_COUNT * sizeof(vec2), NULL, GL_DYNAMIC_DRAW);
  layout_enable_and_set_vertex_attrib_pointer(1, 2, GL_FLOAT, sizeof(vec2), (void*)0);
  glVertexAttribDivisor(1, 1);


  vrtxbuffer_create(&THE_BRICKS->mesh_vbo, sizeof(DEFAULT_QUAD_MESH), DEFAULT_QUAD_MESH, GL_STATIC_DRAW);
  layout_enable_and_set_vertex_attrib_pointer(0, 2, GL_FLOAT, sizeof(vec4), (void*)0);
  layout_enable_and_set_vertex_attrib_pointer(2, 2, GL_FLOAT, sizeof(vec4), (void*)(sizeof(vec2)));

  texture_create(&THE_BRICKS->atlas, "atlas.png", GL_RGBA, GL_RGBA);

  THE_BRICKS->mesh_vbo.unbind(&THE_BRICKS->mesh_vbo);
  THE_BRICKS->instanced_positions_buffer.unbind(&THE_BRICKS->instanced_positions_buffer);
  layout_unbind(&THE_BRICKS->_default);

  vec2 *positions = calloc(THE_BRICKS->BRICKS_COUNT, sizeof(vec2));
  INITIALIZE_VECTOR2(positions, THE_BRICKS->BRICKS_COUNT, -1.9f, -0.4f);
  for(int index = 0; index < THE_BRICKS->BRICKS_COUNT; index++) {
    if(!index == 0)
      positions[index][0] = positions[index - 1][0] + 0.4;
    else
      positions[index][0] += 0.4;
    positions[index][1] = -0.8f;
  }

  THE_BRICKS->brick_individual_positions = calloc(THE_BRICKS->BRICKS_COUNT, sizeof(vec2));
  memcpy(THE_BRICKS->brick_individual_positions, positions, THE_BRICKS->BRICKS_COUNT * sizeof(vec2));

  free(positions);
}