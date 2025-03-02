#include "Player.hpp"

#undef def_as_ptr
#define def_as_ptr(name) typeof(this->name)* name = &this->name
#undef LOG_DEBUG
#define LOG_DEBUG(fmt, ...) std::printf("[DEBUG] " fmt "\n", ##__VA_ARGS__)
static float* zoom, *delta;

typedef struct matrices_struct {
  glm::mat4 projection;
  glm::mat4 view;
} matrices_struct;

void Player::create() {
  def_as_ptr(vertex);
  def_as_ptr(fragment);
  def_as_ptr(program);
  def_as_ptr(vao);
  def_as_ptr(mesh_buffer);
  def_as_ptr(indices_buffer);
  def_as_ptr(matrices_buffer);
  def_as_ptr(texture);
  def_as_ptr(texture_positions_buffer);

  texture->create(std::string(GET_TEXTURES_PATH("character.png")), GL_TEXTURE_2D, GL_RGBA, GL_RGBA);

  vertex->create(GET_SHADERS_PATH("main.vert.glsl"), GL_VERTEX_SHADER);
  fragment->create(GET_SHADERS_PATH("main.frag.glsl"), GL_FRAGMENT_SHADER);
  program->create(vertex, fragment);

  vao->create_and_bind();
  this->mesh_data.push_back((Vertex){ .Position = glm::vec2( -this->size, -this->size ) });
  this->mesh_data.push_back((Vertex){ .Position = glm::vec2(  this->size, -this->size ) });
  this->mesh_data.push_back((Vertex){ .Position = glm::vec2(  this->size,  this->size ) });
  this->mesh_data.push_back((Vertex){ .Position = glm::vec2( -this->size,  this->size ) });

  this->texture_positions.push_back((Vertex){ .Position = glm::vec2(0.0f, 0.0f) });
  this->texture_positions.push_back((Vertex){ .Position = glm::vec2(1.0f, 0.0f) });
  this->texture_positions.push_back((Vertex){ .Position = glm::vec2(1.0f, 1.0f) });
  this->texture_positions.push_back((Vertex){ .Position = glm::vec2(0.0f, 1.0f) });

  unsigned int block_index = glGetUniformBlockIndex(program->get_handle(), "Matrices");
  glUniformBlockBinding(program->get_handle(), block_index, 0);

  matrices_buffer->create(sizeof(matrices_struct), nullptr, GL_DYNAMIC_DRAW, GL_UNIFORM_BUFFER);
  matrices_buffer->unbind();
  glBindBufferBase(GL_UNIFORM_BUFFER, 0, matrices_buffer->get_handle());

  texture_positions_buffer->create(this->texture_positions.size() * sizeof(Vertex), this->texture_positions.data(), GL_STATIC_DRAW, GL_ARRAY_BUFFER);
  vao->enable_and_set_attrib_ptr(2, 2, GL_FLOAT, sizeof(Vertex), (const void*)0);

  mesh_buffer->create(this->mesh_data.size() * sizeof(Vertex), this->mesh_data.data(), GL_STATIC_DRAW, GL_ARRAY_BUFFER);
  vao->enable_and_set_attrib_ptr(0, 2, GL_FLOAT, sizeof(Vertex), (const void*)0);

  unsigned int indices[] = {
    0, 1, 2,
    0, 3, 2
  };

  glUniform1i(glGetUniformLocation(program->get_handle(), "asset"), 0);

  texture_positions_buffer->unbind();
  indices_buffer->create(sizeof(indices), indices, GL_STATIC_DRAW, GL_ELEMENT_ARRAY_BUFFER);

  indices_buffer->unbind();
  mesh_buffer->unbind();
  vao->unbind();

  this->speed = 0.001f; //implicit
  this->velocity = glm::vec2(0.0f, 0.0f);
  this->position = glm::vec2(0.0f, 0.0f);

  this->camera_position = glm::vec3(0.0f, 0.0f, this->cam_z);
  this->target = glm::vec3(0.0f, 0.0f, -1.0f);
  this->up_vector = glm::vec3(0.0f, 1.0f, 0.0f);

  glfwSetScrollCallback(window->get_handle(),  (GLFWscrollfun)scroll_callback);
  zoom = &this->f_counter;
  delta = &this->delta_time;
}

