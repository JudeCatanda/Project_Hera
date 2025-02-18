#include "camera.h"

#undef LOG_DEBUG 
#define LOG_DEBUG(fmt, ...) printf("[DEBUG] " fmt "\n", ##__VA_ARGS__)

static vec3s target = (vec3s){ .x = 0.0f, .y = 0.0f, .z = 0.0f };
static vec3s up_vec = (vec3s){ .x = 0.0f, .y = 1.0f, .z = 0.0f };

void proc_camera_send_matrices(Camera* cam, ShaderProgram* program) { //functions gets called every frame
  Window* window = cam->window;

  window->update_aspect_ratio(window);
  window->get_size(window);

  cam->view = glms_lookat(cam->camera_position, target, up_vec);

  glUniformMatrix4fv(uniform_location(program->handle, "projection"), 1, GL_FALSE, (const float*)&cam->projection.raw);
  glUniformMatrix4fv(uniform_location(program->handle, "view"), 1, GL_FALSE, (const float*)&cam->view.raw[0][0]);
};
void camera_init(Camera *cam) {
  cam->update = proc_camera_send_matrices;

  cam->window->update_aspect_ratio(cam->window);
  cam->projection = glms_perspective(glm_rad(45.0f), cam->window->aspect_ratio, 0.1f, 100.0f);

  cam->camera_position = (vec3s){ .x = 0.0f, .y = 0.0f, .z = 3.0f };
}