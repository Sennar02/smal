#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SFML/Graphics.hpp>
#include <smal/Common/import.hpp>

class Engine
{
public:
    Engine(usize frames, usize fskips = 1)
        : m_active {true}
        , m_frames {frames}
        , m_fskips {fskips}
        , m_clock {}
    { }

    void
    loop(sf::RenderWindow& window)
    {
        sf::Time  slice = sf::seconds(1.0f / this->m_frames);
        sf::Time  delta;
        sf::Event event;

        bool change = false;

        while ( this->m_active ) {
            delta += this->m_clock.restart();

            printf("%f\n", delta.asSeconds());

            while ( window.pollEvent(event) )
                this->handle(event);

            for ( usize s = 0; s < this->m_fskips; s++ ) {
                if ( slice < delta )
                    delta -= slice;
                else
                    break;

                this->update(slice.asSeconds());
                change = true;
            }

            if ( change == true ) {
                this->render(window);

                change = false;
            }
        }
    }

protected:
    virtual void
    handle(const sf::Event& event) = 0;

    virtual void
    update(float delta) = 0;

    virtual void
    render(sf::RenderWindow& target) = 0;

protected:
    bool m_active;

private:
    usize     m_frames;
    usize     m_fskips;
    sf::Clock m_clock;
};

#endif // ENGINE_HPP
