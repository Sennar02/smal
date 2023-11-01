#include <smal/Common/Func.hpp>
#include <smal/Common/helper.hpp>

namespace ma
{
    template <class Ret, class... Args>
    Func<Ret(Args...)>::Func()
        : m_memory {0}
        , m_action {0}
    { }

    template <class Ret, class... Args>
    bool
    Func<Ret(Args...)>::is_bound() const
    {
        return this->m_action != 0;
    }

    template <class Ret, class... Args>
    template <auto Call>
    bool
    Func<Ret(Args...)>::bind()
    {
        this->m_memory = 0;

        this->m_action = [](void* memory, Args... args) -> Ret {
            auto call = Call;

            return (*call)(forw<Args>(args)...);
        };

        return true;
    }

    template <class Ret, class... Args>
    template <auto Call, class Type>
    bool
    Func<Ret(Args...)>::bind(Type* inst)
    {
        this->m_memory = (void*) inst;

        this->m_action = [](void* memory, Args... args) -> Ret {
            auto call = Call;
            auto inst = (Type*) memory;

            return (inst->*call)(forw<Args>(args)...);
        };

        return true;
    }

    template <class Ret, class... Args>
    template <class Call>
    bool
    Func<Ret(Args...)>::bind(Call&& call)
    {
        create(*(Call*) this->m_memory, move(call));

        this->m_action = [](void* memory, Args... args) -> Ret {
            auto call = (Call*) memory;

            return (*call)(forw<Args>(args)...);
        };

        return true;
    }

    template <class Ret, class... Args>
    bool
    Func<Ret(Args...)>::clear()
    {
        this->m_memory = 0;
        this->m_action = 0;

        return true;
    }

    template <class Ret, class... Args>
    template <class... Rest>
    Ret
    Func<Ret(Args...)>::invoke(Args... args, Rest... rest)
    {
        return this->m_action(this->m_memory, forw<Args>(args)...);
    }

    template <class Ret, class... Args>
    template <class... Rest>
    const Ret
    Func<Ret(Args...)>::invoke(Args... args, Rest... rest) const
    {
        return this->m_action(this->m_memory, forw<Args>(args)...);
    }

    template <class Ret, class... Args>
    template <class... Rest>
    Ret
    Func<Ret(Args...)>::operator()(Args... args, Rest... rest)
    {
        return this->invoke(forw<Args>(args)...);
    }

    template <class Ret, class... Args>
    template <class... Rest>
    const Ret
    Func<Ret(Args...)>::operator()(Args... args, Rest... rest) const
    {
        return this->invoke(forw<Args>(args)...);
    }

    template <auto Call>
    auto
    func()
    {
        using Decl = decltype(Call);

        auto result =
            Func<FuncType<Decl>> {};

        result.template bind<Call>();

        return result;
    }

    template <auto Call, class Type>
    auto
    func(Type* inst)
    {
        using Decl = decltype(Call);

        auto result =
            Func<FuncType<Decl>> {};

        result.template bind<Call>(inst);

        return result;
    }

    template <class Call>
    auto
    func(Call&& call)
    {
        using Decl = decltype(&Call::operator());

        auto result =
            Func<FuncType<Decl>> {};

        result.bind(move(call));

        return result;
    }
} // namespace ma
