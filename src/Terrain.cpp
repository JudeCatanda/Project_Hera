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

const int max_render_for_x = 200;
const int max_render_for_y = 200;
const int render_count = max_render_for_x * max_render_for_y;

const unsigned int max_vertex_counts = 50000;//renamed soon to max_quads_count
const unsigned int points_per_quad = 4;
const unsigned int indices_per_quad = 6;

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

  texture_positions_buffer->create((max_vertex_counts * points_per_quad) * sizeof(glm::vec2), nullptr, GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER);
  vao->enable_and_set_attrib_ptr(5, 2, GL_FLOAT, sizeof(glm::vec2), (const void*)0);

  std::vector<glm::vec2> vec = this->tg.get_vector();
  mesh_buffer->create((max_vertex_counts * points_per_quad) * sizeof(glm::vec2), nullptr, GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER);
  vao->enable_and_set_attrib_ptr(0, 2, GL_FLOAT, sizeof(glm::vec2), (const void *)0);

  indices_buffer->create((max_vertex_counts * indices_per_quad) * sizeof(unsigned int), nullptr, GL_DYNAMIC_DRAW,
                         GL_ELEMENT_ARRAY_BUFFER);

  positions_buffer->unbind();
  indices_buffer->unbind();
  mesh_buffer->unbind();
  vao->unbind();

  this->tg.clear();
  int idx = 0;
  const float space = 0.05f;
  const float x_starter = -1.0f;
  glm::vec2 offset = glm::vec2(x_starter, -0.1f);

  std::random_device rand_device;
  std::mt19937 engine(rand_device());
  std::uniform_int_distribution<int> dist(0, 3);

  int sprite_x = 0;
  int sprite_y = 0;
  for(int y = 0; y < max_render_for_y; y++) {
    for (int x = 0; x < max_render_for_x; x++) {
      int rand_pos = dist(engine);
      sprite_x = rand_pos % 2;
      sprite_y = rand_pos / 2;
      this->tg.push_quad_with_sprite(space, offset, glm::vec2(32.0f), cell_size, glm::vec2((float)sprite_x, (float)sprite_y)); //get randome texture
      idx+=1;
      offset.x += space * 2;
    }
    offset.x = x_starter;
    offset.y += space * 2;
  }

  this->tg.gen_indices(this->tg.get_rendered_quads());
  this->mesh_buffer.set_data(0, this->tg.get_vector().size() * sizeof(glm::vec2), this->tg.get());
  this->texture_positions_buffer.set_data(0, this->tg.get_vector_with_sprite().size() * sizeof(glm::vec2), this->tg.get_with_sprite());
  this->indices_buffer.set_data(0, this->tg.get_vector_with_indices_buffer().size(), this->tg.get_with_indices_buffer());

  LOG_DEBUG("We are rendering %d quads", this->tg.get_rendered_quads());
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

  this->hitbox.size = this->size; //fix this later

  //glDrawArrays(GL_TRIANGLES, 0, (max_vertex_counts * points_per_quad)); //if not using indices
  glDrawElements(GL_TRIANGLES, (max_vertex_counts * points_per_quad), GL_UNSIGNED_INT, nullptr);
  
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
  //test the functions
  //this->tg.update_quad(1, glm::vec2(-1.0f), 1.0f);
  this->tg.push_quad(0.1f, glm::vec2(2.0));
  LOG_DEBUG("We are rendering %d quads", this->tg.get_rendered_quads());
  this->mesh_buffer.set_data(0, this->tg.get_vector().size() * sizeof(glm::vec2), this->tg.get());
}

// std::vector<unsigned int> generateIndices(int quadCount) {
//   std::vector<unsigned int> indices(quadCount * 6);
//   for (int q = 0; q < quadCount; ++q) {
//     int base = 4 * q;
//     indices[q * 6 + 0] = base;
//     indices[q * 6 + 1] = base + 1;
//     indices[q * 6 + 2] = base + 2;
//     indices[q * 6 + 3] = base;
//     indices[q * 6 + 4] = base + 3;
//     indices[q * 6 + 5] = base + 2;
//   }
//   return indices;
// } //outdated func

//void push_quad(float size, float x, float y);
void Terrain_Generator::push_quad(float size, glm::vec2 pos) {
  float x = pos.x;
  float y = pos.y;

  this->data.push_back(glm::vec2(x - size, y - size));
  this->data.push_back(glm::vec2(x + size, y - size));
  this->data.push_back(glm::vec2(x + size, y + size));
  this->points += 3;

  this->data.push_back(glm::vec2(x - size, y + size));
  this->points += 1;
};

void Terrain_Generator::update_quad(unsigned int base, glm::vec2 pos, float size) {
  float x = pos.x;
  float y = pos.y;
  unsigned int i = base * 4; 
  if(base + 5 >= this->data.size()) {
    LOG_ERROR("Invalid location access!");
    return;
  }

  this->data[i + 0] = glm::vec2(x - size, y - size);
  this->data[i + 1] = glm::vec2(x + size, y - size);
  this->data[i + 2] = glm::vec2(x + size, y + size);

  this->data[i + 3] = glm::vec2(x - size, y + size);
}

void Terrain_Generator::pop_quad() {
  this->data.pop_back();
  this->data.pop_back();
  this->data.pop_back();

  this->data.pop_back();
}

glm::vec2* Terrain_Generator::get(void) const noexcept {
  return (glm::vec2*)this->data.data();
};

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

  this->data.push_back(glm::vec2(x - size, y + size));
  this->points += 1;

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
  
  // this->texture_pos.push_back(uv2); // tri 2, v0
  this->texture_pos.push_back(uv3); // tri 2, v1
  // this->texture_pos.push_back(uv0); // tri 2, v2
}

glm::vec2* Terrain_Generator::get_with_sprite(void) const noexcept {
  return (glm::vec2*)this->texture_pos.data();
}

const std::vector<glm::vec2>& Terrain_Generator::get_vector_with_sprite(void) const noexcept {
  return this->texture_pos;
};

unsigned int Terrain_Generator::get_rendered_quads(void) const noexcept {
  return (this->data.size() / 4);
};

void Terrain_Generator::gen_indices(int index) {
  this->indices.resize(index * 6);
  for (int q = 0; q < index; ++q) {
    int base = 4 * q;
    this->indices.at(q * 6 + 0) = base;
    this->indices.at(q * 6 + 1) = base + 1;
    this->indices.at(q * 6 + 2) = base + 2;
    this->indices.at(q * 6 + 3) = base;
    this->indices.at(q * 6 + 4) = base + 3;
    this->indices.at(q * 6 + 5) = base + 2;
  }
};

const std::vector<unsigned int>& Terrain_Generator::get_vector_with_indices_buffer(void) const noexcept {
  return this->indices;
};

unsigned int* Terrain_Generator::get_with_indices_buffer(void) const noexcept {
  return (unsigned int*)this->indices.data();
};
