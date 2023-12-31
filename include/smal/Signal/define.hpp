#ifndef SMAL_SIGNAL_DEFINE_HPP
#define SMAL_SIGNAL_DEFINE_HPP

#include <smal/Signal/depend.hpp>

namespace ma
{
    template <class Func>
    class Delegate;

    template <auto Func>
    struct Bind
    {
    public:
        /**
         *
         */
        Bind() = default;
    };

    template <auto Func>
    static inline Bind<Func> bind =
        Bind<Func> {};
} // namespace ma

#endif // SMAL_SIGNAL_DEFINE_HPP
