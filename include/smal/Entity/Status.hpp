#ifndef SMAL_ENTITY_ACTORS_HPP
#define SMAL_ENTITY_ACTORS_HPP

#include <smal/Entity/define.hpp>

namespace smal
{
    template <template <class> class Array = PagedArray>
    class Status
    {
    public:
        /**
         *
         *
         * @param origin
         */
        Status(BaseOrigin* origin);

        /**
         *
         *
         * @return usize
         */
        usize
        create();

        /**
         *
         *
         * @param entity
         *
         * @return True.
         * @return False.
         */
        bool
        destroy(usize entity);

        /**
         *
         *
         * @param entity
         *
         * @return usize
         */
        usize
        version(usize entity);

        /**
         *
         *
         * @param entity
         *
         * @return usize
         */
        usize
        identif(usize entity);

    private:
        /**
         *
         */
        ArrayList<usize, Array> m_list;

        /**
         *
         */
        usize m_next;

        /**
         *
         */
        usize m_size;
    };
} // namespace smal

#include <smal/Entity/impl/Status.tpp>

#endif // SMAL_ENTITY_ACTORS_HPP
