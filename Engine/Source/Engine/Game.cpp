#include  <Engine/Game.h>

#include <Engine/Window.h>
#include <Engine/Graphics/Renderer.h>
#include <Engine/Graphics/VertexArray.h>
#include <Engine/Graphics/IndexBuffer.h>
#include <Engine/Graphics/VertexBuffer.h>
#include <Engine/Graphics/UniformBuffer.h>
#include <Engine/Graphics/ShaderProgram.h>
#include <Engine/Graphics/Shader.h>
#include <Engine/Debug.h>
#include <Engine/Entity.h>
#include <Engine/Logger.h>
#include <Engine/FileLogger.h>

#include <glad/glad.h>

#include <Windows.h>

#include <iostream>
#include <cassert>

Engine::Game* Engine::Game::s_Game = nullptr;

Engine::Game::Game()
try
{
    s_Game = this;

    m_Window.Init(L"OpenGL Game Window", 1280, 720);
    m_Renderer.Initialize(m_Window);
    m_InputSystem.AddListener(this);
    m_Logger = std::make_unique<FileLogger>("OpenGLGame.log");
}
catch (const std::exception& e)
{
    PRINT_ERROR(e.what())
    throw;
}

Engine::Game::~Game() noexcept
{
    m_InputSystem.RemoveListener(this);
}

void Engine::Game::OnBegin()
{
    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    const GLubyte* shadingLangV = glGetString(GL_SHADING_LANGUAGE_VERSION);

    PRINT_INFO(std::string("Vendor: ") + reinterpret_cast<const char*>(vendor));
    PRINT_INFO(std::string("Renderer: ") + reinterpret_cast<const char*>(renderer));
    PRINT_INFO(std::string("Version: ") + reinterpret_cast<const char*>(version));
    PRINT_INFO(std::string("Shading Language Version: ") + reinterpret_cast<const char*>(shadingLangV));

    m_World.OnBegin();
}

void Engine::Game::OnUpdate(const DeltaTime& deltaTime)
{
    m_InputSystem.Update();
    m_World.Update(deltaTime);
}

void Engine::Game::OnRender()
{
    m_World.OnRender();
}

void Engine::Game::OnEnd()
{
    m_World.OnEnd();
}

void Engine::Game::Run()
{
    OnBegin();

    MSG msg;
    // Game loop
    while (m_IsRunning)
    {

        if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
               m_IsRunning = false; 

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        m_DeltaTime.UpdateDeltaTime();
        OnUpdate(m_DeltaTime);

        BeginRender();
        OnRender();
        EndRender();
    }

    OnEnd();
}

void Engine::Game::Quit()
{
    m_IsRunning = false;
}

void Engine::Game::BeginRender()
{
    GetRenderer().SetViewport(GetWindow().GetViewportSize());
    GetRenderer().Clear({ 0.05f, 0.05f, 0.055f, 1.0f });
    GetRenderer().SetFaceCullingMode(Engine::FaceCullingMode::Back);
}

void Engine::Game::EndRender()
{
    GetRenderer().SwapBuffers(1);
}
