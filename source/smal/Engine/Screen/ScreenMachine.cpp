#include <smal/Engine/Screen/ScreenMachine.hpp>

namespace ma
{
    namespace impl
    {
        union ScreenIden
        {
        public:
            ScreenIden(u16 family, u16 status)
                : m_family {family}
                , m_status {status}
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
    ScreenMachine::insert(u16 family, Screen* screen)
    {
        if ( this->m_holder.insert(family, screen) ) {
            if ( screen->attach() )
                screen->set_family(family);
        }

        return screen->family() == family;
    }

    bool
    ScreenMachine::insert(u16 active, u16 status, u16 coming)
    {
        auto change = (impl::ScreenIden {active, status})
                          .number;

        if ( coming != (u16) -1 )
            return this->m_change.insert(change, coming);

        return this->m_change.insert(change, status);
    }

    bool
    ScreenMachine::remove(u16 family)
    {
        if ( this->m_holder.contains(family) ) {
            this->m_holder[family]->detach();

            return this->m_holder
                .remove(family);
        }

        return false;
    }

    bool
    ScreenMachine::remove(u16 active, u16 status)
    {
        auto change = (impl::ScreenIden {active, status})
                          .number;

        return this->m_change.remove(change);
    }

    bool
    ScreenMachine::launch(u16 family)
    {
        if ( this->m_active != 0 )
            this->m_active->leave();

        if ( this->m_holder.contains(family) ) {
            this->m_active = this->m_holder[family];
            this->m_active->enter();
        } else
            this->m_active = 0;

        return this->m_active != 0;
    }

    bool
    ScreenMachine::launch(u16 active, u16 status)
    {
        auto change = (impl::ScreenIden {active, status})
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
