#include <smal/Signal/Observer.hpp>

namespace ma
{
    template <class... Args>
    Observer<Args...>::Observer()
        : Delegate<void(Args...)>()
        , m_next {0}
    { }

    template <class... Args>
    template <auto Func>
    Observer<Args...>::Observer(Bind<Func>)
        : Delegate<void(Args...)>(Bind<Func> {})
        , m_next {0}
    { }

    template <class... Args>
    template <auto Func, class Type>
    Observer<Args...>::Observer(Bind<Func>, Type& inst)
        : Delegate<void(Args...)>(Bind<Func> {}, inst)
        , m_next {0}
    { }

    template <class... Args>
    template <class Func>
    Observer<Args...>::Observer(Func&& func)
        : Delegate<void(Args...)>(func)
        , m_next {0}
    { }
} // namespace ma
