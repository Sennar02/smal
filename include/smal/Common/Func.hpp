#ifndef SMAL_COMMON_FUNC_HPP
#define SMAL_COMMON_FUNC_HPP

#include <smal/Common/define.hpp>

namespace ma
{
    template <class Ret, class... Args>
    class Func<Ret(Args...)>
    {
    public:
        /**
         *
         */
        Func();

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
        template <auto Call>
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
        template <auto Call, class Type>
        bool
        bind(Type* inst);

        /**
         *
         *
         * @param call
         *
         * @return True.
         * @return False.
         */
        template <class Call>
        bool
        bind(Call&& call);

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
        using Action = Ret(void*, Args...);

        /**
         *
         */
        void* m_memory;

        /**
         *
         */
        Action* m_action;
    };

    template <auto Call>
    auto
    func();

    template <auto Call, class Type>
    auto
    func(Type* inst);

    template <class Call>
    auto
    func(Call&& call);
} // namespace ma

#include <smal/Common/impl/Func.tpp>

#endif // SMAL_COMMON_FUNC_HPP
