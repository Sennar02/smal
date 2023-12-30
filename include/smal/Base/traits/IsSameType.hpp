#ifndef SMAL_BASE_TRAITS_IS_SAME_TYPE_HPP
#define SMAL_BASE_TRAITS_IS_SAME_TYPE_HPP

namespace ma
{
    namespace impl
    {
        template <class Type, class Other>
        struct IsSameType
        {
            static const bool Main = false;
        };

        template <class Type>
        struct IsSameType<Type, Type>
        {
            static const bool Main = true;
        };
    } // namespace impl

    template <class Type, class Other>
    static const bool IsSameType = impl::IsSameType<Type, Other>::Main;
} // namespace ma

#endif // SMAL_BASE_TRAITS_IS_SAME_TYPE_HPP
