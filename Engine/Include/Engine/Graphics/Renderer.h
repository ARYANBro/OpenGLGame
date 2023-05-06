#pragma once

#include <Windows.h>

#include <Engine/Math/MathTypes.h>

namespace Engine
{
    enum class DrawMode
    {
        Triangles,
        TriangleStrip
    };

    enum class FaceCullingMode
    {
        Front,
        Back,
        Both
    };

    enum class FaceWindingOrder
    {
        Clockwise,
        Anticlockwise
    };

    class Renderer
    {
    public:
        Renderer(const class Window& window);
        Renderer() noexcept = default;
        ~Renderer() noexcept;

        void Initialize(const Window& window);

        void MakeContextCurrent() const;
        void SetFaceCullingMode(FaceCullingMode faceCulling) const;
        void SetFaceWindingOrder(FaceWindingOrder windingOrder) const;
        void SwapBuffers(int vsync) const;
        void Clear(const struct Math::Vector4& clearColor) const;
        void SetViewport(const struct Math::Rectangle& size) const;

        void DrawArrays(const class VertexArray& vertexArray, const class ShaderProgram& shaderProgram, unsigned int offset, DrawMode mode = DrawMode::Triangles) const;
        void DrawElements(const class VertexArray& vertexArray, const class ShaderProgram& shaderProgram, unsigned int offset, DrawMode mode = DrawMode::Triangles) const;

    private:
        HGLRC m_OpenGLCtxt;
        HDC m_DeviceCtxt;
        
    };
}