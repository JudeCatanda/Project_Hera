#include "scene.h"

Scene *scene_get_all(Scene *sc) {
  static Scene scenes_list;
}

Game_Scenes *gscenes_get_all(void) {
  static Game_Scenes gscenes;

  return &gscenes;
}

void scene_initialize(Scene *sc, char *desc) {
  sc->desc = desc;
}

void scene_create_node(Scene_Node* node, float* mesh_array, OBJECT_TYPE obj_type) {
};
