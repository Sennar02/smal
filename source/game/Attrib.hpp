#ifndef ATTRIB_HPP
#define ATTRIB_HPP

#include <smal/Common/import.hpp>
#include <SFML/Graphics.hpp>

struct Vec2f
{
    void
    nrm();

    float x;
    float y;
};

void
Vec2f::nrm()
{
    float mag = sqrt(this->x * this->x +
                     this->y * this->y);

    this->x = smal::Math::div(this->x, mag);
    this->y = smal::Math::div(this->y, mag);
}

struct Vel : public Vec2f
{
    float frc;
    float acc;
    float mag;
    float max;
};

using Spr = sf::Sprite;

#endif // ATTRIB_HPP
