#ifndef cams_h
#define cams_h

#include <stdio.h>
#include "glad/glad.h"
#include "cglm/cglm.h"
#include "cglm/struct.h"
#include "shader.h"

typedef struct camera {

  mat4s proj;
  float *aspect_ratio, screen_w, screen_h;
  mat4 view;

  unsigned int projection_location, view_location;

  void(*bind_camera)(struct camera* cam_struct, shader_program* program);
  //@brief sets the aspect ration member from the struct with the ptr supplied
  //@param ptr the ptr to the aspect ratio (float)
  void(*set_aspect_ratio_ptr)(struct camera* cam_struct, float* ptr);

  struct camera* self;
} camera;

void camera_init(camera* cam);

#endif
