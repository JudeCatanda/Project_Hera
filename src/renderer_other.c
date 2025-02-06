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
void set_mesh(float *mesh_array, float x, float y) {
  //to Ez?
  //const int vertex_count = 6;
  //for(int y_idx = 0; y < 5; y_idx++) {
  //  for(int x_idx = 0; x < 3; x_idx++) {
  //    //pass!
  //    if(y_idx == 0 && x_idx == 0)
  //      mesh_array[x_idx][y_idx] = -x;
  //    if(y_idx == 0 && x_idx == 1)
  //      mesh_array[x_idx][y_idx] = -y;
  //    if(y_idx == 1 && x_idx == 1)
  //      mesh_array[x_idx][y_idx] = -y;
  //  }
  //}
  mesh_array[0] = -x; mesh_array[1] = -y;   //Trust me... this will not help in the future
  mesh_array[2] = x;  mesh_array[3] = -y;   //Trust me... this will not help in the future
  mesh_array[4] = x;  mesh_array[5] = y;    //Trust me... this will not help in the future
  mesh_array[6] = -x; mesh_array[7] = -y;   //Trust me... this will not help in the future
  mesh_array[8] = -x; mesh_array[9] = y;    //Trust me... this will not help in the future
  mesh_array[10] = x; mesh_array[11] = y;   //Trust me... this will not help in the future
};

float lerp(float start, float end, float percentage) {
  return start + (end - start) * percentage;
}

Vertex* vertex_create(Vertex *vertices, float x, float y, float scale) {
  vertices->Position = (vec2s){ .x = x, .y = y };
  vertices += 1;

  vertices->Position = (vec2s){ .x = x + scale, .y = y };
  vertices += 1;

  vertices->Position = (vec2s){ .x = x + scale, .y = y + scale };
  vertices += 1;

  vertices->Position = (vec2s){ .x = x, .y = y + scale };
  vertices += 1;
  return vertices;
}

unsigned int* ebo_add_index(unsigned int* array, int index_offset) {
    // First triangle: (0, 1, 2)
    *array++ = index_offset;
    *array++ = index_offset + 1;
    *array++ = index_offset + 2;

    // Second triangle: (2, 3, 0)
    *array++ = index_offset + 2;
    *array++ = index_offset + 3;
    *array++ = index_offset;

    return array;  // Return updated pointer
}

