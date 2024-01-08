#include <smal/Engine/Engine.hpp>

#include <SFML/System/Clock.hpp> // sf::Clock

namespace ma
{
    static sf::Clock g_clock;

    Engine::Engine()
        : StateManager(32u)
        , m_active {true}
    { }

    bool
    Engine::isActive() const
    {
        return m_active;
    }

    bool
    Engine::loop(u32 code, u32 frames)
    {
        sf::Time slice = sf::seconds(1.0f / frames);
        sf::Time delta;

        if ( launch(code) == false ) return false;

        while ( true ) {
            delta += g_clock.restart();
            m_active = handle();

            if ( m_active ) {
                for ( ; slice < delta; delta -= slice )
                    update(slice.asSeconds());

                render();
            } else
                break;
        }

        return true;
    }

    bool
    Engine::handle()
    {
        State* state = active();

        if ( state != 0 && state->onHandle() == false )
            return launch(state->next());

        return state != 0;
    }

    void
    Engine::update(f32 delta)
    {
        active()->onUpdate(delta);
    }

    void
    Engine::render()
    {
        active()->onRender();
    }
} // namespace ma
