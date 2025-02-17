#include "camera.h"

#undef LOG_DEBUG 
#define LOG_DEBUG(fmt, ...) printf("[DEBUG] " fmt "\n", ##__VA_ARGS__)

void proc_camera_send_matrices(Camera* cam, ShaderProgram* program) { //functions gets called every frame
  Window* window = cam->window;
  window->update_aspect_ratio(window);
  window->get_size(window);
  cam->orthro = glms_ortho(-window->aspect_ratio, window->aspect_ratio, -2.0f, 1.0f, -1.0f, 1.0f);
  cam->view = glms_mat4_identity();
  cam->view = glms_translate(cam->view, (vec3s){ .x = cam->camera_position.x, .y = cam->camera_position.y, .z = 0.0f }); //move the camera

  glUniformMatrix4fv(uniform_location(program->handle, "projection"), 1, GL_FALSE, (const float*)&cam->orthro.raw);
  glUniformMatrix4fv(uniform_location(program->handle, "view"), 1, GL_FALSE, (const float*)&cam->view.raw[0][0]);
};
void camera_init(Camera *cam) {
  cam->update = proc_camera_send_matrices;
}