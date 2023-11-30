#ifndef SMAL_COMMON_TRAITS_REMOVE_PTR_HPP
#define SMAL_COMMON_TRAITS_REMOVE_PTR_HPP

namespace ma
{
    namespace impl
    {
        template <class Type>
        struct RemovePtr {
            using Main = Type;
        };

        template <class Type>
        struct RemovePtr<Type*> {
            using Main = Type;
        };
    } // namespace impl

    template <class Type>
    using RemovePtr = typename impl::RemovePtr<Type>::Main;
} // namespace ma

#endif // SMAL_COMMON_TRAITS_REMOVE_PTR_HPP
