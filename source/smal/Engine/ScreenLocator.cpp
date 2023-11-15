#include <smal/Engine/ScreenLocator.hpp>

namespace ma
{
    ScreenLocator::ScreenLocator(BaseOrigin* origin, usize size)
        : HashMap<u16, Screen*>(origin, size)
    { }

    bool
    ScreenLocator::insert(u16 family, Screen* screen)
    {
        auto& super = (HashMap<u16, Screen*>&) *this;

        if ( family != 0 && screen != 0 )
            return super.insert(family, screen);

        return false;
    }
} // namespace ma
