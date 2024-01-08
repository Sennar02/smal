#ifndef SMAL_ENGINE_SCREEN_MANAGER_HPP
#define SMAL_ENGINE_SCREEN_MANAGER_HPP

#include <smal/Engine/State.hpp>

namespace ma
{
    struct StateTag;

    class StateManager
        : public AssetManager
    {
    public:
        /**
         *
         */
        StateManager(u32 size);

        /**
         *
         */
        template <class Type>
        bool
        attach(Type& state);

        /**
         *
         */
        template <class Type>
        bool
        detach();

        /**
         *
         */
        bool
        launch(u32 index);

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

#include <smal/Engine/inline/StateManager.inl>

#endif // SMAL_ENGINE_SCREEN_MANAGER_HPP
