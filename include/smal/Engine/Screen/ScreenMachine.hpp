#ifndef SMAL_ENGINE_SCREEN_SCREEN_MACHINE_HPP
#define SMAL_ENGINE_SCREEN_SCREEN_MACHINE_HPP

#include <smal/Engine/Screen/Screen.hpp>

namespace ma
{
    class ScreenMachine
    {
    public:
        ScreenMachine(BaseOrigin* origin, usize size = 0);

        bool
        insert(u16 code, Screen* screen);

        bool
        insert(u16 active, u16 exit, u16 coming = -1);

        bool
        remove(u16 code);

        bool
        remove(u16 active, u16 exit);

        bool
        launch(u16 code);

        bool
        launch(u16 code, u16 exit);

        bool
        finish();

        Screen*
        active();

        const Screen*
        active() const;

    private:
        HashMap<u16, Screen*> m_holder;
        HashMap<u32, u16>     m_change;

        Screen* m_active;
    };
} // namespace ma

#endif // SMAL_ENGINE_SCREEN_SCREEN_MACHINE_HPP
