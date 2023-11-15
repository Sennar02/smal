#ifndef SMAL_ENGINE_SCREEN_MACHINE_HPP
#define SMAL_ENGINE_SCREEN_MACHINE_HPP

#include <smal/Engine/ScreenLocator.hpp>
#include <smal/Engine/ScreenChanges.hpp>

namespace ma
{
    class ScreenMachine
        : public HashMap<u32, Screen*>
    {
    public:
        ScreenMachine(BaseOrigin* origin, usize size = 0);

        bool
        insert(u16 family, Screen* screen);

        bool
        insert(u16 active, u16 status, u16 coming = -1);

        bool
        remove(u16 family);

        bool
        remove(u16 active, u16 status);

        bool
        launch(u16 family);

        bool
        launch(u16 family, u16 status);

        bool
        finish();

        Screen*
        active();

        const Screen*
        active() const;

    private:
        ScreenLocator m_locator;
        ScreenChanges m_changes;

        Screen* m_active;
    };
} // namespace ma

#endif // SMAL_ENGINE_SCREEN_MACHINE_HPP
