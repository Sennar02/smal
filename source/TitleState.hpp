#ifndef SMAL_TITLE_STATE_HPP
#define SMAL_TITLE_STATE_HPP

#include <smal/Engine/import.hpp>

namespace ma
{
    class PauseState;

    class TitleState
        : public State
    {
    public:
        /**
         *
         */
        TitleState();

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

    TitleState::TitleState()
        : State()
        , m_enter {false}
    { }

    void
    TitleState::onEnter()
    {
        m_enter = true;

        printf("title\n");
        printf("Type 0 to pause\n");
        printf("Type 1 to exit\n");
    }

    bool
    TitleState::onHandle()
    {
        static const u32 size       = 256u;
        static char      buff[size] = {0};

        int code = 0;

        if ( fgets(buff, size, stdin) != 0 ) {
            sscanf(buff, "%i", &code);

            if ( code == 0 )
                return setNext(StateTag::get<PauseState>());

            if ( code == 1 )
                return false;
        }

        return true;
    }

    void
    TitleState::onUpdate(f32 delta)
    { }

    void
    TitleState::onRender()
    {
        bool enter = exch(m_enter, false);

        if ( enter )
            printf("title\n");
    }
} // namespace ma

#endif // SMAL_TITLE_STATE_HPP
