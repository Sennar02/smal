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
        isActive() const;

        /**
         *
         */
        bool
        loop(u32 code, u32 frames = 60u);

    private:
        /**
         *
         */
        bool
        handle();

        /**
         *
         */
        void
        update();

        /**
         *
         */
        void
        render();

    private:
        /**
         *
         */
        bool m_active;
    };
} // namespace ma

#endif // SMAL_ENGINE_ENGINE_HPP
