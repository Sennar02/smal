#ifndef SMAL_MEMORY_ORIGIN_FACTORY_HPP
#define SMAL_MEMORY_ORIGIN_FACTORY_HPP

#include <smal/Memory/PageTable.hpp>

namespace ma
{
    class OriginFactory
    {
    public:
        /**
         *
         */
        static const u32 s_size = PageTable::s_size;

    public:
        /**
         *
         */
        OriginFactory(u32 size);

        /**
         *
         */
        ~OriginFactory();

        /**
         *
         */
        template <class Origin, class... Args>
        Origin
        request(u32 size, Args&&... args);

    private:
        /**
         *
         */
        PageTable m_table;
    };

    static OriginFactory g_factory = {256u};
} // namespace ma

#include <smal/Memory/inline/OriginFactory.inl>

#endif // SMAL_MEMORY_ORIGIN_FACTORY_HPP
