#include <smal/Engine/AssetManager.hpp>

namespace ma
{
    namespace impl
    {
        struct AssetTag
        {
            template <class Type>
            static u32
            get()
            {
                static const u32 tag =
                    s_count++;

                return tag;
            }

            static inline u32 s_count = 0;
        };
    } // namespace impl

    template <class Type>
    bool
    AssetManager::insert(Type& asset)
    {
        u32 index =
            impl::AssetTag::get<Type>();

        return m_table.insert(index, (void*) &asset);
    }

    template <class Type>
    bool
    AssetManager::remove()
    {
        u32 index =
            impl::AssetTag::get<Type>();

        return m_table.remove(index);
    }

    template <class Type>
    Type*
    AssetManager::find(Type* deflt)
    {
        u32 index =
            impl::AssetTag::get<Type>();

        return (Type*) m_table.find(index, deflt);
    }

    template <class Type>
    Type*
    AssetManager::find()
    {
        u32 index =
            impl::AssetTag::get<Type>();

        return (Type*) m_table.find(index);
    }
} // namespace ma
