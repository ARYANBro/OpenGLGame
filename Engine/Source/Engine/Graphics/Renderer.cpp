#include <Engine/Graphics/Renderer.h>

#include <Engine/Window.h>
#include <Engine/Graphics/VertexArray.h>
#include <Engine/Graphics/VertexBuffer.h>
#include <Engine/Graphics/IndexBuffer.h>
#include <Engine/Graphics/ShaderProgram.h>
#include <Engine/Debug.h>

#include <Windows.h>
#include <glad/glad.h>
#include <glad/glad_wgl.h>

#include <cassert>
#include <stdexcept>
#include <iostream>

static GLenum GetDrawMode(Engine::DrawMode drawMode) noexcept
{
    switch (drawMode)
    {
    case Engine::DrawMode::Triangles:
        return GL_TRIANGLES;

    case Engine::DrawMode::TriangleStrip:
        return GL_TRIANGLE_STRIP;
        break;

    default:
        assert(false);
        return -1;
    }
}

Engine::Renderer::Renderer(const Window& window)
{
    Initialize(window);
}

Engine::Renderer::~Renderer() noexcept
{
    wglDeleteContext(m_OpenGLCtxt);
}

void Engine::Renderer::Initialize(const Window& window)
{
    m_DeviceCtxt = GetDC(window.GetHandle());
     // Load GL and WGL functions using a temporary context
    {
        PIXELFORMATDESCRIPTOR pixelFormatDes = {};
        pixelFormatDes.nSize = sizeof(PIXELFORMATDESCRIPTOR);
        pixelFormatDes.nVersion = 1;
        pixelFormatDes.iPixelType = PFD_TYPE_RGBA;
        pixelFormatDes.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pixelFormatDes.cColorBits = 32;
        pixelFormatDes.cDepthBits = 8;
        pixelFormatDes.cStencilBits = 8;
        pixelFormatDes.iLayerType = PFD_MAIN_PLANE;

        auto pixelFormat = ChoosePixelFormat(m_DeviceCtxt, &pixelFormatDes);
        SetPixelFormat(m_DeviceCtxt, pixelFormat, &pixelFormatDes);
        
        HGLRC tempCtxt = wglCreateContext(m_DeviceCtxt);
        assert(tempCtxt);
        wglMakeCurrent(m_DeviceCtxt, tempCtxt);

        if (!gladLoadGL())
            throw FailedToLoadGL("Engine::Renderer::Renderer(const Window& window) | gladLoadGL() failed");

        if (!gladLoadWGL(m_DeviceCtxt))
            throw FailedToLoadWGL("Engine::Renderer::Renderer(const Window& window) | gladLoadWGL() failed");

        wglMakeCurrent(m_DeviceCtxt, 0);
        wglDeleteContext(tempCtxt);
    }

    // Create the actual context
    constexpr int pixelFormatAttributes[] = {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB, 32,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_STENCIL_BITS_ARB, 8,
		0
    };

    int pixelFormat = 0;
    UINT numFormats = 0;
    BOOL result = wglChoosePixelFormatARB(m_DeviceCtxt, pixelFormatAttributes, nullptr, 1, &pixelFormat, &numFormats);

    assert(result == TRUE);

    PIXELFORMATDESCRIPTOR pixelFormatDesc = {};
    DescribePixelFormat(m_DeviceCtxt, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pixelFormatDesc);
    SetPixelFormat(m_DeviceCtxt, pixelFormat, &pixelFormatDesc);

    constexpr int openGLAttribs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 6,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };

    m_OpenGLCtxt = wglCreateContextAttribsARB(m_DeviceCtxt, 0, openGLAttribs);
    assert(m_OpenGLCtxt);

    MakeContextCurrent();
    glEnable(GL_DEPTH_TEST);
}

void Engine::Renderer::MakeContextCurrent() const
{
    wglMakeCurrent(m_DeviceCtxt, m_OpenGLCtxt);
}

void Engine::Renderer::SetFaceCullingMode(Engine::FaceCullingMode faceCulling) const
{
    GLenum cullMode;
    switch (faceCulling)
    {
        case FaceCullingMode::Front:
            cullMode = GL_FRONT;
            break;
        
        case FaceCullingMode::Back:
            cullMode = GL_BACK;
            break;

        case FaceCullingMode::Both:
            cullMode = GL_FRONT_AND_BACK;
            break;
    }

    glCullFace(cullMode);
}

void Engine::Renderer::SetFaceWindingOrder(FaceWindingOrder windingOrder) const
{
    GLenum order;

    switch (windingOrder)
    {
        case FaceWindingOrder::Clockwise:
            order = GL_CW;
            break;
        case FaceWindingOrder::Anticlockwise:
            order = GL_CCW;
            break;
    }

    glFrontFace(order);
}

void Engine::Renderer::SwapBuffers(int vsync) const
{
    wglSwapIntervalEXT(vsync);
    wglSwapLayerBuffers(m_DeviceCtxt, WGL_SWAP_MAIN_PLANE);
}

void Engine::Renderer::Clear(const glm::vec4& clearColor) const
{
    glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::Renderer::SetViewport(const glm::ivec2& size) const
{
    glViewport(0, 0, size.x, size.y);
}

void Engine::Renderer::DrawArrays(const VertexArray& vertexArray, const ShaderProgram& shaderProgram, unsigned int offset, DrawMode drawMode) const
{
    shaderProgram.Bind();
    vertexArray.Bind();
    glDrawArrays(GetDrawMode(drawMode), offset, vertexArray.GetVertexBuffer(0).GetCount());
    vertexArray.Unbind();
    shaderProgram.Unbind();
}

void Engine::Renderer::DrawElements(const VertexArray& vertexArray, const ShaderProgram& shaderProgram, unsigned int offset, DrawMode drawMode) const
{
    shaderProgram.Bind();
    vertexArray.Bind();
    glDrawElements(GetDrawMode(drawMode), vertexArray.GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr);
    vertexArray.Unbind();
    shaderProgram.Unbind();
}