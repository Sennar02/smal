#ifndef SMAL_COMMON_FUNC_HPP
#define SMAL_COMMON_FUNC_HPP

#include <smal/Common/define.hpp>

namespace ma
{
    template <class Ret, class... Args>
    class Function<Ret(Args...)>
    {
    public:
        /**
         *
         */
        Function();

        /**
         *
         */
        template <auto Func>
        Function(Bind<Func>);

        /**
         *
         */
        template <auto Func, class Type>
        Function(Bind<Func>, Type* inst);

        /**
         *
         */
        template <class Func>
        Function(Func&& func);

        /**
         *
         */
        bool
        is_bound() const;

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
        invoke(Args... args, Rest... rest);

        /**
         *
         */
        template <class... Rest>
        const Ret
        invoke(Args... args, Rest... rest) const;

        /**
         *
         */
        template <class... Rest>
        Ret
        operator()(Args... args, Rest... rest);

        /**
         *
         */
        template <class... Rest>
        const Ret
        operator()(Args... args, Rest... rest) const;

    private:
        using Call = Ret (*)(void*, Args...);

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
    Function(Bind<Func>)
        -> Function<FuncSignat<decltype(Func)>>;

    template <auto Func, class Type>
    Function(Bind<Func>, Type*)
        -> Function<FuncSignat<decltype(Func)>>;

    template <class Func>
    Function(Func&&)
        -> Function<FuncSignat<decltype(&Func::operator())>>;

    /**
     *
     */
    template <auto Func>
    auto
    function();

    /**
     *
     */
    template <auto Func, class Type>
    auto
    function(Type* inst);

    /**
     *
     */
    template <class Func>
    auto
    function(Func&& func);
} // namespace ma

#include <smal/Common/impl/Function.tpp>

#endif // SMAL_COMMON_FUNC_HPP