void Player::draw() {
  def_as_ptr(program);
  def_as_ptr(vao);
  def_as_ptr(indices_buffer);
  def_as_ptr(matrices_buffer);
  def_as_ptr(texture);
  
  program->bind();
  texture->bind_and_set_active(GL_TEXTURE0);
  vao->bind();
  indices_buffer->bind();
  
  this->move();
  this->projection = glm::mat4(1.0f);
  if(!glfwGetWindowAttrib(window->get_handle(), GLFW_FOCUSED)) {
    this->destroy();
    return;
  };
  this->projection = glm::perspective(glm::radians(*zoom), *this->window->get_aspect_ratio(), 0.1f, 100.0f);
  this->view = glm::mat4(1.0f);
  this->camera_position = glm::vec3(this->position.x, 0.0f, this->cam_z);
  this->target = glm::vec3(this->position.x, 0.0f, -1.0f);
  this->view = glm::lookAt(this->camera_position, this->target, this->up_vector);
  
  program->send_uniform_float2("position", this->position.x, this->position.y);
  
  matrices_struct msturct;
  msturct.projection = this->projection;
  msturct.view = this->view;
  matrices_buffer->set_data(0, sizeof(matrices_struct), &msturct);

  zoom = &this->f_counter;
  delta = &this->delta_time;

  hitbox.origin = this->position;
  hitbox.size = this->size;
  hitbox.maximum = hitbox.origin + (this->size * 2);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  indices_buffer->unbind();
  vao->unbind();
  program->unbind();
}

void Player::destroy() {
  def_as_ptr(program);
  def_as_ptr(vao);
  def_as_ptr(mesh_buffer);
  def_as_ptr(indices_buffer);

  program->destroy();
  vao->destroy();
  mesh_buffer->destroy();
  indices_buffer->destroy();
}

void Player::move() {
  Window* window = this->window;
  
  this->horizontal_input_vector = 0.0f;
  if(window->is_key_pressed(GLFW_KEY_D)) {
    // this->velocity.x += this->speed;
    this->horizontal_input_vector += 1.0f;
  };
  if(window->is_key_pressed(GLFW_KEY_A)) {
    // this->velocity.x -= this->speed;
    this->horizontal_input_vector -= 1.0f;
  };
  if(!this->can_jump) {
    this->velocity.y -= this->gravity * this->delta_time;
  }
  if(window->is_key_pressed(GLFW_KEY_SPACE) && this->can_jump) {
    this->velocity.y += this->gravity * this->delta_time;
  }
  // LOG_DEBUG("Horizontal Input = %10.f", this->horizontal_input_vector);

  if(!disable_physics)
    this->process_physics();
}

void Player::process_physics() {
  this->position.x += this->velocity.x;// * this->delta_time;
  this->position.y += this->velocity.y * this->delta_time;

  if(this->position.y <= this->falling_point) { //if the player is in the window and not at the maximum y (max size of window->y) then fall
    this->position.y = this->falling_point;//  + this->size;
    this->velocity.y = 0.0f;
    this->can_jump = true;
  }
  if(this->position.y + this->size > this->max_jump_height)
    this->can_jump = false;
  
  this->velocity.x = this->horizontal_input_vector * this->speed;
}

void Player::set_window(Window *window) {
  this->window = window;
}

void Player::set_delta_time(float *dt) {
  this->delta_time = *dt;
}

glm::vec2 *Player::get_position() {
  return &this->position;
}

AABB_Hitbox *Player::get_hitbox() {
  return &this->hitbox;
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset) {
  const float max_zoom = 135.0f, min_zoom = 35.0f;
  const float zoom_strenght = 5.0f;
  if((float)yOffset >= 1.0f)
  *zoom -= zoom_strenght;
  if((float)yOffset <= -1.0f) {
    *zoom += zoom_strenght;
  }
  if(*zoom <= min_zoom)
  *zoom = min_zoom;
  if(*zoom >= max_zoom)
  *zoom  = max_zoom;
};
void Player::set_velocity(glm::vec2 velc) {
  this->velocity = velc;
}

void Player::set_position(glm::vec2 pos) {
  this->position = pos;
  this->program.send_uniform_float2("position", this->position.x, this->position.y);
}

void Player::set_falling_point(float y) {
  this->falling_point = y;
}

void Player::set_x_pos(float x) {
  this->position.x = x;
  this->program.send_uniform_float2("position", this->position.x, this->position.y);
}

void Player::set_y_pos(float y) {
  this->position.y = y;
  this->program.send_uniform_float2("position", this->position.x, this->position.y);
}

glm::vec2 Player::get_velocity() {
  return this->velocity;
}

float Player::get_x_pos() {
  return this->get_position()->x;
}

float Player::get_y_pos() {
  return this->get_position()->y;
}
