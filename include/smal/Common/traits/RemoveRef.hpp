#ifndef SMAL_COMMON_TRAITS_REMOVE_REF_HPP
#define SMAL_COMMON_TRAITS_REMOVE_REF_HPP

namespace ma
{
    namespace impl
    {
        template <class Type>
        struct RemoveRef
        {
            using Main = Type;
        };

        template <class Type>
        struct RemoveRef<Type&>
        {
            using Main = Type;
        };

        template <class Type>
        struct RemoveRef<Type&&>
        {
            using Main = Type;
        };
    } // namespace impl

    template <class Type>
    using RemoveRef = typename impl::RemoveRef<Type>::Main;
} // namespace ma

#endif // SMAL_COMMON_TRAITS_REMOVE_REF_HPP
