#ifndef SMAL_COMMON_DEFINE_HPP
#define SMAL_COMMON_DEFINE_HPP

namespace smal
{
    template <class... Types>
    class Tuple;

    template <>
    class Tuple<>
    {
    public:
        static const long LENGTH = 0;
    };
} // namespace smal

#endif // SMAL_COMMON_DEFINE_HPP
