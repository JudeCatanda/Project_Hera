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

void set_mesh_(float* vertices, int* vertex_count, float x, float y, float scale) {
    // Define the base triangle (local coordinates)
    float triangle[6] = {
        -0.5f * scale + x, -0.5f * scale + y, // Bottom-left
         0.5f * scale + x, -0.5f * scale + y, // Bottom-right
         0.0f * scale + x,  0.5f * scale + y  // Top-center
    };

    // Reallocate memory to append the new vertices
    vertices = realloc(vertices, (*vertex_count + 6) * sizeof(Vertex));
    if (!(*vertices)) {
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(1);
    }

    // Copy the new triangle vertices to the end of the array
    for (int i = 0; i < 6; i++) {
        (vertices)[*vertex_count + i] = triangle[i];
    }

    // Update the vertex count
    *vertex_count += 6;
}

Vertex* vertex_create(Vertex *vertices, float x, float y, float scale) {
  vertices->Position.x = x;
  vertices->Position.y = y;
  vertices++;

  vertices->Position.x  = x + scale;
  vertices->Position.y  = y;
  vertices++;

  vertices->Position.x = x + scale;
  vertices->Position.y = y + scale;
  vertices++;

  return vertices;
}

void vector_push(Vector_Descriptor *vdesc, float *arr, float x, float y, float scale) {

}
