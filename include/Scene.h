#ifndef scene_h
#define scene_h

#include <stdio.h>
#include "glad/glad.h"
#include "cglm/cglm.h"
#include "layout.h"
#include "buff.h"
#include "texture.h"

#define MAX_SCENE_NODE_COUNT 100
#define MAX_GAMESCENES_COUNT 3

typedef enum OBJECT_TYPE {
  OBJECT_BLANK = 0,
  OBJECT_TYPE_QUAD, OBJECT_TYPE_TEXT, OBJECT_TYPE_TEXTURE
} OBJECT_TYPE;

typedef struct Scene_Node {
  OBJECT_TYPE type;
  vec2 position;

  layout node_layout;
  vrtxbuffer node_mesh;
  texture_data node_texture;

  int vertex_count;
} Scene_Node;

void scene_create_node(Scene_Node* node, float* mesh_array, OBJECT_TYPE obj_type);

typedef struct Scene {
  Scene_Node objects[MAX_SCENE_NODE_COUNT];
  int object_counts;
  char* desc;
} Scene;

typedef struct Game_Scenes {
  Scene list[MAX_GAMESCENES_COUNT];

  Scene current_bounded;
  char* scene_idf_bounded;
} Game_Scenes;

Game_Scenes* gscenes_get_all(void); //signleton...  static Game_Scenes gscenes; return &gscenes;
void scene_initialize(Scene* sc, char* desc);

#endif
