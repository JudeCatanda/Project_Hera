#include "Terrain.hpp"
#include <random>

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

const int max_render_for_x = 100;
const int max_render_for_y = 20;
const int render_count = max_render_for_x * max_render_for_y;

const unsigned int max_vertex_counts = 2000;
const unsigned int points_per_quad = 6;

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
  vertex->create(GET_SHADERS_PATH("terrain.vert.glsl"), GL_VERTEX_SHADER);
  fragment->create(GET_SHADERS_PATH("terrain.frag.glsl"), GL_FRAGMENT_SHADER);
  program->create(vertex, fragment);

  vao->create_and_bind();

  this->atlas.create(std::string(GET_TEXTURES_PATH("parts.atlas.png")), GL_TEXTURE_2D, GL_RGBA, GL_RGBA);
  this->atlas.bind_and_set_active(GL_TEXTURE1);
  glUniform1i(glGetUniformLocation(program->get_handle(), "tex1"), 1);
  cell_size = glm::vec2(16.0f);
  if(!this->atlas.is_image_valid())
    LOG_DEBUG("the image was invalid for some reason!");

  // positions_buffer->create(render_count * sizeof(glm::vec2), nullptr, GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER);
  // vao->enable_and_set_attrib_ptr(2, 2, GL_FLOAT, sizeof(glm::vec2), (const void *)0);
  // glVertexAttribDivisor(2, 1);
  //not doing instancing anymore

  //unique textures for each quad!
  texture_positions_buffer->create((max_vertex_counts * points_per_quad) * sizeof(glm::vec2), nullptr, GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER);
  vao->enable_and_set_attrib_ptr(5, 2, GL_FLOAT, sizeof(glm::vec2), (const void*)0);
  //glVertexAttribDivisor(5, 1); //hehe you fucking bitch this was the reason why i only used the same uv

  //below code is useless
  //this->mesh_data.push_back((Vertex){.Position = glm::vec2(-this->size, -this->size)});
  //this->mesh_data.push_back((Vertex){.Position = glm::vec2(this->size, -this->size)});
  //this->mesh_data.push_back((Vertex){.Position = glm::vec2(this->size, this->size)});
  //this->mesh_data.push_back((Vertex){.Position = glm::vec2(-this->size, this->size)});

  //mesh_buffer->create(this->mesh_data.size() * sizeof(Vertex), this->mesh_data.data(), GL_STATIC_DRAW, GL_ARRAY_BUFFER);

  std::vector<glm::vec2> vec = this->tg.get_vector();
  mesh_buffer->create((max_vertex_counts * points_per_quad) * sizeof(glm::vec2), nullptr, GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER);
  vao->enable_and_set_attrib_ptr(0, 2, GL_FLOAT, sizeof(glm::vec2), (const void *)0);
  // mesh_buffer->create(this->bacthed_terrain.size() * sizeof(glm::vec2),
  // this->bacthed_terrain.data(), GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER);

  unsigned int indices[] = {0, 1, 2, 0, 3, 2};

  // this->indices = generateIndices(this->bacthed_terrain.size() / 4); //do batched index buffers soon
  indices_buffer->create(sizeof(indices), indices, GL_STATIC_DRAW,
                         GL_ELEMENT_ARRAY_BUFFER);

  positions_buffer->unbind();
  indices_buffer->unbind();
  mesh_buffer->unbind();
  vao->unbind();

  this->tg.clear();
  int idx = 0;
  const float space = 0.05f;
  const float x_starter = -6.0f;
  glm::vec2 offset = glm::vec2(x_starter, 0.0f);
  // srand(time(NULL));
  std::random_device rand_device;
  std::mt19937 engine(rand_device());
  std::uniform_int_distribution<int> dist(0, 3);
  // int rand_pos = 0;
  int sprite_x = 0;
  int sprite_y = 0;
  for(int y = 0; y < max_render_for_y; y++) {
    for (int x = 0; x < max_render_for_x; x++) {
      int rand_pos = dist(engine);
      sprite_x = rand_pos % 2;
      sprite_y = rand_pos / 2;
      this->tg.push_quad_with_sprite(space, offset, glm::vec2(32.0f), cell_size, glm::vec2((float)sprite_x, (float)sprite_y)); //get randome texture
      LOG_DEBUG("%d", rand_pos);
      idx+=1;
      offset.x += space * 2;
    }
    offset.x = x_starter;
    offset.y += space * 2;
  }
  LOG_DEBUG("vector size: %lld", this->tg.get_vector().size());

  // this->mesh_buffer.set_data(0, vec.size() * sizeof(glm::vec2), vec.data());
  this->mesh_buffer.set_data(0, this->tg.get_vector().size() * sizeof(glm::vec2), this->tg.get());
  this->texture_positions_buffer.set_data(0, this->tg.get_vector_with_sprite().size() * sizeof(glm::vec2), this->tg.get_with_sprite());

  // positions_buffer->set_data(0, render_count * sizeof(glm::vec2),
  //                            temp_array.data());

  //texture_positions_buffer->set_data(0, this->tex_pos.size()  * sizeof(glm::vec2), this->tex_pos.data());

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

  // glDrawArrays(GL_TRIANGLES, 0, this->tg.get_points());
  glDrawArrays(GL_TRIANGLES, 0, (max_vertex_counts * points_per_quad));

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
  this->tg.update_quad(1, glm::vec2(-1.0f), 1.0f);
  this->mesh_buffer.set_data(0, this->tg.get_vector().size() * sizeof(glm::vec2), this->tg.get());
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

