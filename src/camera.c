#include "camera.h"

#undef def_as_ptr
#define def_as_ptr(pstruct, pname) typeof(pstruct->pname)* pname = &pstruct->pname;

// void(*send_matrices)(struct Camera* cam, ShaderProgram* program);
void proc_camera_send_matrices(Camera* cam, ShaderProgram* program) {

};
// void(*create_camera)(struct Camera* cam);
void proc_camera_create(Camera* cam) {
  cam->orthro = glms_ortho(cam->);
};

void camera_init(Camera *cam) {
  cam->send_matrices = proc_camera_send_matrices;
}
