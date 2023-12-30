#ifndef SMAL_SIGNAL_DELEGATE_HPP
#define SMAL_SIGNAL_DELEGATE_HPP

#include <smal/Signal/define.hpp>
#include <smal/Signal/traits/Signature.hpp>

namespace ma
{
    template <class Ret, class... Args>
    class Delegate<Ret(Args...)>
    {
    public:
        /**
         *
         */
        Delegate();

        /**
         *
         */
        template <auto Func>
        Delegate(Bind<Func>);

        /**
         *
         */
        template <auto Func, class Type>
        Delegate(Bind<Func>, Type& inst);

        /**
         *
         */
        template <class Func>
        Delegate(const Func& func);

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
        bind(Type& inst);

        /**
         *
         */
        template <class Func>
        bool
        bind(const Func& func);

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

        /**
         *
         */
        template <class... Rest>
        Ret
        invoke(const Tuple<Args..., Rest...>& tuple) const;

        /**
         *
         */
        template <class... Rest>
        Ret
        operator()(const Tuple<Args..., Rest...>& tuple) const;

    private:
        using Call = Ret(void*, Args...);

    private:
        /**
         *
         */
        template <class... Rest, u32... List>
        Ret
        unwind(const Tuple<Args..., Rest...>& tuple, IndexSeq<List...> sequence) const;

    private:
        /**
         *
         */
        void* m_memory;

        /**
         *
         */
        Call* m_func;
    };

    template <auto Func>
    Delegate(Bind<Func>)
        -> Delegate<Signature<Func>>;

    template <auto Func, class Type>
    Delegate(Bind<Func>, Type&)
        -> Delegate<Signature<Func>>;

    template <class Func>
    Delegate(const Func&)
        -> Delegate<Signature<&Func::operator()>>;

    /**
     *
     */
    template <auto Func>
    auto
    delegate();

    /**
     *
     */
    template <auto Func, class Type>
    auto
    delegate(Type& inst);

    /**
     *
     */
    template <class Func>
    auto
    delegate(const Func& func);
} // namespace ma

#include <smal/Signal/inline/Delegate.inl>

#endif // SMAL_SIGNAL_DELEGATE_HPP
