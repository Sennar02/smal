#ifndef SMAL_ENGINE_ACTOR_MANAGER_HPP
#define SMAL_ENGINE_ACTOR_MANAGER_HPP

#include <smal/Engine/Actor.hpp>

namespace ma
{
    class ActorManager
    {
    public:
        /**
         *
         */
        ActorManager(u32 size);

        /**
         *
         */
        Actor
        acquire();

        /**
         *
         */
        bool
        release(const Actor& actor);

    private:
        /**
         *
         */
        Actor
        recycle();

    private:
        /**
         *
         */
        ArrayList<Actor> m_list;

        /**
         *
         */
        u32 m_count;

        /**
         *
         */
        Actor m_next;
    };
} // namespace ma

#endif // SMAL_ENGINE_ACTOR_MANAGER_HPP
