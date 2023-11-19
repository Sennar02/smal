#include <smal/Engine/Screen/Screen.hpp>

namespace ma
{
    Screen::Screen(const HashMap<String, u16>& names,
        const HashMap<String, u16>&            exits)
        : m_code {(u16) -1}
        , m_exit {(u16) -1}
        , names {names}
        , exits {exits}
    { }

    u16
    Screen::code() const
    {
        return this->m_code;
    }

    u16
    Screen::exit() const
    {
        return this->m_exit;
    }

    void
    Screen::set_exit(u16 exit)
    {
        this->m_exit = exit;
    }

    void
    Screen::set_code(u16 code)
    {
        this->m_code = code;
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
