#ifndef SMAL_ENGINE_SCREEN_LOCATOR_HPP
#define SMAL_ENGINE_SCREEN_LOCATOR_HPP

#include <smal/Engine/Screen.hpp>

namespace ma
{
    class ScreenLocator
        : public HashMap<u16, Screen*>
    {
    public:
        /**
         *
         */
        ScreenLocator(BaseOrigin* origin, usize size = 0);

        /**
         *
         */
        bool
        insert(u16 family, Screen* screen);
    };
} // namespace ma

#endif // SMAL_ENGINE_SCREEN_LOCATOR_HPP
