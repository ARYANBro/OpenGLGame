#include <Engine/CameraEntity.h>

#include <glm/gtc/matrix_transform.hpp>

void Engine::CameraEntity::OnUpdate(const DeltaTime& deltaTime)
{
    glm::vec2 viewportSize = Game::Get().GetWindow().GetViewportSize();
    float aspectRatio = static_cast<float>(viewportSize.x) / viewportSize.y;

    switch (m_ProjectionType)
    {
        case ProjectionType::Prespective:
        {
            m_Projection = glm::perspective(glm::radians(m_FOV), aspectRatio, m_Near, m_Far);
            break;
        }
        case ProjectionType::Orthographic:
        {
            float left = 0.0f;
            float right = static_cast<float>(viewportSize.x);
            float bottom = 0.0f;
            float top = static_cast<float>(viewportSize.y);
            m_Projection = glm::ortho(left, right, bottom, top, m_Near, m_Far);
            break;
        }
        default:
            assert(false && "No ProjectionType");
    }

    m_Pitch = std::clamp(m_Pitch, -89.0f, 89.0f);
    m_Forward.x = std::cos(glm::radians(m_Yaw)) * std::cos(glm::radians(m_Pitch));
    m_Forward.y = std::sin(glm::radians(m_Pitch));
    m_Forward.z = std::sin(glm::radians(m_Yaw)) * std::cos(glm::radians(m_Pitch));

    m_View = glm::lookAt(m_Position, m_Position + m_Forward, glm::vec3(0.0f, 1.0f, 0.0f));

    m_Right.x = m_View[0][0];
    m_Right.y = m_View[1][0];
    m_Right.z = m_View[2][0];

    m_Up.x = m_View[0][1];
    m_Up.y = m_View[1][1];
    m_Up.z = m_View[2][1];
}
