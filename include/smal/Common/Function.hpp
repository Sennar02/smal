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
         *
         * @return True.
         * @return False.
         */
        bool
        is_bound() const;

        /**
         *
         *
         * @return True.
         * @return False.
         */
        template <auto Func>
        bool
        bind();

        /**
         *
         *
         * @param inst
         *
         * @return True.
         * @return False.
         */
        template <auto Func, class Type>
        bool
        bind(Type* inst);

        /**
         *
         *
         * @param func
         *
         * @return True.
         * @return False.
         */
        template <class Func>
        bool
        bind(Func&& func);

        /**
         *
         *
         * @return True.
         * @return False.
         */
        bool
        clear();

        /**
         *
         *
         * @param args
         *
         * @return
         */
        template <class... Rest>
        Ret
        invoke(Args... args, Rest... rest);

        /**
         *
         *
         * @param args
         *
         * @return
         */
        template <class... Rest>
        const Ret
        invoke(Args... args, Rest... rest) const;

        /**
         *
         *
         * @param args
         *
         * @return
         */
        template <class... Rest>
        Ret
        operator()(Args... args, Rest... rest);

        /**
         *
         *
         * @param args
         *
         * @return
         */
        template <class... Rest>
        const Ret
        operator()(Args... args, Rest... rest) const;

    private:
        using Proto = Ret(void*, Args...);

        /**
         *
         */
        void* m_memory;

        /**
         *
         */
        Proto* m_action;
    };

    template <auto Func>
    auto
    function();

    template <auto Func, class Type>
    auto
    function(Type* inst);

    template <class Func>
    auto
    function(Func&& func);
} // namespace ma

#include <smal/Common/impl/Function.tpp>

#endif // SMAL_COMMON_FUNC_HPP
