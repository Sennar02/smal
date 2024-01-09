#include <smal/Engine/Engine.hpp>

#include <SFML/System/Clock.hpp> // sf::Clock

namespace ma
{
    static sf::Clock g_clock;

    Engine::Engine()
        : StateManager(32u)
        , m_active {0}
    { }

    bool
    Engine::loop(const String& name, u32 frames)
    {
        sf::Time slice = sf::seconds(1.0f / frames);
        sf::Time delta;

        m_active = launch(name);

        if ( m_active == 0 ) return false;

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
} // namespace ma
