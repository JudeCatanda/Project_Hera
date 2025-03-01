#include "Terrain.hpp"

#undef def_as_ptr
#define def_as_ptr(name) typeof(this->name)* name = &this->name
#undef LOG_DEBUG
#define LOG_DEBUG(fmt, ...) std::printf("[DEBUG] " fmt "\n", ##__VA_ARGS__)

const int max_render_for_x = 25;
const int max_render_for_y = 1;
const int render_count = max_render_for_x * max_render_for_y;

void Terrain::create() {
  def_as_ptr(vertex);
  def_as_ptr(fragment);
  def_as_ptr(program);
  def_as_ptr(vao);
  def_as_ptr(mesh_buffer);
  def_as_ptr(indices_buffer);
  def_as_ptr(positions_buffer);

  vertex->create(GET_SHADERS_PATH("terrain.vert.glsl"), GL_VERTEX_SHADER);
  fragment->create(GET_SHADERS_PATH("terrain.frag.glsl"), GL_FRAGMENT_SHADER);
  program->create(vertex, fragment);

  vao->create_and_bind();
  positions_buffer->create(render_count * sizeof(glm::vec2), nullptr, GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER);
  vao->enable_and_set_attrib_ptr(2, 2, GL_FLOAT, sizeof(glm::vec2), (const void*)0);
  glVertexAttribDivisor(2, 1);

  this->mesh_data.push_back((Vertex){ .Position = glm::vec2( -this->size, -this->size ) });
  this->mesh_data.push_back((Vertex){ .Position = glm::vec2(  this->size, -this->size ) });
  this->mesh_data.push_back((Vertex){ .Position = glm::vec2(  this->size,  this->size ) });
  this->mesh_data.push_back((Vertex){ .Position = glm::vec2( -this->size,  this->size ) });

  mesh_buffer->create(this->mesh_data.size() * sizeof(Vertex), this->mesh_data.data(), GL_STATIC_DRAW, GL_ARRAY_BUFFER);
  vao->enable_and_set_attrib_ptr(0, 2, GL_FLOAT, sizeof(Vertex), (const void*)0);

  unsigned int indices[] = {
    0, 1, 2,
    0, 3, 2
  };

  indices_buffer->create(sizeof(indices), indices, GL_STATIC_DRAW, GL_ELEMENT_ARRAY_BUFFER);

  positions_buffer->unbind();
  indices_buffer->unbind();
  mesh_buffer->unbind();
  vao->unbind();

  std::array<glm::vec2, render_count> temp_array = {};
  float offset = 1.0f;
  this->first_offset = offset;
  for (size_t i = 0; i < temp_array.size(); i++) {
    temp_array[i] = glm::vec2(offset, -0.800000012f);
    if(i == 0)
      this->pos_data.push_back(offset);
    offset += this->size * 2;
    if(i == temp_array.size() - 1)
      this->pos_data.push_back(offset);
  }
  this->terrain_hbox_end_size = offset;
  positions_buffer->set_data(0, render_count * sizeof(glm::vec2), temp_array.data());

  // positions_buffer->bind();
  // void* buffer = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
  // if(buffer) {
  //   glm::vec2* gpu_data = (glm::vec2*)buffer;
  //   for (size_t i = 0; i < render_count; i++) {
  //     LOG_DEBUG("GPU Buffer[%zu] = (%.2f, %.2f)", i, gpu_data[i].x, gpu_data[i].y);
  //   }
  //   glUnmapBuffer(GL_ARRAY_BUFFER);
  // }
  // positions_buffer->unbind();
  this->hitbox.origin = glm::vec2(this->pos_data[0], -0.800000012f);
  this->hitbox.size = this->size;
}

void Terrain::draw() {
  def_as_ptr(program);
  def_as_ptr(vao);
  def_as_ptr(indices_buffer);
  def_as_ptr(positions_buffer);

  program->bind();
  vao->bind();
  indices_buffer->bind();
  positions_buffer->bind();

  this->hitbox.origin = glm::vec2(this->pos_data[0], -0.800000012f);
  this->hitbox.size = this->size;

  program->send_uniform_float("dbg", this->dbg_color);

  glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, render_count);
  // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  program->unbind();
  vao->unbind();
  indices_buffer->unbind();
}

void Terrain::destroy() {
  def_as_ptr(program);
  def_as_ptr(vao);
  def_as_ptr(mesh_buffer);
  def_as_ptr(indices_buffer);
  def_as_ptr(positions_buffer);

  program->destroy();
  vao->destroy();
  mesh_buffer->destroy();
  indices_buffer->destroy();
  positions_buffer->destroy();
}

// void Terrain::set_camera(glm::mat4 *mat) {
//   this->camera = *mat;
// }

bool Terrain::is_player_collided(glm::vec2* plr_pos, float player_hitbox_size) {
  // Define player's AABB (assuming plr_pos is the bottom-left corner)
  glm::vec2 player_min = *plr_pos;
  glm::vec2 player_max = *plr_pos + glm::vec2(player_hitbox_size, player_hitbox_size);
  
  // Known terrain parameters:
  float terrainWidth = this->size * 2.0f;
  float terrainY = -0.800000012f;  // constant y position used in your positions_buffer
  // Let's assume the terrain instances are arranged in a line along the x-axis.
  float firstOffset = 0.0f;  // or this->first_offset if you set it elsewhere
  
  // for (size_t i = 0; i < render_count; i++) {
  //     float instanceX = firstOffset + i * terrainWidth;
  //     glm::vec2 terrain_min = glm::vec2(instanceX, terrainY);
  //     glm::vec2 terrain_max = terrain_min + glm::vec2(terrainWidth, terrainWidth); // assuming square terrain
      
  //     if (player_max.x >= terrain_min.x && player_min.x <= terrain_max.x &&
  //         player_max.y >= terrain_min.y && player_min.y <= terrain_max.y) {
  //         return true;
  //     }
  if(player_max.x >= this->pos_data[0] && player_min.x <= this->pos_data[1] &&
     player_max.y >= terrainY && player_min.y <= terrainY + terrainWidth) {
    return true;
  }
  
  return false;
}

AABB_Hitbox * Terrain::get_hitbox() {
  return &this->hitbox;
}

ShaderProgram *Terrain::get_shader_program(void) {
  return &this->program;
}
