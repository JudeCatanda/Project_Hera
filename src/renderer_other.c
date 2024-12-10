#include "renderer.h"

//util functions
void INITIALIZE_VECTOR2(vec2* arr, int max_n, float default_x, float default_y) {
  // static int calls = 0;
  // calls++;
  // printf("EXTERN SUCCESS %d\n", calls);
  for(int positions_in_arr = 0; positions_in_arr < max_n; positions_in_arr++) {
    arr[positions_in_arr][0] = default_x;
    arr[positions_in_arr][1] = default_y;
  }
};