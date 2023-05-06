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
}

void Sandbox::OnUpdate(const Engine::DeltaTime& deltaTime)
{
    Game3D::OnUpdate(deltaTime);

    m_ElapsedSeconds += deltaTime;

    m_Scale += (22.0f / 7.0f) * 0.5f * deltaTime;
    float currScale = (std::sin(m_Scale) + 3.0f) * 0.25f; 

    Engine::TransformComponent* transform = m_Entity->GetComponent<Engine::TransformComponent>();
    transform->SetScale({ 1.0f });
    transform->SetRotation({ m_RotationX, m_RotationY, m_RotationZ });
    transform->SetTranslation({ m_LocationX, 0.0f, m_LocationZ });

    transform = m_Entity2->GetComponent<Engine::TransformComponent>();
    transform->SetScale({ 1.0f });
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

    const Engine::DeltaTime& deltaTime = GetDeltaTime();

    if (key == 'W')
    {
        m_RotationX -= deltaTime * 2;
        PRINT_INFO("Pressed Key: W");
    }
    else if (key == 'A')
    {
        m_LocationX -= deltaTime * 2;
        PRINT_INFO("Pressed Key: A");
    }
    else if (key == 'S')
    {
        m_RotationX += deltaTime * 2;
        PRINT_INFO("Pressed Key: S");
    }
    else if (key == 'D')
    {
        m_LocationX += deltaTime * 2;
        PRINT_INFO("Pressed Key: D");
    }
    else if (key == 'Q')
    {
        m_LocationZ -= deltaTime * 2;
    }
    else if (key == 'E')
    {
        m_LocationZ += deltaTime * 2;
    }
}

void Sandbox::OnKeyUp(int key)
{
    Game3D::OnKeyUp(key);

    if (key == 'W')
    {
        PRINT_INFO("Pressed Released: W");
    }
    else if (key == 'A')
    {
        PRINT_INFO("Pressed Released: A");
    }
    else if (key == 'S')
    {
        PRINT_INFO("Pressed Released: S");
    }
    else if (key == 'D')
    {
        PRINT_INFO("Pressed Released: D");
    }
}

void Sandbox::OnMouseMove(const Math::Vector2& deltaMousePos)
{
    Game3D::OnMouseMove(deltaMousePos);

    m_RotationX -= deltaMousePos.Y * GetDeltaTime() * 0.35f;
    m_RotationY -= deltaMousePos.X * GetDeltaTime() * 0.35f;
}