#include "Player.hpp"

#undef def_as_ptr
#define def_as_ptr(name) typeof(this->name) *name = &this->name
#undef LOG_DEBUG
#define LOG_DEBUG(fmt, ...) std::printf("[DEBUG] " fmt "\n", ##__VA_ARGS__)
static float *zoom, *delta;
bool* can_zoom;

typedef struct matrices_struct {
  glm::mat4 projection;
  glm::mat4 view;
} matrices_struct;

void Player::create() {
  can_zoom = &m_can_zoom;
  def_as_ptr(vao);
  def_as_ptr(mesh_buffer);
  def_as_ptr(indices_buffer);
  def_as_ptr(matrices_buffer);
  def_as_ptr(texture);
  def_as_ptr(texture_positions_buffer);

  texture->create(std::string(GET_TEXTURES_PATH("character.png")),
                  GL_TEXTURE_2D, GL_RGBA, GL_RGBA);

  m_Vertex.Create(GET_SHADERS_PATH("main.vert.glsl"), GL_VERTEX_SHADER);
  m_Fragment.Create(GET_SHADERS_PATH("main.frag.glsl"), GL_FRAGMENT_SHADER);
  m_ProgramShader.CreateProgram(&m_Vertex, &m_Fragment);

  vao->CreateAndBind();
  this->mesh_data.push_back(
      (Vertex){.Position = glm::vec2(-this->size, -this->size)});
  this->mesh_data.push_back(
      (Vertex){.Position = glm::vec2(this->size, -this->size)});
  this->mesh_data.push_back(
      (Vertex){.Position = glm::vec2(this->size, this->size)});
  this->mesh_data.push_back(
      (Vertex){.Position = glm::vec2(-this->size, this->size)});

  this->texture_positions.push_back(
      (Vertex){.Position = glm::vec2(0.0f, 0.0f)});
  this->texture_positions.push_back(
      (Vertex){.Position = glm::vec2(1.0f, 0.0f)});
  this->texture_positions.push_back(
      (Vertex){.Position = glm::vec2(1.0f, 1.0f)});
  this->texture_positions.push_back(
      (Vertex){.Position = glm::vec2(0.0f, 1.0f)});

  unsigned int block_index =
      glGetUniformBlockIndex(m_ProgramShader.GetHandle(), "Matrices");
  glUniformBlockBinding(m_ProgramShader.GetHandle(), block_index, 0);
  //LOG_DEBUG("Works Fine?");

  matrices_buffer->Create(sizeof(CameraMatrices_t), nullptr, GL_DYNAMIC_DRAW,
                          GL_UNIFORM_BUFFER);
  matrices_buffer->Unbind();
  glBindBufferBase(GL_UNIFORM_BUFFER, 0, matrices_buffer->GetHandle());

  texture_positions_buffer->Create(
      this->texture_positions.size() * sizeof(Vertex),
      this->texture_positions.data(), GL_STATIC_DRAW, GL_ARRAY_BUFFER);
  vao->SetVertexAttrib(2, 2, GL_FLOAT, 2 * sizeof(float),
                                 (const void *)0);


  mesh_buffer->Create(this->mesh_data.size() * sizeof(Vertex),
                      this->mesh_data.data(), GL_STATIC_DRAW, GL_ARRAY_BUFFER);
  vao->SetVertexAttrib(0, 2, GL_FLOAT, sizeof(Vertex),
                                 (const void *)0);

  unsigned int indices[] = {0, 1, 2, 0, 3, 2};

  glUniform1i(glGetUniformLocation(m_ProgramShader.GetHandle(), "asset"), 0);

  texture_positions_buffer->Unbind();
  indices_buffer->Create(sizeof(indices), indices, GL_STATIC_DRAW,
                         GL_ELEMENT_ARRAY_BUFFER);

  indices_buffer->Unbind();
  mesh_buffer->Unbind();
  vao->Unbind();

  //this->speed = 0.01f;
  //this->position = glm::vec2((float)this->window->GetSize()->x/2.0f, (float)this->window->GetSize()->y/2.0f);
  m_Position = glm::vec2(0.0f, 232.0f);

  // this->camera_position = glm::vec3(this->position.x, 0.0f, this->cam_z);
  // this->target = glm::vec3(this->position.x, 0.0f, -1.0f);
  // this->up_vector = glm::vec3(0.0f, 1.0f, 0.0f);
  m_Camera.SetPosition(glm::vec3(m_Position.x, 0.0f, cam_z));
  m_Camera.SetLookAtTarget(glm::vec3(m_Position.x, 0.0f, -1.0f));
  m_Camera.Create();

  glfwSetScrollCallback(window->GetHandle(), (GLFWscrollfun)scroll_callback);
  zoom = &this->f_counter;
  delta = &this->delta_time;
  this->target = glm::vec3(0.0f, 0.0f, -1.0f);
  m_Velocity = glm::vec2(0.0f);
}

