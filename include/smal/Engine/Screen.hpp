#ifndef SMAL_ENGINE_SCREEN_HPP
#define SMAL_ENGINE_SCREEN_HPP

#include <smal/Engine/define.hpp>

namespace ma
{
    class Screen
    {
    public:
        Screen();

        u16
        family() const;

        u16
        status() const;

        void
        set_status(u16 status);

        virtual bool
        attach();

        virtual void
        detach();

        virtual void
        enter();

        virtual void
        leave();

        virtual u16
        handle();

        virtual u16
        handle(const sf::Event& event) = 0;

        virtual void
        update(f32 delta);

        virtual void
        render(sf::RenderTarget& target);

    private:
        friend class ScreenMachine;

        void
        set_family(u16 family);

    private:
        u16 m_family;
        u16 m_status;
    };
} // namespace ma

#endif // SMAL_ENGINE_SCREEN_HPP
