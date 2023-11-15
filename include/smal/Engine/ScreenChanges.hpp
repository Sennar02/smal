#ifndef SMAL_ENGINE_SCREEN_CHANGES_HPP
#define SMAL_ENGINE_SCREEN_CHANGES_HPP

#include <smal/Engine/Screen.hpp>

namespace ma
{
    class ScreenChanges
        : public HashMap<u32, u16>
    {
    public:
        ScreenChanges(BaseOrigin* origin, usize size = 0);

        bool
        insert(u32 change, u16 coming);
    };
} // namespace ma

#endif // SMAL_ENGINE_SCREEN_CHANGES_HPP
