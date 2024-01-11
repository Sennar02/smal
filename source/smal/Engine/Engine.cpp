#include <smal/Engine/Engine.hpp>

#include <SFML/System/Clock.hpp> // sf::Clock

namespace ma
{
    static sf::Clock g_clock;

    Engine::Engine()
        : StateManager(32u, m_actors)
        , m_actors {32u}
        , m_active {0}
    { }

    bool
    Engine::execute(const String& name, u32 frames)
    {
        bool result = start(name) &&
                      loop(frames) &&
                      clean();

        return result;
    }

    bool
    Engine::start(const String& name)
    {
        m_table.forEach([](auto, State*& state, u32) {
            state->onStart();
        });

        m_active = launch(name);

        if ( m_active != 0 )
            return true;

        return false;
    }

    bool
    Engine::loop(u32 frames)
    {
        sf::Time slice = sf::seconds(1.0f / frames);
        sf::Time delta;

        while ( m_active != 0 ) {
            delta += g_clock.restart();

            if ( m_active->onUpdate() == false )
                m_active = launch(m_active->next());

            if ( m_active != 0 ) {
                for ( ; delta < slice; delta -= slice )
                    m_active->onStep(slice.asSeconds());

                m_active->onLast();
            }
        }

        return true;
    }

    bool
    Engine::clean()
    {
        bool result = true;

        m_table.forEach([](auto, State*& state, u32) {
            state->onClean();
        });

        m_table.forEach([&result](auto, State*& state, u32) {
            result &= state->onDetach();
        });

        return result;
    }
} // namespace ma
