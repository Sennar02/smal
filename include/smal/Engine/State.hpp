#ifndef SMAL_ENGINE_SCREEN_HPP
#define SMAL_ENGINE_SCREEN_HPP

#include <smal/Engine/ActorManager.hpp>

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
        setNext(const String& next);

        /**
         *
         */
        String
        next();

        /**
         *
         */
        virtual bool
        onAttach(ActorManager& actors);

        /**
         *
         */
        virtual bool
        onDetach();

        /**
         *
         */
        virtual void
        onStart();

        /**
         *
         */
        virtual void
        onClean();

        /**
         *
         */
        virtual void
        onEnter(ActorManager& actors);

        /**
         *
         */
        virtual void
        onLeave();

        /**
         *
         */
        virtual bool
        onUpdate();

        /**
         *
         */
        virtual void
        onStep(f32 delta);

        /**
         *
         */
        virtual void
        onLast();

    private:
        /**
         *
         */
        String m_next;
    };
} // namespace ma

#endif // SMAL_ENGINE_SCREEN_HPP
