#include <smal/Engine/Screen/ScreenMachine.hpp>

namespace ma
{
    namespace impl
    {
        union ScreenIden
        {
        public:
            ScreenIden(u16 code, u16 exit)
                : m_family {code}
                , m_status {exit}
            { }

            u32 number;

        private:
            struct
            {
                u16 m_family;
                u16 m_status;
            };
        };
    } // namespace impl

    ScreenMachine::ScreenMachine(BaseOrigin* origin, usize size)
        : m_holder {origin, size}
        , m_change {origin, size}
        , m_active {0}
    { }

    bool
    ScreenMachine::insert(u16 code, Screen* screen)
    {
        if ( this->m_holder.insert(code, screen) ) {
            if ( screen->attach() )
                screen->set_code(code);
        }

        return screen->code() == code;
    }

    bool
    ScreenMachine::insert(u16 active, u16 exit, u16 coming)
    {
        auto change = (impl::ScreenIden {active, exit})
                          .number;

        if ( coming != (u16) -1 )
            return this->m_change.insert(change, coming);

        return this->m_change.insert(change, exit);
    }

    bool
    ScreenMachine::remove(u16 code)
    {
        if ( this->m_holder.contains(code) ) {
            this->m_holder[code]->detach();

            return this->m_holder
                .remove(code);
        }

        return false;
    }

    bool
    ScreenMachine::remove(u16 active, u16 exit)
    {
        auto change = (impl::ScreenIden {active, exit})
                          .number;

        return this->m_change.remove(change);
    }

    bool
    ScreenMachine::launch(u16 code)
    {
        if ( this->m_active != 0 )
            this->m_active->leave();

        if ( this->m_holder.contains(code) ) {
            this->m_active = this->m_holder[code];
            this->m_active->enter();
        } else
            this->m_active = 0;

        return this->m_active != 0;
    }

    bool
    ScreenMachine::launch(u16 active, u16 exit)
    {
        auto change = (impl::ScreenIden {active, exit})
                          .number;

        if ( this->m_change.contains(change) )
            return this->launch(this->m_change[change]);

        return false;
    }

    bool
    ScreenMachine::finish()
    {
        auto func = [](auto&, auto& s) {
            s->detach();
        };

        this->m_holder.for_each(func);

        return true;
    }

    Screen*
    ScreenMachine::active()
    {
        return this->m_active;
    }

    const Screen*
    ScreenMachine::active() const
    {
        return this->m_active;
    }
} // namespace ma
