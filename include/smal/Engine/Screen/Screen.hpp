#ifndef SMAL_ENGINE_SCREEN_SCREEN_HPP
#define SMAL_ENGINE_SCREEN_SCREEN_HPP

#include <smal/Engine/define.hpp>

namespace ma
{
    class Screen
    {
    public:
        Screen(const HashMap<String, u16>& names,
            const HashMap<String, u16>&    exits);

        virtual ~Screen() = default;

        u16
        code() const;

        u16
        exit() const;

        void
        set_exit(u16 exit);

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
        set_code(u16 code);

    private:
        u16 m_code;
        u16 m_exit;

    protected:
        const HashMap<String, u16>& names;
        const HashMap<String, u16>& exits;
    };
} // namespace ma

#endif // SMAL_ENGINE_SCREEN_SCREEN_HPP
