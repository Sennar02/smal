#ifndef SMAL_ENTITY_ACTORS_HPP
#define SMAL_ENTITY_ACTORS_HPP

#include <smal/Entity/define.hpp>

namespace smal
{
    template <template <class> class Array = PagedArray>
    class Actors
    {
    public:
        /**
         * @brief
         *
         * @param origin
         */
        Actors(BaseOrigin* origin);

        /**
         * @brief
         *
         * @return usize
         */
        usize
        create();

        /**
         * @brief
         *
         * @param entity
         *
         * @return true
         * @return false
         */
        bool
        destroy(usize entity);

        /**
         * @brief
         *
         * @param entity
         *
         * @return usize
         */
        usize
        version(usize entity);

        /**
         * @brief
         *
         * @param entity
         *
         * @return usize
         */
        usize
        identif(usize entity);

    private:
        /**
         * @brief
         */
        ArrayList<usize, Array> m_list;

        /**
         * @brief
         */
        usize m_next;

        /**
         * @brief
         */
        usize m_size;
    };
} // namespace smal

#include <smal/Entity/impl/Actors.tpp>

#endif // SMAL_ENTITY_ACTORS_HPP
