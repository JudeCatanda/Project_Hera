#include "Terrain.hpp"

#undef def_as_ptr
#define def_as_ptr(name) typeof(this->name) *name = &this->name
#undef LOG_DEBUG
#define LOG_DEBUG(fmt, ...) std::printf("[DEBUG] " fmt "\n", ##__VA_ARGS__)
#undef LOG_ERROR
#define LOG_ERROR(fmt, ...) std::printf("[ERROR] " fmt "\n", ##__VA_ARGS__);
#define glCall(statement)\
  statement;\
  while(GLenum err = glGetError())\
    LOG_ERROR("AH SHIT!!! %d @line: %d", err, __LINE__);

const int max_render_for_x = 30;
const int max_render_for_y = 1;
const int render_count = max_render_for_x * max_render_for_y;

glm::vec2 cell_size;

void Terrain::create() {
  def_as_ptr(vertex);
  def_as_ptr(fragment);
  def_as_ptr(program);
  def_as_ptr(vao);
  def_as_ptr(mesh_buffer);
  def_as_ptr(indices_buffer);
  def_as_ptr(positions_buffer);
  def_as_ptr(texture_positions_buffer);

  //this->rdoc_api->StartFrameCapture(nullptr, nullptr);
  glCall(vertex->create(GET_SHADERS_PATH("terrain.vert.glsl"), GL_VERTEX_SHADER));
  glCall(fragment->create(GET_SHADERS_PATH("terrain.frag.glsl"), GL_FRAGMENT_SHADER));
  glCall(program->create(vertex, fragment));

  glCall(vao->create_and_bind());

  glCall(this->atlas.create(std::string(GET_TEXTURES_PATH("parts.atlas.png")), GL_TEXTURE_2D, GL_RGBA, GL_RGBA));
  glCall(this->atlas.bind_and_set_active(GL_TEXTURE1));
  glCall(glUniform1i(glGetUniformLocation(program->get_handle(), "tex1"), 1));
  cell_size = glm::vec2(16.0f);
  if(!this->atlas.is_image_valid())
    LOG_DEBUG("the image was invalid for some reason!");

  glCall(positions_buffer->create(render_count * sizeof(glm::vec2), nullptr, GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER));
  glCall(vao->enable_and_set_attrib_ptr(2, 2, GL_FLOAT, sizeof(glm::vec2), (const void *)0));
  glCall(glVertexAttribDivisor(2, 1));
  //unique textures for each quad!
  glCall(texture_positions_buffer->create(render_count * 2 * sizeof(glm::vec2), nullptr, GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER));
  glCall(vao->enable_and_set_attrib_ptr(5, 2, GL_FLOAT, sizeof(glm::vec2), (const void*)0));
  glCall(glVertexAttribDivisor(5, 1));

  this->mesh_data.push_back((Vertex){.Position = glm::vec2(-this->size, -this->size)});
  this->mesh_data.push_back((Vertex){.Position = glm::vec2(this->size, -this->size)});
  this->mesh_data.push_back((Vertex){.Position = glm::vec2(this->size, this->size)});
  this->mesh_data.push_back((Vertex){.Position = glm::vec2(-this->size, this->size)});

  //mesh_buffer->create(this->mesh_data.size() * sizeof(Vertex), this->mesh_data.data(), GL_STATIC_DRAW, GL_ARRAY_BUFFER);

  this->tg.push_quad(0.1f, glm::vec2(0.0f, 0.0f));
  this->tg.push_quad(0.1f, glm::vec2(1.0f, 1.0f));
  //mesh_buffer->create((this->tg.get_points() * 2) * sizeof(float), this->tg.get(), GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER);
  mesh_buffer->create(this->tg.get_vector()->size() * sizeof(glm::vec2), this->tg.get_vector()->data(), GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER);
  vao->enable_and_set_attrib_ptr(0, 2, GL_FLOAT, 2 * sizeof(float), (const void *)0);
  // mesh_buffer->create(this->bacthed_terrain.size() * sizeof(glm::vec2),
  // this->bacthed_terrain.data(), GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER);

  unsigned int indices[] = {0, 1, 2, 0, 3, 2};

  // this->indices = generateIndices(this->bacthed_terrain.size() / 4);
  indices_buffer->create(sizeof(indices), indices, GL_STATIC_DRAW,
                         GL_ELEMENT_ARRAY_BUFFER);

  positions_buffer->unbind();
  indices_buffer->unbind();
  mesh_buffer->unbind();
  vao->unbind();

  // std::array<glm::vec2, render_count> temp_array = {};
  // int index = 0;
  // glm::vec2 offset = glm::vec2(-6.0f, -6.0f);
  // for (int y = 0; y < max_render_for_y; y++) {
  //   for (int x = 0; x < max_render_for_x; x++) {
  //     temp_array[index] = offset; // Store first, then update offset
  //     this->tg.push_quad(this->size, offset.x, offset.y);
  //     index++;
  //     set_texture_pos(this->atlas, &this->tex_pos, glm::vec2(0.0f));
  //     offset.x += this->size * 2; // Move right
  //   }
  //
  //   offset.x = -6.0f;           // Reset x position for next row
  //   offset.y += this->size * 2; // Move down
  // }
  this->tg.log_class();
  int idx = 0;
  glm::vec2 offset2 = glm::vec2(0.0f, 0.0f);
  for(int y = 0; y < max_render_for_y; y++) {
    for (int x = 0; x < max_render_for_x; x++) {
      this->tg.push_quad(0.2f, offset2);
      //temp_array[idx] = offset2;
      idx+=1;
      offset2.x += this->size * 2;
    }
    offset2.x = 0.0f;
    offset2.y += this->size * 2;
  }

  for(int i = 0; i < this->tg.get_points(); i++) {
    //LOG_DEBUG("%2.2f, %2.2f", this->tg.at(i).x ,this->tg.at(i).y);
  }
  this->tg.log_class();
  this->mesh_buffer.set_data(0, this->tg.get_vector()->size() * sizeof(glm::vec2), this->tg.get_vector()->data());

  // positions_buffer->set_data(0, render_count * sizeof(glm::vec2),
  //                            temp_array.data());

  texture_positions_buffer->set_data(0, this->tex_pos.size()  * sizeof(glm::vec2), this->tex_pos.data());

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
  //TODO: Fix this shit
  this->hitbox.size = this->size;
  this->hitbox.maximum = this->hitbox.origin + this->size * 2;
}

