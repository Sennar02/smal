#include <smal/Common/Action.hpp>
#include <smal/Common/util.hpp>

namespace ma
{
    template <class Ret, class... Args>
    Action<Ret(Args...)>::Action()
        : m_memory {0}
        , m_func {0}
    { }

    template <class Ret, class... Args>
    template <auto Func>
    Action<Ret(Args...)>::Action(Bind<Func>)
        : m_memory {0}
        , m_func {0}
    {
        bind<Func>();
    }

    template <class Ret, class... Args>
    template <auto Func, class Type>
    Action<Ret(Args...)>::Action(Bind<Func>, Type* inst)
        : m_memory {0}
        , m_func {0}
    {
        bind<Func>(inst);
    }

    template <class Ret, class... Args>
    template <class Func>
    Action<Ret(Args...)>::Action(Func&& func)
        : m_memory {0}
        , m_func {0}
    {
        bind<Func>(move(func));
    }

    template <class Ret, class... Args>
    bool
    Action<Ret(Args...)>::is_bound() const
    {
        return m_func != 0;
    }

    template <class Ret, class... Args>
    template <auto Func>
    bool
    Action<Ret(Args...)>::bind()
    {
        m_memory = 0;

        m_func = [](void* memory, Args... args) -> Ret {
            auto func = Func;

            return (*func)(forw<Args>(args)...);
        };

        return true;
    }

    template <class Ret, class... Args>
    template <auto Func, class Type>
    bool
    Action<Ret(Args...)>::bind(Type* inst)
    {
        m_memory = (void*) inst;

        m_func = [](void* memory, Args... args) -> Ret {
            auto func = Func;
            auto subj = (Type*) memory;

            return (subj->*func)(forw<Args>(args)...);
        };

        return true;
    }

    template <class Ret, class... Args>
    template <class Func>
    bool
    Action<Ret(Args...)>::bind(Func&& func)
    {
        create(*(Func*) m_memory, move(func));

        m_func = [](void* memory, Args... args) -> Ret {
            auto func = (Func*) memory;

            return (*func)(forw<Args>(args)...);
        };

        return true;
    }

    template <class Ret, class... Args>
    bool
    Action<Ret(Args...)>::clear()
    {
        m_memory = 0;
        m_func   = 0;

        return true;
    }

    template <class Ret, class... Args>
    template <class... Rest>
    Ret
    Action<Ret(Args...)>::invoke(Args... args, Rest... rest)
    {
        return m_func(m_memory, forw<Args>(args)...);
    }

    template <class Ret, class... Args>
    template <class... Rest>
    const Ret
    Action<Ret(Args...)>::invoke(Args... args, Rest... rest) const
    {
        return m_func(m_memory, forw<Args>(args)...);
    }

    template <class Ret, class... Args>
    template <class... Rest>
    Ret
    Action<Ret(Args...)>::operator()(Args... args, Rest... rest)
    {
        return m_func(m_memory, forw<Args>(args)...);
    }

    template <class Ret, class... Args>
    template <class... Rest>
    const Ret
    Action<Ret(Args...)>::operator()(Args... args, Rest... rest) const
    {
        return m_func(m_memory, forw<Args>(args)...);
    }

    template <auto Func>
    auto
    action()
    {
        return {bind<Func>};
    }

    template <auto Func, class Type>
    auto
    action(Type* inst)
    {
        return {bind<Func>, inst};
    }

    template <class Func>
    auto
    action(Func&& func)
    {
        return {move(func)};
    }
} // namespace ma
