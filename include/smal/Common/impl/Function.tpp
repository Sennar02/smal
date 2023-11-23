#include <smal/Common/Function.hpp>
#include <smal/Common/helper.hpp>

namespace ma
{
    template <class Ret, class... Args>
    Function<Ret(Args...)>::Function()
        : m_memory {0}
        , m_action {0}
    { }

    template <class Ret, class... Args>
    bool
    Function<Ret(Args...)>::is_bound() const
    {
        return m_action != 0;
    }

    template <class Ret, class... Args>
    template <auto Func>
    bool
    Function<Ret(Args...)>::bind()
    {
        m_memory = 0;

        m_action = [](void* memory, Args... args) -> Ret {
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

        m_action = [](void* memory, Args... args) -> Ret {
            auto func = Func;
            auto inst = (Type*) memory;

            return (inst->*func)(forw<Args>(args)...);
        };

        return true;
    }

    template <class Ret, class... Args>
    template <class Func>
    bool
    Function<Ret(Args...)>::bind(Func&& func)
    {
        create(*(Func*) m_memory, move(func));

        m_action = [](void* memory, Args... args) -> Ret {
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
        m_action = 0;

        return true;
    }

    template <class Ret, class... Args>
    template <class... Rest>
    Ret
    Function<Ret(Args...)>::invoke(Args... args, Rest... rest)
    {
        return m_action(m_memory, forw<Args>(args)...);
    }

    template <class Ret, class... Args>
    template <class... Rest>
    const Ret
    Function<Ret(Args...)>::invoke(Args... args, Rest... rest) const
    {
        return m_action(m_memory, forw<Args>(args)...);
    }

    template <class Ret, class... Args>
    template <class... Rest>
    Ret
    Function<Ret(Args...)>::operator()(Args... args, Rest... rest)
    {
        return invoke(forw<Args>(args)...);
    }

    template <class Ret, class... Args>
    template <class... Rest>
    const Ret
    Function<Ret(Args...)>::operator()(Args... args, Rest... rest) const
    {
        return invoke(forw<Args>(args)...);
    }

    template <auto Func>
    auto
    function()
    {
        using Decl = decltype(Func);

        auto result =
            Function<FuncType<Decl>> {};

        result.template bind<Func>();

        return result;
    }

    template <auto Func, class Type>
    auto
    function(Type* inst)
    {
        using Decl = decltype(Func);

        auto result =
            Function<FuncType<Decl>> {};

        result.template bind<Func>(inst);

        return result;
    }

    template <class Func>
    auto
    function(Func&& func)
    {
        using Decl = decltype(&Func::operator());

        auto result =
            Function<FuncType<Decl>> {};

        result.bind(move(func));

        return result;
    }
} // namespace ma