void Player::draw() {
  def_as_ptr(vao);
  def_as_ptr(indices_buffer);
  def_as_ptr(matrices_buffer);
  def_as_ptr(texture);

  m_ProgramShader.BindProgram();
  texture->bind_and_set_active(GL_TEXTURE1);
  vao->Bind();
  indices_buffer->Bind();

  this->move();
  m_Position += m_Velocity * delta_time;

  this->projection = glm::mat4(1.0f);
  //this->projection = glm::perspective(
      //glm::radians(*zoom), *this->window->get_aspect_ratio(), 0.1f, 100.0f);
  //this->projection = glm::ortho(-50.0f, 50.0f, -50.0f, 50.0f, 0.1f, 100.0f);


  float flAspect = *window->GetAspectRatio(); // width / height
  float flHalfHeight = 50.0f; // half of vertical view range
  
  float flLeft   = -flHalfHeight * flAspect;
  float flRight  =  flHalfHeight * flAspect;
  float flBottom = -flHalfHeight;
  float flTop    =  flHalfHeight;

  this->projection = glm::ortho(flLeft, flRight, flBottom, flTop, 0.1f, 100.0f);
  m_Camera.Update(flLeft, flBottom, flTop, flRight);

  this->view = glm::mat4(1.0f);
  //clip the camera ?
  // if(this->position.x >= 4.0f || this->position.x <= -4.0f || this->position.y >= 1.5f || this->position.y <= -1.5f) {
  //   this->view = glm::lookAt(this->camera_position, this->target, this->up_vector);
  //   this->camera_position = glm::vec3(this->position.x, this->position.y, this->cam_z);
  //   this->target = glm::vec3(this->position.x, this->position.y, -1.0f);
  //   this->up_vector = glm::vec3(0.0f, 1.0f, 0.0f);
  // }
  // this->view = glm::lookAt(this->camera_position, this->target, this->up_vector);
  // this->camera_position = glm::vec3(this->position.x, this->position.y, this->cam_z);
  // this->target = glm::vec3(this->position.x, this->position.y, -1.0f);
  // this->up_vector = glm::vec3(0.0f, 1.0f, 0.0f);

  m_Camera.SetPosition(glm::vec3(m_Position.x, m_Position.y, cam_z));
  m_Camera.SetLookAtTarget(glm::vec3(m_Position.x, m_Position.y, -1.0f));
  m_Camera.UpdateView();
  m_Camera.UpdateMatricesBuffer();

  unsigned int nPlayerPosLocation = glGetUniformLocation(m_ProgramShader.GetHandle(), "position");
  glUniform2f(nPlayerPosLocation, m_Position.x, m_Position.y);

  matrices_struct msturct;
  msturct.projection = this->projection;
  msturct.view = this->view;
  matrices_buffer->UpdateData(0, sizeof(CameraMatrices_t), m_Camera.GetMatrices());

  zoom = &this->f_counter;
  delta = &this->delta_time;

  hitbox.origin = this->m_Position;
  hitbox.size = this->size;
  hitbox.maximum = hitbox.origin + (this->size * 2);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  indices_buffer->Unbind();
  vao->Unbind();
  m_ProgramShader.UnbindProgram();
}

void Player::destroy() {
  def_as_ptr(vao);
  def_as_ptr(mesh_buffer);
  def_as_ptr(indices_buffer);

  m_ProgramShader.Destroy();
  vao->Destroy();
  mesh_buffer->Destroy();
  indices_buffer->Destroy();
}

void Player::move() {
  Window *window = this->window;

  bool bHasHorizontalInput = false;
  bool bIsOnGround = (m_Position.y <= 0.0f);

  if (window->is_key_pressed(GLFW_KEY_D)) {
    m_Velocity.x += m_flAcceleration * delta_time;
    bHasHorizontalInput = true;
  };
  if (window->is_key_pressed(GLFW_KEY_A)) {
    m_Velocity.x -= m_flAcceleration * delta_time;
    bHasHorizontalInput = true;
  };

  if(!bHasHorizontalInput) {
    m_Velocity.x = 0.0f;
  }

  if(m_Velocity.x > m_flMaxSpeedX) {
    m_Velocity.x = m_flMaxSpeedX;
  } else if(m_Velocity.x < -m_flMaxSpeedX) {
    m_Velocity.x = -m_flMaxSpeedX;
  }

  static bool sbWasSpacePressed = false;
  bool bIsSpacePressed = window->is_key_pressed(GLFW_KEY_SPACE);

  if(bIsSpacePressed && !sbWasSpacePressed && bIsOnGround) {
    m_Velocity.y = m_flJumpForce;
  }

  sbWasSpacePressed = bIsSpacePressed;
  m_Velocity.y += m_flGravity * delta_time;

  if(m_Position.y <= 0.0f && m_Velocity.y < 0) {
    m_Position.y = 0.0f;
    m_Velocity.y = 0.0f;
  }
}

void Player::set_window(Window *window) { this->window = window; }

void Player::set_delta_time(float *dt) { this->delta_time = *dt; }

glm::vec2 *Player::get_position() { return &this->m_Position; }

AABB_Hitbox *Player::get_hitbox() { return &this->hitbox; }

void scroll_callback(GLFWwindow *window, double xOffset, double yOffset) {
  if(*can_zoom == false) {
    return;
  }
  //135.0f
  const float max_zoom = 140.0f, min_zoom = 35.0f;
  const float zoom_strenght = 5.0f;//5.0f
  if ((float)yOffset >= 1.0f)
    *zoom -= zoom_strenght;
  if ((float)yOffset <= -1.0f) {
    *zoom += zoom_strenght;
  }

  if (*zoom <= min_zoom)
    *zoom = min_zoom;
  if (*zoom >= max_zoom)
    *zoom = max_zoom;
};

void Player::set_position(glm::vec2 pos) {
  this->m_Position = pos;
  glUniform2f(glGetUniformLocation(m_ProgramShader.GetHandle(), "position"), m_Position.x, m_Position.y);
}

void Player::set_x_pos(float x) {
  this->m_Position.x = x;
  glUniform2f(glGetUniformLocation(m_ProgramShader.GetHandle(), "position"), m_Position.x, m_Position.y);
}

void Player::set_y_pos(float y) {
  this->m_Position.y = y;
  glUniform2f(glGetUniformLocation(m_ProgramShader.GetHandle(), "position"), m_Position.x, m_Position.y);
}

float Player::get_x_pos() { return this->get_position()->x; }

float Player::get_y_pos() { return this->get_position()->y; }
void Player::reset_all_stats() {
  this->m_Position = glm::vec2(0.0f);
};
