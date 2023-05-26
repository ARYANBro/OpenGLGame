#pragma once

#include <Windows.h>

#include <stdexcept>
#include <glm/glm.hpp>

namespace Engine
{
    class FailedToLoadGL : public std::runtime_error
    {
    public:
        FailedToLoadGL(const std::string& what) : std::runtime_error(what) {}
        FailedToLoadGL(const char* what) : std::runtime_error(what) {}
    };

    class FailedToLoadWGL : public std::runtime_error
    {
    public:
        FailedToLoadWGL(const std::string& what) : std::runtime_error(what) {}
        FailedToLoadWGL(const char* what) : std::runtime_error(what) {}
    };

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
        void Clear(const glm::vec4& clearColor) const;
        void SetViewport(const glm::ivec2& vec2) const;

        void DrawArrays(const class VertexArray& vertexArray, const class ShaderProgram& shaderProgram, unsigned int offset, DrawMode mode = DrawMode::Triangles) const;
        void DrawElements(const class VertexArray& vertexArray, const class ShaderProgram& shaderProgram, unsigned int offset, DrawMode mode = DrawMode::Triangles) const;

    private:
        HGLRC m_OpenGLCtxt;
        HDC m_DeviceCtxt;
        
    };
}