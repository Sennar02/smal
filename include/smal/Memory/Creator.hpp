#ifndef SMAL_MEMORY_CREATOR_HPP
#define SMAL_MEMORY_CREATOR_HPP

#include <smal/Memory/Origin/PoolOrigin.hpp>

namespace smal
{
    template <class Type>
    class Creator
    {
    public:
        /**
         * @brief
         */
        static const usize SIZE = sizeof(Type);

    public:
        /**
         * @brief
         *
         * @param origin
         */
        Creator(PoolOrigin& origin);

        /**
         * @brief
         *
         * @return Type*
         */
        Type*
        create();

        /**
         * @brief
         *
         * @tparam Args
         *
         * @param args
         *
         * @return Type*
         */
        template <class... Args>
        Type*
        create(Args&&... args);

        /**
         * @brief
         *
         * @param item
         *
         * @return true
         * @return false
         */
        bool
        destroy(Type* item);

    private:
        /**
         * @brief
         */
        BaseOrigin& m_origin;
    };
} // namespace smal

#include <smal/Memory/impl/Creator.tpp>

#endif // SMAL_MEMORY_CREATOR_HPP
