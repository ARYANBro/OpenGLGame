#include <Engine/MeshComponent.h>

#include <Engine/Graphics/VertexArray.h>
#include <Engine/Graphics/ShaderProgram.h>
#include <Engine/Graphics/VertexBuffer.h>
#include <Engine/Graphics/IndexBuffer.h>
#include <Engine/Graphics/Shader.h>
#include <Engine/Graphics/Texture.h>
#include <Engine/TransformComponent.h>
#include <Engine/Entity.h>

#include <Engine/Game.h>

std::shared_ptr<Engine::ShaderProgram> Engine::MeshComponent::s_GlobalShader = nullptr;

void Engine::MeshComponent::OnBegin()
{
    Component::OnBegin();
}

void Engine::MeshComponent::OnUpdate(const DeltaTime& deltaTime)
{
    Component::OnUpdate(deltaTime);
}

void Engine::MeshComponent::OnRender()
{
    // TODO: Accept textures in the rendering function as this should be handeled by the renderer
    // Bind the  textures before rendering the mesh
    for (int i = 0; i < m_CurrIndex; i++)
    {
        m_Textures[i]->Bind(i);
    }

    TransformComponent* transformComponent = m_Entity.GetComponent<TransformComponent>();
    if (transformComponent)
        m_Shader->SetMatrix4("u_Model", transformComponent->GetTransform());

    Game::Get().GetRenderer().DrawElements(*m_VertexArray, *m_Shader, 0);

    // Unbind after the rendering, since the other mesh will probably have some other textures
    for (int i = 0; i < m_CurrIndex; i++)
    {
        m_Textures[i]->Unbind();
    }
}

void Engine::MeshComponent::OnEnd()
{
    Component::OnEnd();
}

void Engine::MeshComponent::SetMesh(const MeshData& mesh)
{
    // Create and initialize vertex and index buffers
    auto vbo = std::make_shared<VertexBuffer>(/* data */ mesh.Verticies.data(), /* size */ mesh.Verticies.size() * sizeof(float), /* count */ mesh.Verticies.size());
    auto ibo = std::make_shared<IndexBuffer>(/* data */ mesh.Indicies.data(), /* size */ mesh.Indicies.size() * sizeof(unsigned int), /* count */ mesh.Indicies.size());

    // Set the vertex buffer

    // since there are only two attributes as of now position (3 floats) and texture coordinates (2 floats) so stride = 5 * sizeof(float)
    unsigned int bufferIdx = m_VertexArray->AddVertexBuffer(vbo, 0, 5 * sizeof(float));
    m_VertexArray->BindAttribute(0, bufferIdx);
    m_VertexArray->BindAttribute(1, bufferIdx);

    // Set the index buffer
    m_VertexArray->SetIndexBuffer(ibo);

    // We're expecting a specific format as of now
    std::list<VertexAttributeFormat> formats = {
        { 0, 3, VertexAttributeType::Float, false, 0 },
        { 1, 2, VertexAttributeType::Float, false, 3 * sizeof(float) }
    };

    m_VertexArray->SetAttributeFormats(formats);
}

void Engine::MeshComponent::AddTexture(const std::shared_ptr<Texture>& texture)
{
    if (m_CurrIndex > 15)
        throw TextureOverflow("A Maxium of only 16 textures can be added to a mesh");

    m_Textures[m_CurrIndex++] = texture;
}

Engine::MeshData Engine::MeshComponent::CreateCube() noexcept
{
    static const std::vector<float> s_Verticies = {
        // Front face               Texture Coords
        -0.5f, -0.5f, -0.5f,       0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,       0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,       1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,       1.0f, 0.0f,

        // Back face
        -0.5f, -0.5f, 0.5f,        0.0f, 0.0f,
        -0.5f,  0.5f, 0.5f,        0.0f, 1.0f,
         0.5f,  0.5f, 0.5f,        1.0f, 1.0f,
         0.5f, -0.5f, 0.5f,        1.0f, 0.0f,

        // Left face
        -0.5f, -0.5f,  0.5f,        0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,        0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,        1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,        1.0f, 0.0f,

        // Right face
        0.5f, -0.5f,  0.5f,        0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,        0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,        1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,        1.0f, 0.0f,

        // Top face
        -0.5f,  0.5f, -0.5f,        0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,        0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,        1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,        1.0f, 0.0f,

        // Down face
        -0.5f, -0.5f, -0.5f,        0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,        0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,        1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,        1.0f, 0.0f
    };

    static const std::vector<unsigned int> s_Indicies = {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    return { s_Verticies, s_Indicies };
}