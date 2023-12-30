#ifndef SMAL_SIGNAL_SIGNAL_HPP
#define SMAL_SIGNAL_SIGNAL_HPP

#include <smal/Signal/Observer.hpp>

namespace ma
{
    template <class... Args>
    class Signal
    {
    public:
        /**
         *
         */
        Signal();

        /**
         *
         */
        bool
        include(Observer<Args...>& item);

        /**
         *
         */
        bool
        exclude(Observer<Args...>& item);

        /**
         *
         */
        bool
        clear();

        /**
         *
         */
        bool
        publish(Args&&... args);

        /**
         *
         */
        bool
        publish(const Tuple<Args...>& args);

    private:
        /**
         *
         */
        Observer<Args...>* m_head;
    };
} // namespace ma

#include <smal/Signal/inline/Signal.inl>

#endif // SMAL_SIGNAL_SIGNAL_HPP
