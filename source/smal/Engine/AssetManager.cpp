#include <smal/Engine/AssetManager.hpp>

namespace ma
{
    AssetManager::AssetManager(u32 size)
        : m_table {g_origin, size}
    { }
} // namespace ma
