#ifndef cams_h
#define cams_h

#include <stdio.h>
#include "glad/glad.h"
#include "cglm/cglm.h"
#include "cglm/struct.h"
#include "shader.h"

typedef struct camera {
  
  vec3 position;

  mat4s proj;
  float *aspect_ratio, screen_w, screen_h;
  mat4 view;

  unsigned int projection_location, view_location;

  //@brief binds the camera and changing its position
  //@param cam_struct use cam.self
  //@param program the shader program which the uniforms is located
  void(*bind_camera)(struct camera* cam_struct, ShaderProgram* program);
  //@brief sets the aspect ration member from the struct with the ptr supplied
  //@param cam_struct use cam.self
  //@param ptr the ptr to the aspect ratio (float)
  void(*set_aspect_ratio_ptr)(struct camera* cam_struct, float* ptr);

  struct camera* self;
} camera;

void camera_init(camera* cam);

#endif
