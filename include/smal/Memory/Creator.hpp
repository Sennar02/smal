#ifndef SMAL_MEMORY_CREATOR_HPP
#define SMAL_MEMORY_CREATOR_HPP

#include <smal/Memory/Origin/PoolOrigin.hpp>

namespace ma
{
    class Creator
    {
    public:
        /**
         * Creates a creator.
         *
         * @param origin Memory origin.
         */
        Creator(BaseOrigin* origin);

        /**
         * Creates a default instance of a type.
         *
         * @return A pointer to the instance.
         */
        template <class Type>
        Type*
        create();

        /**
         * Creates an instance of a type.
         *
         * @param args Arguments to create the instance.
         *
         * @return A pointer to the instance.
         */
        template <class Type, class... Args>
        Type*
        create(Args&&... args);

        /**
         * Destroys a previously created instance.
         *
         * @param item Instance to destroy.
         *
         * @return True if it's destroy.
         * @return False otherwise.
         */
        template <class Type>
        bool
        destroy(Type* item);

    private:
        /**
         * Origin of memory.
         */
        BaseOrigin* m_origin;
    };
} // namespace ma

#include <smal/Memory/impl/Creator.tpp>

#endif // SMAL_MEMORY_CREATOR_HPP
