#include <smal/Signal/Signal.hpp>

namespace ma
{
    template <class... Args>
    Signal<Args...>::Signal()
        : m_head {0}
    { }

    template <class... Args>
    bool
    Signal<Args...>::include(Observer<Args...>& item)
    {
        if ( item.m_next == 0 ) {
            item.m_next = m_head;
            m_head      = &item;

            return true;
        }

        return false;
    }

    template <class... Args>
    bool
    Signal<Args...>::exclude(Observer<Args...>& item)
    {
        return false;
    }

    template <class... Args>
    bool
    Signal<Args...>::clear()
    {
        while ( m_head != 0 )
            exclude(m_head);

        return true;
    }

    template <class... Args>
    bool
    Signal<Args...>::publish(Args&&... args)
    {
        Observer<Args...>* node = m_head;

        for ( ; node != 0; node = node->m_next )
            node->invoke(forw<Args>(args)...);

        return true;
    }

    template <class... Args>
    bool
    Signal<Args...>::publish(const Tuple<Args...>& tuple)
    {
        Observer<Args...>* node = m_head;

        for ( ; node != 0; node = node->m_next )
            node->invoke(tuple);

        return true;
    }
} // namespace ma
