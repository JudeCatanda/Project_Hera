#include "Player.hpp"

#undef LOG_DEBUG
#define LOG_DEBUG(fmt, ...) std::printf("[DEBUG] " fmt "\n", ##__VA_ARGS__)

void CPlayer::Create() {

  texture.create(std::string(GET_TEXTURES_PATH("character.png")),
                  GL_TEXTURE_2D, GL_RGBA, GL_RGBA);

  m_Vertex.Create(GET_SHADERS_PATH("main.vert.glsl"), GL_VERTEX_SHADER);
  m_Fragment.Create(GET_SHADERS_PATH("main.frag.glsl"), GL_FRAGMENT_SHADER);
  m_ProgramShader.CreateProgram(&m_Vertex, &m_Fragment);

  vao.CreateAndBind();
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

  matrices_buffer.Create(sizeof(CameraMatrices_t), nullptr, GL_DYNAMIC_DRAW,
                          GL_UNIFORM_BUFFER);
  matrices_buffer.Unbind();
  glBindBufferBase(GL_UNIFORM_BUFFER, 0, matrices_buffer.GetHandle());

  texture_positions_buffer.Create(
      this->texture_positions.size() * sizeof(Vertex),
      this->texture_positions.data(), GL_STATIC_DRAW, GL_ARRAY_BUFFER);
  vao.SetVertexAttrib(2, 2, GL_FLOAT, 2 * sizeof(float),
                                 (const void *)0);


  mesh_buffer.Create(this->mesh_data.size() * sizeof(Vertex),
                      this->mesh_data.data(), GL_STATIC_DRAW, GL_ARRAY_BUFFER);
  vao.SetVertexAttrib(0, 2, GL_FLOAT, sizeof(Vertex),
                                 (const void *)0);

  unsigned int indices[] = {0, 1, 2, 0, 3, 2};

  glUniform1i(glGetUniformLocation(m_ProgramShader.GetHandle(), "asset"), 0);

  texture_positions_buffer.Unbind();
  indices_buffer.Create(sizeof(indices), indices, GL_STATIC_DRAW,
                         GL_ELEMENT_ARRAY_BUFFER);

  indices_buffer.Unbind();
  mesh_buffer.Unbind();
  vao.Unbind();

  m_Position = glm::vec2(0.0f, 232.0f);

  m_Camera.SetPosition(glm::vec3(m_Position.x, 0.0f, DEFAULT_CAMERA_Z));
  m_Camera.SetLookAtTarget(glm::vec3(m_Position.x, 0.0f, -1.0f));
  m_Camera.Create();

  m_Hitbox = CreateHitbox(m_Position, size);

  m_Velocity = glm::vec2(0.0f);
}

void CPlayer::Draw() {

  m_ProgramShader.BindProgram();
  texture.bind_and_set_active(GL_TEXTURE1);
  vao.Bind();
  indices_buffer.Bind();

  move();
  m_Position += m_Velocity * m_flDeltaTime;
  m_Hitbox = CreateHitbox(m_Position, size);

  float flAspect = *m_Window->GetAspectRatio();
  float flHalfHeight = 80.0f;
  
  float flLeft   = -flHalfHeight * flAspect;
  float flRight  =  flHalfHeight * flAspect;
  float flBottom = -flHalfHeight;
  float flTop    =  flHalfHeight;

  m_Camera.Update(flLeft, flBottom, flTop, flRight);
  m_Camera.SetPosition(glm::vec3(m_Position.x, m_Position.y, DEFAULT_CAMERA_Z));
  m_Camera.SetLookAtTarget(glm::vec3(m_Position.x, m_Position.y, -1.0f));
  m_Camera.UpdateView();
  m_Camera.UpdateMatricesBuffer();

  matrices_buffer.UpdateData(0, sizeof(CameraMatrices_t), m_Camera.GetMatrices());

  unsigned int nPlayerPosLocation = glGetUniformLocation(m_ProgramShader.GetHandle(), "position");
  glUniform2f(nPlayerPosLocation, m_Position.x, m_Position.y);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  indices_buffer.Unbind();
  vao.Unbind();
  m_ProgramShader.UnbindProgram();
}

void CPlayer::Destroy() {
  m_ProgramShader.Destroy();
  vao.Destroy();
  mesh_buffer.Destroy();
  indices_buffer.Destroy();
}

void CPlayer::move() {
  bool bHasHorizontalInput = false;
  
  // Calculate potential horizontal velocity
  glm::vec2 potentialVelocity = m_Velocity;
  
  if (m_Window->is_key_pressed(GLFW_KEY_D)) {
    potentialVelocity.x += m_flAcceleration * m_flDeltaTime;
    bHasHorizontalInput = true;
  };
  if (m_Window->is_key_pressed(GLFW_KEY_A)) {
    potentialVelocity.x -= m_flAcceleration * m_flDeltaTime;
    bHasHorizontalInput = true;
  };
  if(!bHasHorizontalInput) {
    potentialVelocity.x = 0.0f;
  }
  if(potentialVelocity.x > m_flMaxSpeedX) {
    potentialVelocity.x = m_flMaxSpeedX;
  } else if(potentialVelocity.x < -m_flMaxSpeedX) {
    potentialVelocity.x = -m_flMaxSpeedX;
  }
  
  // Test horizontal movement only
  glm::vec2 testPosX = m_Position;
  testPosX.x += potentialVelocity.x * m_flDeltaTime;
  Hitbox testHitboxX = CreateHitbox(testPosX, size);
  
  if(!m_pCurrentGridLevel->IsColliding(testHitboxX)) {
    m_Velocity.x = potentialVelocity.x;
  } else {
    m_Velocity.x = 0.0f;
  }
  
  // Check if player is on ground (test small downward movement)
  glm::vec2 groundTestPos = m_Position;
  groundTestPos.y -= 0.1f; // Small downward test
  Hitbox groundTestHitbox = CreateHitbox(groundTestPos, size);
  bool bIsOnGround = m_pCurrentGridLevel->IsColliding(groundTestHitbox);
  
  static bool sbWasSpacePressed = false;
  bool bIsSpacePressed = m_Window->is_key_pressed(GLFW_KEY_SPACE);
  if(bIsSpacePressed && !sbWasSpacePressed && bIsOnGround) {
    m_Velocity.y += m_flJumpForce;
  }
  sbWasSpacePressed = bIsSpacePressed;
  
  // Apply gravity
  m_Velocity.y += m_flGravity * m_flDeltaTime;
  
  // Test vertical movement only
  glm::vec2 testPosY = m_Position;
  testPosY.y += m_Velocity.y * m_flDeltaTime;
  Hitbox testHitboxY = CreateHitbox(testPosY, size);
  
  if(m_pCurrentGridLevel->IsColliding(testHitboxY)) {
    m_Velocity.y = 0.0f;
  }
}

void CPlayer::SetPosition(glm::vec2 Position) {
  m_Position = Position;
  glUniform2f(glGetUniformLocation(m_ProgramShader.GetHandle(), "position"), m_Position.x, m_Position.y);
}
