#ifndef SMAL_ENGINE_ENGINE_HPP
#define SMAL_ENGINE_ENGINE_HPP

#include <smal/Engine/Screen/ScreenMachine.hpp>

namespace ma
{
    class Engine
    {
    public:
        Engine(BaseOrigin* origin, usize size = 0);

        bool
        is_active() const;

        void
        loop(u16 code, usize frames = 60);

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

    private:
        sf::RenderWindow m_window;
        sf::Clock        m_clock;
        ScreenMachine    m_screens;
        bool             m_active;
    };
} // namespace ma

#endif // SMAL_ENGINE_ENGINE_HPP
