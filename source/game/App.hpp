#ifndef APP_HPP
#define APP_HPP

#include <smal/Entity/import.hpp>
#include "Attrib.hpp"
#include "Engine.hpp"

static const float scale  = 1;
static const usize side   = 16 * scale;
static const usize width  = 1280 / side;
static const usize height = 720 / side;

class App
    : public Engine
{
public:
    App(smal::Attributes& holder)
        : Engine(120, 120)
        , m_holder {&holder}
        , m_textur {}
        , m_sprite {}
    {
        if ( this->m_textur.loadFromFile("player.png") == false )
            this->m_active = false;
        // PLAYER
        this->m_sprite.setTexture(this->m_textur);
        this->m_sprite.setTextureRect({0, 0, 48, 48});
        this->m_sprite.setPosition({0, 0});

        this->m_holder->give<Velocity>(0, {0, 0, 20, 20, 3});
        this->m_holder->give<Sprite>(0, this->m_sprite);
    }

    void
    handle(const sf::Event& event)
    {
        if ( event.type == sf::Event::Closed )
            this->m_active = false;

        if ( event.type == sf::Event::KeyReleased ) {
            if ( event.key.code == sf::Keyboard::Escape )
                this->m_active = false;
        }
    }

    void
    update(float delta)
    {
        auto& velocity = this->m_holder->get<Velocity>();
        auto& sprite   = this->m_holder->get<Sprite>();

        Vec2f inp = {0, 0};

        // Input system.
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::W) )
            inp.y -= 1;
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::A) )
            inp.x -= 1;
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::S) )
            inp.y += 1;
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::D) )
            inp.x += 1;

        inp.nrm();

        // Movement system.
        auto& vel = velocity.valueOf(0);
        auto& spr = sprite.valueOf(0);
        auto  pos = spr.getPosition();

        if ( (inp.x == inp.y) && (inp.x == 0) ) {
            if ( vel.len() > vel.frc * delta ) {
                vel.x -= vel.x * vel.frc * delta;
                vel.y -= vel.y * vel.frc * delta;
            } else
                vel.x = vel.y = 0;
        } else {
            vel.x += inp.x * vel.acc * delta;
            vel.y += inp.y * vel.acc * delta;

            vel.lim(vel.mag);
        }

        pos.x += vel.x;
        pos.y += vel.y;

        spr.setPosition(pos);
    }

    void
    render(sf::RenderWindow& window)
    {
        window.clear(sf::Color {192, 192, 192});

        auto& sprite = this->m_holder->get<Sprite>();

        // Rendering system.
        for ( usize i = 0; i < sprite.size(); i++ )
            window.draw(sprite[i]);

        window.display();
    }

private:
    smal::Attributes* m_holder;
    sf::Texture       m_textur;
    sf::Sprite        m_sprite;
};

#endif // APP_HPP
