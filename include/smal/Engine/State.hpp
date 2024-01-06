#ifndef SMAL_ENGINE_SCREEN_HPP
#define SMAL_ENGINE_SCREEN_HPP

#include <smal/Engine/define.hpp>

namespace ma
{
    class State
    {
    public:
        /**
         *
         */
        State();

        /**
         *
         */
        virtual ~State() = default;
        /**
         *
         */
        bool
        setNext(u32 next);

        /**
         *
         */
        u32
        next();

        /**
         *
         */
        virtual bool
        onAttach();

        /**
         *
         */
        virtual bool
        onDetach();

        /**
         *
         */
        virtual void
        onEnter();

        /**
         *
         */
        virtual void
        onLeave();

        /**
         *
         */
        virtual bool
        onHandle() = 0;

        /**
         *
         */
        virtual void
        onUpdate(f32 delta) = 0;

        /**
         *
         */
        virtual void
        onRender() = 0;

    private:
        /**
         *
         */
        u32 m_next;
    };
} // namespace ma

#endif // SMAL_ENGINE_SCREEN_HPP
