#include <Sandbox.h>

#include <Engine/DeltaTime.h>
#include <Engine/Entity.h>
#include <Engine/TransformComponent.h>
#include <Engine/MeshComponent.h>
#include <Engine/Graphics/Texture.h>
#include <Engine/ConsoleLogger.h>

void Sandbox::OnBegin()
{
    Game3D::OnBegin();

    SetLogger<Engine::ConsoleLogger>();

    // Initialize textures
    std::shared_ptr<Engine::Texture> texture = std::make_shared<Engine::Texture>();
    texture->Load("C:\\Users\\nalin\\OneDrive\\Documents\\Projects\\OpenGLGame\\Assets\\Textures\\Kenny Textures\\Purple\\texture_05.png");

    // Create and initialize components
    m_Entity = GetWorld().CreateEntity<Engine::Entity>();
    m_Entity->AddComponent<Engine::TransformComponent>();
    Engine::MeshComponent* mesh = m_Entity->AddComponent<Engine::MeshComponent>();
    mesh->SetMesh(Engine::MeshComponent::CreateCube());
    mesh->AddTexture(texture);

    m_Entity2 = GetWorld().CreateEntity<Engine::Entity>();
    auto transform = m_Entity2->AddComponent<Engine::TransformComponent>();
    mesh = m_Entity2->AddComponent<Engine::MeshComponent>();
    mesh->SetMesh(Engine::MeshComponent::CreateCube());
    mesh->AddTexture(texture);

    m_Entity3 = GetWorld().CreateEntity<Engine::Entity>();
    transform = m_Entity3->AddComponent<Engine::TransformComponent>();
    mesh = m_Entity3->AddComponent<Engine::MeshComponent>();
    mesh->SetMesh(Engine::MeshComponent::CreateCube());
    mesh->AddTexture(texture);
    transform->SetTranslation({ 0.0f, 0.0f, 10.0f });
}

void Sandbox::OnUpdate(const Engine::DeltaTime& deltaTime)
{
    Game3D::OnUpdate(deltaTime);

    m_ElapsedSeconds += deltaTime;

    m_Scale += (22.0f / 7.0f) * 0.5f * deltaTime;
    float currScale = (std::sin(m_Scale) + 3.0f) * 0.25f; 

    Engine::TransformComponent* transform = m_Entity->GetComponent<Engine::TransformComponent>();
    transform->SetScale(glm::vec3{ 1.0f });
    transform->SetRotation({ m_RotationX, m_RotationY, m_RotationZ });
    transform->SetTranslation({ m_LocationX, 0.0f, m_LocationZ });

    transform = m_Entity2->GetComponent<Engine::TransformComponent>();
    transform->SetScale(glm::vec3{ 1.0f });
    transform->SetRotation({ m_RotationX, m_RotationY, m_RotationZ });
    transform->SetTranslation({ 1.0f, 0.0f, m_LocationZ });
}

void Sandbox::OnEnd()
{
    Game3D::OnEnd();
}

void Sandbox::OnKeyDown(int key)
{
    Game3D::OnKeyDown(key);
}

void Sandbox::OnKeyUp(int key)
{
    Game3D::OnKeyUp(key);
}

void Sandbox::OnMouseMove(const glm::vec2& deltaMouse)
{
    Game3D::OnMouseMove(deltaMouse);
}