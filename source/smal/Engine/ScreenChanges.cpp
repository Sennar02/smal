#include <smal/Engine/ScreenChanges.hpp>

namespace ma
{
    ScreenChanges::ScreenChanges(BaseOrigin* origin, usize size)
        : HashMap<u32, u16>(origin, size)
    { }

    bool
    ScreenChanges::insert(u32 change, u16 coming)
    {
        auto& super = (HashMap<u32, u16>&) *this;

        if ( change != 0 && coming != 0 )
            return super.insert(change, coming);

        return false;
    }
} // namespace ma
