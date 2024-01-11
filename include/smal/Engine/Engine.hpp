#ifndef SMAL_ENGINE_ENGINE_HPP
#define SMAL_ENGINE_ENGINE_HPP

#include <smal/Engine/StateManager.hpp>

namespace ma
{
    class Engine
        : public StateManager
    {
    public:
        /**
         *
         */
        Engine();

        /**
         *
         */
        bool
        execute(const String& name, u32 frames = 60u);

    private:
        /**
         *
         */
        bool
        start(const String& name);

        /**
         *
         */
        bool
        loop(u32 frames = 60u);

        /**
         *
         */
        bool
        clean();

    private:
        /**
         *
         */
        ActorManager m_actors;

        /**
         *
         */
        State* m_active;
    };
} // namespace ma

#endif // SMAL_ENGINE_ENGINE_HPP
