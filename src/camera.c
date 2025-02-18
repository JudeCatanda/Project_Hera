#include "camera.h"

#undef LOG_DEBUG 
#define LOG_DEBUG(fmt, ...) printf("[DEBUG] " fmt "\n", ##__VA_ARGS__)

void proc_camera_send_matrices(Camera* cam, ShaderProgram* program) { //functions gets called every frame
  Window* window = cam->window;

  window->update_aspect_ratio(window);
  window->get_size(window);

  float orthro_w = window->size.x / cam->scale;
  float orthro_h = window->size.y / cam->scale;

  // cam->view = glms_lookat(cam->camera_position, target, up_vec);
  cam->projection = glms_ortho(
    -orthro_w / 2.0f,
     orthro_w / 2.0f,
    -orthro_h / 2.0f,
     orthro_h / 2.0f,
     0.1f, 100.0f
  );
  cam->view = GLMS_MAT4_IDENTITY;
  cam->view = glms_translate(
    cam->view,
    (vec3s){
      .x = -cam->camera_position.x * 2.0f,
      .y = -cam->camera_position.y,
      .z = -cam->camera_position.z
    }
  );

  glUniformMatrix4fv(uniform_location(program->handle, "projection"), 1, GL_FALSE, (const float*)&cam->projection.raw);
  glUniformMatrix4fv(uniform_location(program->handle, "view"), 1, GL_FALSE, (const float*)&cam->view.raw[0][0]);
};
void camera_init(Camera *cam) {
  cam->update = proc_camera_send_matrices;

  cam->window->update_aspect_ratio(cam->window);
  cam->camera_position = (vec3s){ .x = 0.0f, .y = 0.0f, .z = 3.0f };
}