//void push_quad(float size, float x, float y);
void Terrain_Generator::push_quad(float size, glm::vec2 pos) {
  float x = pos.x;
  float y = pos.y;

  this->data.push_back(glm::vec2(x - size, y - size));
  this->data.push_back(glm::vec2(x + size, y - size));
  this->data.push_back(glm::vec2(x + size, y + size));
  this->points += 3;

  this->data.push_back(glm::vec2(x + size, y + size));
  this->data.push_back(glm::vec2(x - size, y + size));
  this->data.push_back(glm::vec2(x - size, y - size));
  this->points += 3;

  // LOG_DEBUG("[!!!] %d", this->last_write);
  // LOG_DEBUG("[!!!] %d", this->capacity);
};

void Terrain_Generator::update_quad(unsigned int base, glm::vec2 pos, float size) {
  float x = pos.x;
  float y = pos.y;
  unsigned int i = base * 6; 
  if(base + 5 >= this->data.size()) {
    LOG_ERROR("Invalid location access!");
    return;
  }

  this->data[i + 0] = glm::vec2(x - size, y - size);
  this->data[i + 1] = glm::vec2(x + size, y - size);
  this->data[i + 2] = glm::vec2(x + size, y + size);

  this->data[i + 3] = glm::vec2(x + size, y + size);
  this->data[i + 4] = glm::vec2(x - size, y + size);
  this->data[i + 5] = glm::vec2(x - size, y - size);
}

void Terrain_Generator::pop_quad() {
  this->data.pop_back();
  this->data.pop_back();
  this->data.pop_back();

  this->data.pop_back();
  this->data.pop_back();
  this->data.pop_back();
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

const std::vector<glm::vec2>& Terrain_Generator::get_vector(void) const noexcept {
  return this->data;
};

unsigned int Terrain_Generator::get_points(void) const noexcept {
  return this->points;
};

void Terrain_Generator::clear(void) noexcept {
  this->data.clear();
  this->points = 0;
};

void Terrain_Generator::push_quad_with_sprite(float size, glm::vec2 pos, glm::vec2 image_dimensions, glm::vec2 cell_size, glm::vec2 sprite_pos) {
  float x = pos.x;
  float y = pos.y;

  this->data.push_back(glm::vec2(x - size, y - size));
  this->data.push_back(glm::vec2(x + size, y - size));
  this->data.push_back(glm::vec2(x + size, y + size));
  this->points += 3;

  this->data.push_back(glm::vec2(x + size, y + size));
  this->data.push_back(glm::vec2(x - size, y + size));
  this->data.push_back(glm::vec2(x - size, y - size));
  this->points += 3;

  // sprite sheet cell in (column,row)
  float tex_x    = sprite_pos.x;
  float tex_y    = sprite_pos.y;
  float swidth   = cell_size.x;
  float sheight  = cell_size.y;
  float iwidth   = image_dimensions.x;
  float iheight  = image_dimensions.y;
  
  glm::vec2 uv0{ ( tex_x    * swidth) / iwidth, ( tex_y    * sheight) / iheight }; // bottom‐left
  glm::vec2 uv1{ ((tex_x+1) * swidth) / iwidth, ( tex_y    * sheight) / iheight }; // bottom‐right
  glm::vec2 uv2{ ((tex_x+1) * swidth) / iwidth, ((tex_y+1) * sheight) / iheight }; // top‐right
  glm::vec2 uv3{ ( tex_x    * swidth) / iwidth, ((tex_y+1) * sheight) / iheight }; // top‐left
  
  this->texture_pos.push_back(uv0); // tri 1, v0
  this->texture_pos.push_back(uv1); // tri 1, v1
  this->texture_pos.push_back(uv2); // tri 1, v2
  
  this->texture_pos.push_back(uv2); // tri 2, v0
  this->texture_pos.push_back(uv3); // tri 2, v1
  this->texture_pos.push_back(uv0); // tri 2, v2
}

glm::vec2* Terrain_Generator::get_with_sprite(void) const noexcept {
  return (glm::vec2*)this->texture_pos.data();
}

const std::vector<glm::vec2>& Terrain_Generator::get_vector_with_sprite(void) const noexcept {
  return this->texture_pos;
};
