#ifndef SMAL_ENGINE_SCREEN_MANAGER_HPP
#define SMAL_ENGINE_SCREEN_MANAGER_HPP

#include <smal/Engine/State.hpp>

namespace ma
{
    class StateManager
    {
    public:
        /**
         *
         */
        StateManager(u32 size);

        /**
         *
         */
        bool
        attach(u32 code, State& state);

        /**
         *
         */
        bool
        detach(u32 code);

        /**
         *
         */
        bool
        launch(u32 code);

        /**
         *
         */
        State*
        active();

        /**
         *
         */
        State*
        active() const;

    private:
        /**
         *
         */
        bool
        enter();

        /**
         *
         */
        bool
        leave();

    protected:
        /**
         *
         */
        HashTable<u32, State*> m_table;

        /**
         *
         */
        ArrayStack<State*> m_stack;
    };
} // namespace ma

#endif // SMAL_ENGINE_SCREEN_MANAGER_HPP
