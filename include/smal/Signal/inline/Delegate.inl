#include <smal/Signal/Delegate.hpp>

namespace ma
{
    template <class Ret, class... Args>
    Delegate<Ret(Args...)>::Delegate()
        : m_memory {0}
        , m_func {0}
    { }

    template <class Ret, class... Args>
    template <auto Func>
    Delegate<Ret(Args...)>::Delegate(Bind<Func>)
        : m_memory {0}
        , m_func {0}
    {
        bind<Func>();
    }

    template <class Ret, class... Args>
    template <auto Func, class Type>
    Delegate<Ret(Args...)>::Delegate(Bind<Func>, Type& inst)
        : m_memory {0}
        , m_func {0}
    {
        bind<Func>(inst);
    }

    template <class Ret, class... Args>
    template <class Func>
    Delegate<Ret(Args...)>::Delegate(const Func& func)
        : m_memory {0}
        , m_func {0}
    {
        bind(func);
    }

    template <class Ret, class... Args>
    bool
    Delegate<Ret(Args...)>::isBound() const
    {
        return m_func != 0;
    }

    template <class Ret, class... Args>
    template <auto Func>
    bool
    Delegate<Ret(Args...)>::bind()
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
    Delegate<Ret(Args...)>::bind(Type& inst)
    {
        m_memory = (void*) &inst;

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
    Delegate<Ret(Args...)>::bind(const Func& func)
    {
        m_memory = (void*) &func;

        m_func = [](void* memory, Args... args) -> Ret {
            auto func = (Func*) memory;

            return (*func)(forw<Args>(args)...);
        };

        return true;
    }

    template <class Ret, class... Args>
    bool
    Delegate<Ret(Args...)>::clear()
    {
        m_memory = 0;
        m_func   = 0;

        return true;
    }

    template <class Ret, class... Args>
    template <class... Rest>
    Ret
    Delegate<Ret(Args...)>::invoke(Args... args, Rest... rest) const
    {
        return m_func(m_memory, forw<Args>(args)...);
    }

    template <class Ret, class... Args>
    template <class... Rest>
    Ret
    Delegate<Ret(Args...)>::operator()(Args... args, Rest... rest) const
    {
        return m_func(m_memory, forw<Args>(args)...);
    }

    template <class Ret, class... Args>
    template <class... Rest>
    Ret
    Delegate<Ret(Args...)>::invoke(const Tuple<Args..., Rest...>& tuple) const
    {
        return unwind(tuple, IndexGen<sizeof...(Args)> {});
    }

    template <class Ret, class... Args>
    template <class... Rest>
    Ret
    Delegate<Ret(Args...)>::operator()(const Tuple<Args..., Rest...>& tuple) const
    {
        return unwind(tuple, IndexGen<sizeof...(Args)> {});
    }

    template <class Ret, class... Args>
    template <class... Rest, u32... List>
    Ret
    Delegate<Ret(Args...)>::unwind(const Tuple<Args..., Rest...>& tuple, IndexSeq<List...> sequence) const
    {
        return m_func(m_memory, tuple.template extract<List>()...);
    }

    template <auto Func>
    auto
    delegate()
    {
        return Delegate {bind<Func>};
    }

    template <auto Func, class Type>
    auto
    delegate(Type& inst)
    {
        return Delegate {bind<Func>, inst};
    }

    template <class Func>
    auto
    delegate(const Func& func)
    {
        return Delegate {func};
    }
} // namespace ma
