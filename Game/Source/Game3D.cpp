#include <Game3D.h>

#include <Engine/DeltaTime.h>
#include <Engine/Debug.h>
#include <Engine/Entity.h>
#include <Engine/Graphics/Shader.h>
#include <Engine/Graphics/UniformBuffer.h>
#include <Engine/Graphics/ShaderProgram.h>
#include <Engine/Component.h>
#include <Engine/Graphics/Texture.h>
#include <Engine/ConsoleLogger.h>
#include <Engine/Debug.h>
#include <Engine/CameraEntity.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void Game3D::OnBegin()
{
    Game::OnBegin();

    SetLogger<Engine::ConsoleLogger>();

    try
    {
        // Creating the camera entity and customizing params
        m_Camera = GetWorld().CreateEntity<Engine::CameraEntity>();
        m_Camera->SetPosition({ -1.0f, 2.0f, -2.0f });
        m_Camera->SetYaw(65.0f);
        m_Camera->SetPitch(-25.0f);

        // Setting the global shader for the mesh to use
        Engine::Shader vertShader(Engine::ShaderType::VertexShader);
        Engine::Shader fragShader(Engine::ShaderType::FragmentShader);
        fragShader.SetSourceCode("../../Assets/Shaders/BasicShader/BasicShader.frag");
        vertShader.SetSourceCode("../../Assets/Shaders/BasicShader/BasicShader.vert");

        // Creating the default shader
        auto shaderProgram = std::make_shared<Engine::ShaderProgram>();
        shaderProgram->AttachShader(fragShader);
        shaderProgram->AttachShader(vertShader);
        shaderProgram->Link();
        Engine::MeshComponent::SetDefaultShader(shaderProgram);

        m_UBO = std::make_shared<Engine::UniformBuffer>();
        m_UBO->Bind(0);
    }
    catch (const std::runtime_error& e)
    {
        PRINT_ERROR(e.what());
        throw;
    }
}

void Game3D::OnUpdate(const Engine::DeltaTime& deltaTime)
{
    Game::OnUpdate(deltaTime);

    m_ElapsedTime += deltaTime;

    try
    {
        // Send the projection and view data to the ubo
        struct UBOData
        {
            glm::mat4 projection;
            glm::mat4 view;
        };

        UBOData uboData;
        uboData.projection = m_Camera->GetProjection();
        uboData.view = m_Camera->GetView();
        m_UBO->SetData(/* data */ &uboData, /* size */ sizeof(UBOData));
    }
    catch (const std::invalid_argument& e)
    {
        PRINT_ERROR(e.what());
        throw;
    }
    catch (const std::runtime_error& e)
    {
        PRINT_ERROR(e.what());
        throw;
    }
}

void Game3D::OnEnd()
{  
    Game::OnEnd();
}

// Update the view matrix based on W, A, S, D keys
void Game3D::OnKeyDown(int key)
{
    switch (key)
    {
        // Move forward
        case 'W':
            m_Camera->AddPosition(m_Camera->GetForward() * m_Camera->GetSpeed() * static_cast<float>(GetDeltaTime()));
            break;

        // Move backward
        case 'S':
            m_Camera->AddPosition(-m_Camera->GetForward() * m_Camera->GetSpeed() * static_cast<float>(GetDeltaTime()));
            break;

        // Move right
        case 'D':
            m_Camera->AddPosition(m_Camera->GetRight() * m_Camera->GetSpeed() * static_cast<float>(GetDeltaTime()));
            break;

        // Move left
        case 'A':
            m_Camera->AddPosition(-m_Camera->GetRight() * m_Camera->GetSpeed() * static_cast<float>(GetDeltaTime()));
            break;

        // Move up
        case 'Q':
            m_Camera->AddPosition(-m_Camera->GetUp() * m_Camera->GetSpeed() * static_cast<float>(GetDeltaTime()));
            break;

        // Move down
        case 'E':
            m_Camera->AddPosition(m_Camera->GetUp() * m_Camera->GetSpeed() * static_cast<float>(GetDeltaTime()));
            break;

        default:
            break;
    }
}

void Game3D::OnMouseMove(const glm::vec2& deltaMousePos)
{
    // Update the yaw and the pitch based on the delta mouse movement
    if (m_RightMouseDown)
    {
        m_Camera->AddYaw(deltaMousePos.x * m_Camera->GetSensitivity());
        m_Camera->AddPitch(-(deltaMousePos.y * m_Camera->GetSensitivity()));
    }
}

void Game3D::OnMouseDown(Engine::MouseButton button)
{
    if (button == Engine::MouseButton::Right)
        m_RightMouseDown = true;
}

void Game3D::OnMouseUp(Engine::MouseButton button)
{
    if (button == Engine::MouseButton::Right)
        m_RightMouseDown = false;   
}