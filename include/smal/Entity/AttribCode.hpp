#ifndef SMAL_ENTITY_ATTRIB_CODE_HPP
#define SMAL_ENTITY_ATTRIB_CODE_HPP

namespace smal
{
    class AttribCode
    {
    private:
        inline static long next = 0;

    public:
        template <class Type>
        inline static const long of =
            next++;
    };
} // namespace smal

#endif // SMAL_ENTITY_ATTRIB_CODE_HPP