void Terrain::draw() {
  def_as_ptr(program);
  def_as_ptr(vao);
  def_as_ptr(indices_buffer);
  def_as_ptr(positions_buffer);

  program->bind();
  this->atlas.bind_and_set_active(GL_TEXTURE1);
  vao->bind();
  indices_buffer->bind();
  positions_buffer->bind();

  //GLenum err;
  //if((err = glGetError()) != GL_NO_ERROR)
  //  LOG_ERROR("Ah shit there's an error in terrain::draw! fuck this i am out! %d", err);

  this->hitbox.size = this->size;

  //glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, render_count);
  this->mesh_buffer.set_data(0, this->tg.get_vector()->size() * sizeof(glm::vec2), this->tg.get_vector()->data());

  glDrawArrays(GL_TRIANGLES, 0, this->tg.get_points());

  //this->rdoc_api->EndFrameCapture(nullptr, nullptr);
  //this->rdoc_api->ShowReplayUI();
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

void Terrain::test_tg(void) {
  // int ret = this->tg.update_quads(0, 2.0f, 2.0f, 0.5f);
  //this->tg.push_quad(0.5f, 3.0f, 3.0f);
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
void set_texture_pos(Texture& texture, std::vector<glm::vec2>* tex_pos, glm::vec2 pos) {
  glm::vec2 size = texture.get_size();
  //LOG_DEBUG("The Size of the texture accessed is %.2f,%.2f", size.x, size.y);
  float u_min, u_max, v_min, v_max;
  u_min = (pos.x * cell_size.x) / size.x;
  u_max = ((pos.x + 1.0f) * cell_size.x) / size.x;
  v_min = (pos.y * cell_size.y) / size.y;
  v_max = ((pos.y + 1) * cell_size.y) / size.y;
  //LOG_DEBUG("Positions Are Lower left: %f %f\nLower right: %f %f\nUpper right: %f %f\nUpper left: %f %f\n", u_min, v_min, u_max, v_min, u_max, v_max, u_min, v_max);

  tex_pos->push_back(glm::vec2(u_min, v_min));
  tex_pos->push_back(glm::vec2(u_max, v_min));
  tex_pos->push_back(glm::vec2(u_max, v_max));
  tex_pos->push_back(glm::vec2(u_min, v_max));
};

void Terrain_Generator::push_back(float wx, float wy) {
  this->data.push_back(glm::vec2(wx, wy));
  this->points += 1;
};

//void push_quad(float size, float x, float y);
void Terrain_Generator::push_quad(float size, glm::vec2 pos) {
  float x = pos.x;
  float y = pos.y;
  this->push_back(x - size, y - size);
  this->push_back(x + size, y - size);
  this->push_back(x + size, y + size);

  this->push_back(x + size, y + size);
  this->push_back(x - size, y + size);
  this->push_back(x - size, y - size);
  // LOG_DEBUG("[!!!] %d", this->last_write);
  // LOG_DEBUG("[!!!] %d", this->capacity);
};

unsigned int Terrain_Generator::get_points(void) const noexcept {
  return this->points;
}

void Terrain_Generator::update_quad(unsigned int base, float x, float y, float size) {
  unsigned int i = base * 12; 
  if(base + 11 >= 0) {
    LOG_ERROR("Invalid location access!");
    return;
  }
}

void Terrain_Generator::pop_back() {
  this->data.pop_back();
  this->data.pop_back();
}

void Terrain_Generator::pop_quad() {
  this->pop_back();
  this->pop_back();
  this->pop_back();

  this->pop_back();
  this->pop_back();
  this->pop_back();
}

glm::vec2* Terrain_Generator::get(void) const noexcept {
  return (glm::vec2*)this->data.data();
};

// int Terrain_Generator::update_quads(unsigned int index, float x, float y, float size) {
//   int cpy = index;
//   this->set_at(cpy++, x - size, y - size);
//   this->set_at(cpy++, x + size, y - size);
//   this->set_at(cpy++, x + size, y + size);
//   this->set_at(cpy++, x + size, y + size);
//   this->set_at(cpy++, x - size, y + size);
//   this->set_at(cpy++, x - size, y - size);
//   LOG_DEBUG("value of the ret is %d" , cpy);
//   return cpy;
// };

glm::vec2 Terrain_Generator::at(unsigned int index) {
  return this->data[index];
}

void Terrain_Generator::set_at(unsigned int index, float xvalue, float yvalue) {
  if(this->at(index).x == RET_ERR_VEC2)
    return;
};

void Terrain_Generator::log_class(void) {
  LOG_DEBUG(" [Log Class was called!]\n>  size: %d\n>  get_points: %d\n>  capacity: %d", 0, this->get_points(), 0);
};

Terrain_Generator::~Terrain_Generator() {
  this->points = 0;
}

std::vector<float>* Terrain_Generator::get_vector(void) const noexcept {
  return (std::vector<float>*)&this->data;
};
