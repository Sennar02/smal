#include <smal/Common/Function.hpp>
#include <smal/Common/util.hpp>

namespace ma
{
    template <class Ret, class... Args>
    Function<Ret(Args...)>::Function()
        : m_memory {0}
        , m_func {0}
    { }

    template <class Ret, class... Args>
    template <auto Func>
    Function<Ret(Args...)>::Function(Bind<Func>)
        : m_memory {0}
        , m_func {0}
    {
        bind<Func>();
    }

    template <class Ret, class... Args>
    template <auto Func, class Type>
    Function<Ret(Args...)>::Function(Bind<Func>, Type* inst)
        : m_memory {0}
        , m_func {0}
    {
        bind<Func>(inst);
    }

    template <class Ret, class... Args>
    template <class Func>
    Function<Ret(Args...)>::Function(Func&& func)
        : m_memory {0}
        , m_func {0}
    {
        bind<Func>(move(func));
    }

    template <class Ret, class... Args>
    bool
    Function<Ret(Args...)>::is_bound() const
    {
        return m_func != 0;
    }

    template <class Ret, class... Args>
    template <auto Func>
    bool
    Function<Ret(Args...)>::bind()
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
    Function<Ret(Args...)>::bind(Type* inst)
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
    Function<Ret(Args...)>::bind(Func&& func)
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
    Function<Ret(Args...)>::clear()
    {
        m_memory = 0;
        m_func   = 0;

        return true;
    }

    template <class Ret, class... Args>
    template <class... Rest>
    Ret
    Function<Ret(Args...)>::invoke(Args... args, Rest... rest)
    {
        return m_func(m_memory, forw<Args>(args)...);
    }

    template <class Ret, class... Args>
    template <class... Rest>
    const Ret
    Function<Ret(Args...)>::invoke(Args... args, Rest... rest) const
    {
        return m_func(m_memory, forw<Args>(args)...);
    }

    template <class Ret, class... Args>
    template <class... Rest>
    Ret
    Function<Ret(Args...)>::operator()(Args... args, Rest... rest)
    {
        return m_func(m_memory, forw<Args>(args)...);
    }

    template <class Ret, class... Args>
    template <class... Rest>
    const Ret
    Function<Ret(Args...)>::operator()(Args... args, Rest... rest) const
    {
        return m_func(m_memory, forw<Args>(args)...);
    }

    template <auto Func>
    auto
    function()
    {
        Function f =
            {bind<Func>};

        return f;
    }

    template <auto Func, class Type>
    auto
    function(Type* inst)
    {
        Function f =
            {bind<Func>, inst};

        return f;
    }

    template <class Func>
    auto
    function(Func&& func)
    {
        Function f =
            {move(func)};

        return f;
    }
} // namespace ma
