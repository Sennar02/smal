#ifndef SMAL_COMMON_ACTION_HPP
#define SMAL_COMMON_ACTION_HPP

#include <smal/Common/define.hpp>
#include <smal/Common/traits/Signature.hpp>

namespace ma
{
    template <class Ret, class... Args>
    class Action<Ret(Args...)>
    {
    public:
        /**
         *
         */
        Action();

        /**
         *
         */
        template <auto Func>
        Action(Bind<Func>);

        /**
         *
         */
        template <auto Func, class Type>
        Action(Bind<Func>, Type* inst);

        /**
         *
         */
        template <class Func>
        Action(Func&& func);

        /**
         *
         */
        bool
        isBound() const;

        /**
         *
         */
        template <auto Func>
        bool
        bind();

        /**
         *
         */
        template <auto Func, class Type>
        bool
        bind(Type* inst);

        /**
         *
         */
        template <class Func>
        bool
        bind(Func&& func);

        /**
         *
         */
        bool
        clear();

        /**
         *
         */
        template <class... Rest>
        Ret
        invoke(Args... args, Rest... rest) const;

        /**
         *
         */
        template <class... Rest>
        Ret
        operator()(Args... args, Rest... rest) const;

    private:
        using Call = Ret (*)(void*, Args...);

    private:
        /**
         *
         */
        void* m_memory;

        /**
         *
         */
        Call m_func;
    };

    template <auto Func>
    Action(Bind<Func>)
        -> Action<Signature<Func>>;

    template <auto Func, class Type>
    Action(Bind<Func>, Type*)
        -> Action<Signature<Func>>;

    template <class Func>
    Action(Func&&)
        -> Action<Signature<&Func::operator()>>;

    /**
     *
     */
    template <auto Func>
    auto
    action();

    /**
     *
     */
    template <auto Func, class Type>
    auto
    action(Type* inst);

    /**
     *
     */
    template <class Func>
    auto
    action(Func&& func);
} // namespace ma

#include <smal/Common/impl/Action.tpp>

#endif // SMAL_COMMON_ACTION_HPP
