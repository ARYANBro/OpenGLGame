#include <Engine/TransformComponent.h>

#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Engine::TransformComponent::GetTransform()
{
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), m_Translation);
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_Scale);
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), m_Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        rotation = glm::rotate(rotation, m_Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        rotation = glm::rotate(rotation, m_Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

        // return scale * rotation * translation;
        return translation * rotation * scale;
}