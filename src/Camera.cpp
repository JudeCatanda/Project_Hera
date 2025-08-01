#include "Camera.hpp"

using glm::vec3, glm::ortho, glm::mat4, glm::lookAt;
const float kDefaultNear = 0.1f, kDefaultFar = 100.0f;

void CCamera::Create(void) {
    m_CamLookAtTarget = vec3(0.0f, 0.0f, -1.0f);
    m_CamUpVector = vec3(0.0f, 1.0f, 0.0f); //default up vector;
    m_ProjectionMatrix = mat4(1.0f);

    m_Matrices.projection = m_ProjectionMatrix;
    m_Matrices.view = m_ViewMatrix;
};

void CCamera::Update(float flLeft, float flBottom, float flTop, float flRight) {
    m_ProjectionMatrix = mat4(1.0f); //reset

    m_ProjectionMatrix = ortho(flLeft, flRight, flBottom, flTop, kDefaultNear, kDefaultFar); //use default near and far

    m_ViewMatrix = mat4(1.0f);
};

void CCamera::UpdateView(void) {
    m_ViewMatrix = lookAt(m_CamPosition, m_CamLookAtTarget, m_CamUpVector);
};

void CCamera::UpdateMatricesBuffer(void) {
    m_Matrices.projection = m_ProjectionMatrix;
    m_Matrices.view = m_ViewMatrix;
};
