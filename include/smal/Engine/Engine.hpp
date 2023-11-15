#ifndef SMAL_ENGINE_ENGINE_HPP
#define SMAL_ENGINE_ENGINE_HPP

#include <smal/Engine/ScreenMachine.hpp>

namespace ma
{
    class Engine
    {
    public:
        Engine(BaseOrigin* origin, usize size = 0);

        bool
        is_active() const;

        void
        loop(u16 family, usize frames = 60);

        ScreenMachine&
        screens();

        const ScreenMachine&
        screens() const;

    private:
        void
        handle();

        void
        handle(const sf::Event& event);

        void
        update(f32 delta);

        void
        render();

    public:
        // // Move after resource management
        // sf::VideoMode win_vmode = {g_window_width, g_window_height};
        // const char*   win_title = "smal";
        // ma::usize     win_style = sf::Style::Default;

    private:
        sf::RenderWindow  m_window;
        sf::Clock         m_clock;
        ScreenMachine m_screens;
        bool          m_active;
    };
} // namespace ma

#endif // SMAL_ENGINE_ENGINE_HPP
