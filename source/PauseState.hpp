#ifndef SMAL_PAUSE_STATE_HPP
#define SMAL_PAUSE_STATE_HPP

#include <smal/Engine/import.hpp>

namespace ma
{
    class PauseState
        : public State
    {
    public:
        /**
         *
         */
        PauseState();

        /**
         *
         */
        void
        onEnter();

        /**
         *
         */
        bool
        onHandle();

        /**
         *
         */
        void
        onUpdate(f32 delta);

        /**
         *
         */
        void
        onRender();

    private:
        /**
         *
         */
        bool m_enter;
    };

    PauseState::PauseState()
        : State()
        , m_enter {false}
    { }

    void
    PauseState::onEnter()
    {
        m_enter = true;

        printf("pause\n");
        printf("Type 0 to resume\n");
    }

    bool
    PauseState::onHandle()
    {
        static const u32 size       = 256u;
        static char      buff[size] = {0};

        int code = 0;

        if ( fgets(buff, size, stdin) != 0 ) {
            sscanf(buff, "%i", &code);

            if ( code == 0 )
                return false;
        }

        return true;
    }

    void
    PauseState::onUpdate(f32 delta)
    { }

    void
    PauseState::onRender()
    {
        bool enter = exch(m_enter, false);

        if ( enter )
            printf("pause\n");
    }
} // namespace ma

#endif // SMAL_PAUSE_STATE_HPP
