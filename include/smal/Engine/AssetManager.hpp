#ifndef SMAL_ENGINE_ASSET_MANAGER_HPP
#define SMAL_ENGINE_ASSET_MANAGER_HPP

#include <smal/Engine/define.hpp>

namespace ma
{
    class AssetManager
    {
    public:
        /**
         *
         */
        AssetManager(u32 size);

        /**
         *
         */
        template <class Type>
        bool
        insert(Type& asset);

        /**
         *
         */
        template <class Type>
        bool
        remove();

        /**
         *
         */
        template <class Type>
        Type*
        find(Type* deflt);

        /**
         *
         */
        template <class Type>
        Type*
        find();

    protected:
        /**
         *
         */
        HashTable<u32, void*> m_table;
    };
} // namespace ma

#include <smal/Engine/inline/AssetManager.inl>

#endif // SMAL_ENGINE_ASSET_MANAGER_HPP
