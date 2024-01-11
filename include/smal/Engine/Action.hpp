#ifndef SMAL_ENGINE_ACTION_HPP
#define SMAL_ENGINE_ACTION_HPP

#include <smal/Engine/define.hpp>

namespace ma
{
    class Action
    {
    public:
        /**
         *
         */
        virtual ~Action() = default;

        /**
         *
         */
        virtual void
        perform() = 0;

        /**
         *
         */
        virtual void
        reverse();
    };
} // namespace ma

#endif // SMAL_ENGINE_ACTION_HPP
