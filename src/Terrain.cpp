#include "Terrain.hpp"

#undef def_as_ptr
#define def_as_ptr(name) typeof(this->name) *name = &this->name
#undef LOG_DEBUG
#define LOG_DEBUG(fmt, ...) std::printf("[DEBUG] " fmt "\n", ##__VA_ARGS__)

const int max_render_for_x = 30;
const int max_render_for_y = 50;
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
  positions_buffer->create(render_count * sizeof(glm::vec2), nullptr,
                           GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER);
  vao->enable_and_set_attrib_ptr(2, 2, GL_FLOAT, sizeof(glm::vec2),
                                 (const void *)0);
  glVertexAttribDivisor(2, 1);

  this->mesh_data.push_back(
      (Vertex){.Position = glm::vec2(-this->size, -this->size)});
  this->mesh_data.push_back(
      (Vertex){.Position = glm::vec2(this->size, -this->size)});
  this->mesh_data.push_back(
      (Vertex){.Position = glm::vec2(this->size, this->size)});
  this->mesh_data.push_back(
      (Vertex){.Position = glm::vec2(-this->size, this->size)});

  mesh_buffer->create(this->mesh_data.size() * sizeof(Vertex),
                      this->mesh_data.data(), GL_STATIC_DRAW, GL_ARRAY_BUFFER);
  // mesh_buffer->create(this->bacthed_terrain.size() * sizeof(glm::vec2),
  // this->bacthed_terrain.data(), GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER);
  vao->enable_and_set_attrib_ptr(0, 2, GL_FLOAT, sizeof(glm::vec2),
                                 (const void *)0);

  unsigned int indices[] = {0, 1, 2, 0, 3, 2};

  // this->indices = generateIndices(this->bacthed_terrain.size() / 4);
  indices_buffer->create(sizeof(indices), indices, GL_STATIC_DRAW,
                         GL_ELEMENT_ARRAY_BUFFER);

  positions_buffer->unbind();
  indices_buffer->unbind();
  mesh_buffer->unbind();
  vao->unbind();

  std::array<glm::vec2, render_count> temp_array = {};
  int index = 0;
  glm::vec2 offset = glm::vec2(-5.0f, -5.0f);
  for (int y = 0; y < max_render_for_y; y++) {
    for (int x = 0; x < max_render_for_x; x++) {
      temp_array[index] = offset; // Store first, then update offset
      index++;

      offset.x += this->size * 2; // Move right
    }

    offset.x = -5.0f;            // Reset x position for next row
    offset.y += this->size * 2; // Move down
  }

  //for (glm::vec2 pos_data : temp_array) {
  //  LOG_DEBUG("<pos> %2.2f %2.2f", pos_data.x, pos_data.y);
  //};
  positions_buffer->set_data(0, render_count * sizeof(glm::vec2),
                             temp_array.data());

  // positions_buffer->bind();
  // void* buffer = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
  // if(buffer) {
  //   glm::vec2* gpu_data = (glm::vec2*)buffer;
  //   for (size_t i = 0; i < render_count; i++) {
  //     LOG_DEBUG("GPU Buffer[%zu] = (%.2f, %.2f)", i, gpu_data[i].x,
  //     gpu_data[i].y);
  //   }
  //   glUnmapBuffer(GL_ARRAY_BUFFER);
  // }
  // positions_buffer->unbind();

  indices_buffer->bind();
  void *buffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_ONLY);
  if (buffer) {
    unsigned int *gpu_data = (unsigned int *)buffer;
    for (int i = 0; i < (int)this->indices.size(); i++)
      LOG_DEBUG("index: %d", gpu_data[i]);
  }
  glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
  this->indices_buffer.unbind();

  this->hitbox.size = this->size;
  this->hitbox.maximum = this->hitbox.origin + this->size * 2;
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

  this->hitbox.size = this->size;

  glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, render_count);
  // glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
  // glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
  //  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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

int write_point(int first_index, std::vector<glm::vec2> &collection,
                glm::vec2 data) {
  int end_offset = first_index;
  LOG_DEBUG("first index was: %d", first_index);
  collection.insert(collection.begin() + end_offset, data);
  end_offset += 1;
  return end_offset;
};
int write_quad(int first_index, std::vector<glm::vec2> &collection, float size,
               glm::vec2 pos) {
  collection.resize(collection.size() + 4);
  collection.at(first_index) = pos + glm::vec2(-size, -size);
  collection.at(first_index + 1) = pos + glm::vec2(size, -size);
  collection.at(first_index + 2) = pos + glm::vec2(size, size);
  collection.at(first_index + 3) = pos + glm::vec2(-size, size);
  return first_index + 4;
};
std::vector<unsigned int> generateIndices(int quadCount) {
  std::vector<unsigned int> indices(quadCount * 6);
  for (int q = 0; q < quadCount; ++q) {
    int base = 4 * q;
    indices[q * 6 + 0] = base;
    indices[q * 6 + 1] = base + 1;
    indices[q * 6 + 2] = base + 2;
    indices[q * 6 + 3] = base;
    indices[q * 6 + 4] = base + 3;
    indices[q * 6 + 5] = base + 2;
  }
  return indices;
}
