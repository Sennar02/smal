#ifndef SMAL_SIGNAL_OBSERVER_HPP
#define SMAL_SIGNAL_OBSERVER_HPP

#include <smal/Signal/Delegate.hpp>

namespace ma
{
    template <class... Args>
    class Observer
        : public Delegate<void(Args...)>
    {
    public:
        /**
         *
         */
        Observer();

        /**
         *
         */
        template <auto Func>
        Observer(Bind<Func>);

        /**
         *
         */
        template <auto Func, class Type>
        Observer(Bind<Func>, Type& inst);

        /**
         *
         */
        template <class Func>
        Observer(Func&& func);

    private:
        friend Signal<Args...>;

    private:
        /**
         *
         */
        Observer<Args...>* m_next;
    };
} // namespace ma

#include <smal/Signal/inline/Observer.inl>

#endif // SMAL_SIGNAL_OBSERVER_HPP
