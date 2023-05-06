#include <Game3D.h>

#include <Engine/DeltaTime.h>
#include <Engine/Debug.h>
#include <Engine/Entity.h>
#include <Engine/Graphics/Buffer.h>
#include <Engine/Graphics/Shader.h>
#include <Engine/Graphics/VertexArray.h>
#include <Engine/Graphics/IndexBuffer.h>
#include <Engine/Graphics/VertexBuffer.h>
#include <Engine/Graphics/UniformBuffer.h>
#include <Engine/Graphics/ShaderProgram.h>
#include <Engine/Math/Vector.h>
#include <Engine/Math/Rectangle.h>
#include <Engine/Math/Matrix4.h>
#include <Engine/Math/Utility.h>
#include <Engine/Component.h>
#include <Engine/TransformComponent.h>
#include <Engine/Graphics/Texture.h>

void Game3D::OnBegin()
{
    Game::OnBegin();

    try
    {
        // Setting the global shader for the mesh to use
        Engine::Shader vertShader(Engine::ShaderType::VertexShader);
        Engine::Shader fragShader(Engine::ShaderType::FragmentShader);
        fragShader.SetSourceCode("../../Assets/Shaders/BasicShader/BasicShader.frag");
        vertShader.SetSourceCode("../../Assets/Shaders/BasicShader/BasicShader.vert");

        auto shader = std::make_shared<Engine::ShaderProgram>();
        shader->AttachShader(fragShader);
        shader->AttachShader(vertShader);
        shader->Link();
        Engine::MeshComponent::SetDefaultShader(shader);

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

    try
    {
        Math::Rectangle viewPortSize = GetWindow().GetViewportSize();
        Math::Matrix4 projection;

        float aspectRatio = viewPortSize.Height / static_cast<float>(viewPortSize.Width);
        projection.SetPrespective(aspectRatio, Math::DegToRad(90), 0.01f, 1000.0f);
        m_UBO->SetData(/* data */ &projection, /* size */ sizeof(projection));
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
