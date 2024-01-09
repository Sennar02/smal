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
        attach(const String& name, State& state);

        /**
         *
         */
        bool
        detach(const String& name);

        /**
         *
         */
        State*
        launch(const String& name);

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
        change(const String& name);

    protected:
        /**
         *
         */
        HashTable<String, State*> m_table;

        /**
         *
         */
        ArrayStack<State*> m_stack;
    };
} // namespace ma

#endif // SMAL_ENGINE_SCREEN_MANAGER_HPP
