#pragma once

#include "Component.h"

#include <memory>
#include <vector>
#include <array>

namespace Engine
{
    class DeltaTime;
    class VertexArray;
    class ShaderProgram;
    class Texture;

    struct MeshData
    {
        std::vector<float> Verticies;
        std::vector<unsigned int> Indicies;
    };

    class MeshComponent : public Component
    {
    public:
        MeshComponent(const class Entity& entity, const std::shared_ptr<VertexArray>& vertexArray = std::make_shared<VertexArray>(), const std::shared_ptr<ShaderProgram>& shader = nullptr)
            : Component(entity),
            m_VertexArray(vertexArray),
            m_Shader((shader == nullptr ? s_GlobalShader : shader))
        {
        }

        virtual void OnBegin() override;
        virtual void OnUpdate(const DeltaTime& DeltaTime) override;
        virtual void OnRender() override; 
        virtual void OnEnd() override;

        void SetMesh(const MeshData& meshData);
        void AddTexture(const std::shared_ptr<Texture>& texture);
        void SetShader(const std::shared_ptr<ShaderProgram>& shaderProgram) { m_Shader = shaderProgram; }
        static void SetDefaultShader(const std::shared_ptr<ShaderProgram>& shader) { s_GlobalShader = shader; }
        static MeshData CreateCube() noexcept;
    private:
        std::shared_ptr<VertexArray> m_VertexArray;
        std::shared_ptr<ShaderProgram> m_Shader;

        // OpenGL has at least sixteen slots
        std::array<std::shared_ptr<Texture>, 16> m_Textures;
        std::size_t m_CurrIndex = 0;

        // Use a global shader for all meshes for convenience, user still has the option to ovrride it
        static std::shared_ptr<ShaderProgram> s_GlobalShader;
    };
}
