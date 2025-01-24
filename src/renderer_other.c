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

void set_mesh_(float **mesh_array, size_t *size, float x, float y, float scale) {
    // Reallocate memory to make space for 4 new elements (for x, y, y+scale, x+scale)
    mesh_array = realloc(mesh_array, (*size + 4) * sizeof(float));

    if (mesh_array == NULL) {
        // Handle memory allocation failure
        printf("Memory allocation failed\n");
        return;
    }

    // Append the new values to the array
    mesh_array[*size] = x;
    mesh_array[*size + 1] = y;
    mesh_array[*size + 2] = y + scale;
    mesh_array[*size + 3] = x + scale;

    // Update the size of the array
    *size += 4;

    // Note: the pointer was modified, but the calling function must receive the new pointer
}