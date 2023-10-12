#ifndef APP_HPP
#define APP_HPP

#include <smal/Entity/import.hpp>
#include "Attrib.hpp"
#include "Engine.hpp"

class App
    : public Engine
{
public:
    App(const smal::Attributes& attrib)
        : Engine(120, 120)
        , m_attrib {smal::move(attrib)}
        , m_textur {}
        , m_sprite {}
    {
        if ( this->m_textur.loadFromFile("player.png") == false )
            this->m_active = false;

        this->m_sprite.setTexture(this->m_textur);
        this->m_sprite.setTextureRect({0, 0, 48, 48});
        this->m_sprite.setPosition({0, 0});
        this->m_sprite.setScale({2.f, 2.f});

        this->m_attrib.give<Vel>(0, {0, 0, 5, 15, 0, 250});
        this->m_attrib.give<Spr>(0, this->m_sprite);
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
        auto& velp = this->m_attrib.get<Vel>();
        auto& sprp = this->m_attrib.get<Spr>();

        long size = smal::Math::min(velp.size(), sprp.size());

        // Input system.
        for ( long i = 0; i < velp.size(); i++ ) {
            bool  frc = false;
            auto& vel = this->m_attrib.get<Vel>(i);

            if ( sf::Keyboard::isKeyPressed(sf::Keyboard::W) )
                vel.y -= 1, frc = true;
            if ( sf::Keyboard::isKeyPressed(sf::Keyboard::A) )
                vel.x -= 1, frc = true;
            if ( sf::Keyboard::isKeyPressed(sf::Keyboard::S) )
                vel.y += 1, frc = true;
            if ( sf::Keyboard::isKeyPressed(sf::Keyboard::D) )
                vel.x += 1, frc = true;

            if ( frc == true )
                vel.mag = smal::Math::min(vel.max, vel.mag + vel.acc);

            frc = false;

            vel.nrm();
        }

        // Movement system.
        for ( long i = 0; i < size; i++ ) {
            auto& vel = this->m_attrib.get<Vel>(i);
            auto& spr = this->m_attrib.get<Spr>(i);
            auto  pos = spr.getPosition();

            pos.x += vel.x * vel.mag * delta;
            pos.y += vel.y * vel.mag * delta;

            vel.mag = smal::Math::max(0.f, vel.mag - vel.frc);

            spr.setPosition(pos);
        }
    }

    void
    render(sf::RenderWindow& window)
    {
        window.clear(sf::Color {192, 192, 192});

        auto& sprp = this->m_attrib.get<Spr>();

        // Rendering system.
        for ( long i = 0; i < sprp.size(); i++ )
            window.draw(this->m_attrib.get<Spr>(i));

        window.display();
    }

private:
    smal::Attributes m_attrib;
    sf::Texture      m_textur;
    sf::Sprite       m_sprite;
};

#endif // APP_HPP
