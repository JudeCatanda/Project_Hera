#include "camera.h"

void camera_bind_camera(camera *cam_struct, shader_program *program) {
  program->UseProgram(program);

  cam_struct->proj = glms_ortho(-*cam_struct->aspect_ratio, *cam_struct->aspect_ratio, -1.0f, 1.0, -1.0f, 1.0f);
  glm_mat4_identity(cam_struct->view);

  //vec3 negPos;
  //glm_vec3_negate_to(cam_struct->position, negPos);
  glm_translate(cam_struct->view, cam_struct->position);

  cam_struct->view_location = glGetUniformLocation(program->handle, "view");
  cam_struct->projection_location = glGetUniformLocation(program->handle, "projection");
  glUniformMatrix4fv(cam_struct->projection_location, 1, GL_FALSE, (const float *)&cam_struct->proj.raw);
  glUniformMatrix4fv(cam_struct->view_location, 1, GL_FALSE, (const float*)&cam_struct->view[0][0]);
};

//void(*set_aspect_ratio_ptr)(struct camera* cam_struct, float* ptr);
void camera_set_aspect_ration_ptr(camera* cam_struct, float* ptr) {
  cam_struct->aspect_ratio = ptr;
};
void camera_init(camera *cam) {
  cam->self = cam;
  cam->bind_camera = camera_bind_camera;
  cam->set_aspect_ratio_ptr = camera_set_aspect_ration_ptr;

  if(cam->bind_camera != NULL) {
    // printf("Camera Attached\n");
  }
  if(cam->set_aspect_ratio_ptr == NULL) {
    printf("Did not bound (camera_set_aspect_ration_ptr()) \n");
  }
}
