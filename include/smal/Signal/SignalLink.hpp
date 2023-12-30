#ifndef SMAL_SIGNAL_SIGNAL_LINK_HPP
#define SMAL_SIGNAL_SIGNAL_LINK_HPP

#include <smal/Signal/Signal.hpp>

namespace ma
{
    template <class... Args>
    class SignalLink
    {
    public:
        SignalLink()
            : m_signal {0}
        { }

        SignalLink(Signal<Args...>& signal)
            : m_signal {&signal}
        { }

        bool
        include(Observer<Args...>& item)
        {
            if ( m_signal != 0 )
                return m_signal->include(item);

            return false;
        }

        bool
        exclude(Observer<Args...>& item)
        {
            if ( m_signal != 0 )
                return m_signal->exclude(item);

            return false;
        }

    private:
        Signal<Args...>* m_signal;
    };

} // namespace ma

#endif // SMAL_SIGNA_SIGNAL_CONN_HPP
