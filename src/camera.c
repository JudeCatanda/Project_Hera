#include "camera.h"

#undef LOG_DEBUG 
#define LOG_DEBUG(fmt, ...) printf("[DEBUG] " fmt "\n", ##__VA_ARGS__)

// void(*send_matrices)(struct Camera* cam, ShaderProgram* program);
void proc_camera_send_matrices(Camera* cam, ShaderProgram* program) {
  Window* window = cam->window;
  window->update_aspect_ratio(window);
  window->get_size(window);
  cam->orthro = glms_ortho(-window->aspect_ratio, window->aspect_ratio, -2.0f, 1.0f, -1.0f, 1.0f);
  cam->view = glms_mat4_identity();
  cam->view = glms_translate(cam->view, (vec3s){ .x = cam->camera_position.x, .y = cam->camera_position.y, .z = 0.0f });
  glUniformMatrix4fv(uniform_location(program->handle, "projection"), 1, GL_FALSE, (const float*)&cam->orthro.raw);
  glUniformMatrix4fv(uniform_location(program->handle, "view"), 1, GL_FALSE, (const float*)&cam->view.raw[0][0]);
  // LOG_DEBUG("window is not null.. here have its size! %dx%d", window->size.x, window->size.y);// actually prints the size! DYNAMICALY!
};
void camera_init(Camera *cam) {
  cam->update = proc_camera_send_matrices;
}
