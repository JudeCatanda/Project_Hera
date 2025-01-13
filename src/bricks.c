#include "bricks.h"

extern void INITIALIZE_VECTOR2(vec2 *arr, int max_n, float default_x, float default_y);

void create_bricks(brick *THE_BRICKS)
{
  FILE *logs = fopen("./logs.txt", "w");
  if (THE_BRICKS->maximum_brick_x == 0 && THE_BRICKS->maximum_brick_y == 0)
  {
    fprintf(stderr, "maximum_brick_? is 0\n");
  }
  THE_BRICKS->BRICKS_COUNT = THE_BRICKS->maximum_brick_x * THE_BRICKS->maximum_brick_y;
  fprintf(logs, "BRICKS_COUNT: %d\nmaximum_brick_x: %d\nmaximum_brick_y: %d\n",
          THE_BRICKS->BRICKS_COUNT, THE_BRICKS->maximum_brick_x, THE_BRICKS->maximum_brick_y);
  fclose(logs);
  float TEXTURE_X = 2, TEXTURE_Y = 15;
  float TEXTURE_CELL_SIZE = 16;
  float IMAGE_SIZE = 256;

  float DEFAULT_QUAD_MESH[24] = {
      -0.2f, -0.2f, TEXTURE_X * TEXTURE_CELL_SIZE / IMAGE_SIZE, TEXTURE_Y * TEXTURE_CELL_SIZE / IMAGE_SIZE,
      0.2f, -0.2f, (TEXTURE_X + 1) * TEXTURE_CELL_SIZE / IMAGE_SIZE, TEXTURE_Y * TEXTURE_CELL_SIZE / IMAGE_SIZE,
      0.2f, 0.2f, (TEXTURE_X + 1) * TEXTURE_CELL_SIZE / IMAGE_SIZE, (TEXTURE_Y + 1) * TEXTURE_CELL_SIZE / IMAGE_SIZE,

      -0.2f, -0.2f, TEXTURE_X * TEXTURE_CELL_SIZE / IMAGE_SIZE, TEXTURE_Y * TEXTURE_CELL_SIZE / IMAGE_SIZE,
      -0.2f, 0.2f, TEXTURE_X * TEXTURE_CELL_SIZE / IMAGE_SIZE, (TEXTURE_Y + 1) * TEXTURE_CELL_SIZE / IMAGE_SIZE,
      0.2f, 0.2f, (TEXTURE_X + 1) * TEXTURE_CELL_SIZE / IMAGE_SIZE, (TEXTURE_Y + 1) * TEXTURE_CELL_SIZE / IMAGE_SIZE};

  shader_create(&THE_BRICKS->vertex_, "./assets/shaders/shader.brick.vert", GL_VERTEX_SHADER);
  shader_create(&THE_BRICKS->fragment_, "./assets/shaders/shader.brick.frag", GL_FRAGMENT_SHADER);
  program_create(&THE_BRICKS->program, &THE_BRICKS->vertex_, &THE_BRICKS->fragment_);
  layout_create_and_bind(&THE_BRICKS->layout_default);

  layout_enable_and_set_vertex_attrib_pointer(1, 2, GL_FLOAT, sizeof(vec2), (void *)0);
  glVertexAttribDivisor(1, 1);

  layout_enable_and_set_vertex_attrib_pointer(0, 2, GL_FLOAT, sizeof(vec4), (void *)0);
  layout_enable_and_set_vertex_attrib_pointer(2, 2, GL_FLOAT, sizeof(vec4), (void *)(sizeof(vec2)));

  texture_create(&THE_BRICKS->atlas, "./assets/textures/atlas.png", GL_RGBA, GL_RGBA);

  layout_unbind(&THE_BRICKS->layout_default);

  vec2 *positions = calloc(THE_BRICKS->BRICKS_COUNT, sizeof(vec2));
  INITIALIZE_VECTOR2(positions, THE_BRICKS->BRICKS_COUNT, -1.9f, -0.4f);
  int index = 0;
  float initial_x = -1.9f;
  float initial_y = -0.4f;
  for (int y = 0; y < THE_BRICKS->maximum_brick_y; y++) // Loop through rows (Y)
  {
    float last_x = initial_x; // Reset the x position at the start of each row

    for (int x = 0; x < THE_BRICKS->maximum_brick_x; x++) // Loop through columns (X)
    {
      positions[index][0] = last_x + 0.4f;        // Increment x position by 0.4
      positions[index][1] = initial_y - y * 0.4f; // Increment y position based on row

      last_x = positions[index][0]; // Update last x position for the next brick in the row
      index++;
    }
  }
  THE_BRICKS->brick_individual_positions = calloc(THE_BRICKS->BRICKS_COUNT, sizeof(vec2));
  memcpy(THE_BRICKS->brick_individual_positions, positions, THE_BRICKS->BRICKS_COUNT * sizeof(vec2));
  // free(positions);
  // printf("texture size %d x %d\n", THE_BRICKS->atlas.img_width, THE_BRICKS->atlas.img_height);
}
void render_bricks(brick *THE_BRICKS)
{
  THE_BRICKS->atlas.Bind(&THE_BRICKS->atlas);
  THE_BRICKS->program.use_program(&THE_BRICKS->program);

  glm_ortho(-THE_BRICKS->ASPECT_RATIO, THE_BRICKS->ASPECT_RATIO, -1.0f, 1.0f, -1.0f, 1.0f, THE_BRICKS->projection);
  glUniformMatrix4fv(glGetUniformLocation(THE_BRICKS->program.handle, "projection"), 1, GL_FALSE, (float *)THE_BRICKS->projection);

  layout_bind(&THE_BRICKS->layout_default);
  glDrawArraysInstanced(GL_TRIANGLES, 0, 6, THE_BRICKS->BRICKS_COUNT);
}

void bricks_unbind(brick *THE_BRICKS)
{
  layout_unbind(&THE_BRICKS->layout_default);
  THE_BRICKS->program.unbind(&THE_BRICKS->program);
  THE_BRICKS->atlas.Unbind(&THE_BRICKS->atlas);
}
