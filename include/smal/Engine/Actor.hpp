#ifndef SMAL_ENGINE_ACTOR_HPP
#define SMAL_ENGINE_ACTOR_HPP

#include <smal/Engine/define.hpp>

namespace ma
{
    class Actor
    {
    public:
        /**
         *
         */
        Actor();

        /**
         *
         */
        u32
        identif() const;

        /**
         *
         */
        u32
        version() const;

    private:
        friend class ActorManager;

        /**
         *
         */
        Actor(u32 code, u32 vers);

    private:
        /**
         *
         */
        u32 m_code;

        /**
         *
         */
        u32 m_vers;
    };
} // namespace ma

#endif // SMAL_ENGINE_ACTOR_HPP
