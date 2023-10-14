#ifndef ATTRIB_HPP
#define ATTRIB_HPP

#include <smal/Common/import.hpp>
#include <SFML/Graphics.hpp>

struct Vec2f
{
    void
    nrm();

    float
    len();

    void
    lim(float len);

    float x;
    float y;
};

void
Vec2f::nrm()
{
    float len = this->len();

    this->x = smal::Math::div(this->x, len);
    this->y = smal::Math::div(this->y, len);
}

float
Vec2f::len()
{
    return sqrt(this->x * this->x +
                this->y * this->y);
}

void
Vec2f::lim(float max)
{
    auto len = this->len();
    auto div = max / len;

    if ( len > max ) {
        this->x *= div;
        this->y *= div;
    }
}

struct Velocity
    : public Vec2f
{
    float frc;
    float acc;
    float mag;
};

using Sprite = sf::Sprite;

#endif // ATTRIB_HPP
