#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/ext.hpp>

#include "Window.hpp"


struct CameraMatrices_t { //memory layout for shader!
  glm::mat4 projection;
  glm::mat4 view;
};

class CCamera {
private:
    glm::mat4 m_ViewMatrix, m_ProjectionMatrix;
    glm::vec3 m_CamPosition, m_CamUpVector, m_CamLookAtTarget;
    float m_flAspectRatio;
    CameraMatrices_t m_Matrices;
public:
    CCamera() = default;

    void                Create(float flTop, float flRight);
    void                SetAspectRatio(float flAspectRatio) { m_flAspectRatio = flAspectRatio; };
    glm::mat4           GetMatrix(void) const { return m_ViewMatrix * m_ProjectionMatrix; };
    CameraMatrices_t*   GetMatrices(void) { return &m_Matrices; }; //returns the m_Matrices (for ubo)
};
