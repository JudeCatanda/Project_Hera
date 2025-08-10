#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/ext.hpp>
#include <vector>
#include <array>

#include "Shader.hpp"
#include "Layout.hpp"
#include "Buffer.hpp"
#include "Window.hpp"
#include "Texture.hpp"
#include "AABB.hpp"
#include "Camera.hpp"
#include "Terrain.hpp"

class CPlayer {
private:
  /* OPENGL RELATED MEMBERS */
  CWindow* m_Window;
  CShader m_Vertex, m_Fragment;
  CShaderProgram m_ProgramShader;
  CLayout vao;
  Buffer mesh_buffer, indices_buffer, matrices_buffer, texture_positions_buffer;
  Texture texture;
  std::vector<Vertex> mesh_data;
  std::vector<Vertex> texture_positions;

  float size = 8.0f;

  float m_flDeltaTime;

  //PHYSICS BASED MEMBERS
  glm::vec2 m_Position;
  glm::vec2 m_Velocity;
  float m_flAcceleration = 32.0f;
  float m_flJumpForce = 200.0f;
  float m_flGravity = -300.0f;
  const float m_flMaxSpeedX = 128.0f;
  Hitbox m_Hitbox;

  CCamera m_Camera;

  CGridMap* m_pCurrentGridLevel;

  void move();
public:
  CPlayer() = default;
  void                            Create();
  void                            Draw();
  void                            Destroy();

  void                            SetWindow(CWindow* Window) { m_Window = Window; } //we are fucked if nullptr
  void                            SetDeltaTime(float* flDeltaTime) { m_flDeltaTime = *flDeltaTime; }
  void                            SetPosition(glm::vec2 Position);
  void                            SetCurrentGridLevel(CGridMap& Gridmap) noexcept { m_pCurrentGridLevel = &Gridmap; };
  
  glm::vec2                       GetPosition() const { return m_Position; }
  CGridMap*                       GetCurrentGridLevel(void) const noexcept { return m_pCurrentGridLevel; };
};
