#include <smal/Engine/Screen.hpp>

namespace ma
{
    Screen::Screen()
        : m_family {(u16) -1}
        , m_status {(u16) -1}
    { }

    u16
    Screen::family() const
    {
        return this->m_family;
    }

    u16
    Screen::status() const
    {
        return this->m_status;
    }

    void
    Screen::set_status(u16 status)
    {
        this->m_status = status;
    }

    void
    Screen::set_family(u16 family)
    {
        this->m_family = family;
    }

    bool
    Screen::attach()
    {
        return true;
    }

    void
    Screen::detach()
    { }

    void
    Screen::enter()
    { }

    void
    Screen::leave()
    { }

    u16
    Screen::handle()
    {
        return 0;
    }

    void
    Screen::update(f32 delta)
    { }

    void
    Screen::render(sf::RenderTarget& target)
    { }
} // namespace ma
