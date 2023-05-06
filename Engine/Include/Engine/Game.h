#pragma once

#include "Math/MathTypes.h"
#include "Window.h"
#include "World.h"
#include "Graphics/Renderer.h"
#include "InputListener.h"
#include "InputSystem.h"
#include "DeltaTime.h"

#include <memory>

namespace Engine
{
    class Logger;

    class Game : public InputListener
    {
    public:
        Game();
        ~Game() noexcept;

        virtual void OnBegin();
        virtual void OnUpdate(const class DeltaTime& deltaTime);
        virtual void OnRender();
        virtual void OnEnd();

        void Run();
        void Quit();

        virtual void OnKeyDown(int key) override {}
        virtual void OnKeyUp(int key) override {}
        virtual void OnMouseMove(const Math::Vector2& deltaMousePos) {}

        template<typename LoggerType, typename... Args>
        void SetLogger(Args&&... args) { m_Logger.reset(new LoggerType(std::forward<Args>(args)... )); }
        const Logger& GetLogger() const noexcept { return *m_Logger; }
        const Renderer& GetRenderer() const noexcept { return m_Renderer; }
        const Window& GetWindow() const noexcept { return m_Window; }
        const World& GetWorld() const noexcept { return m_World; }
        const InputSystem& GetInputSystem() const noexcept { return m_InputSystem; }
        const DeltaTime& GetDeltaTime() const noexcept { return m_DeltaTime; }

        Logger& GetLogger() noexcept{ return *m_Logger; }
        Renderer& GetRenderer() noexcept { return m_Renderer; }
        Window& GetWindow() noexcept { return m_Window; }
        World& GetWorld() noexcept { return m_World;}
        InputSystem& GetInputSystem() noexcept { return m_InputSystem; }

        static Game& Get() noexcept { return *s_Game; }

    private:
        void BeginRender();
        void EndRender();

    private:
        bool m_IsRunning = true;
        Renderer m_Renderer;
        InputSystem m_InputSystem;
        Window m_Window;
        World m_World;
        std::unique_ptr<Logger> m_Logger;
        DeltaTime m_DeltaTime;

        static Game* s_Game;
    };
}
