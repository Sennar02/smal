#include <smal/Entity/Actors.hpp>

namespace smal
{
    template <template <class> class Array>
    Actors<Array>::Actors(BaseOrigin* origin)
        : m_list {origin}
        , m_next {(usize) -1}
        , m_size {0}
    { }

    template <template <class> class Array>
    usize
    Actors<Array>::create()
    {
        usize entity = -1;

        if ( this->m_size == 0 ) {
            entity = this->m_list.size();

            if ( this->m_list.insert(entity) )
                return entity;
        } else {
            entity = this->m_next;
            this->m_size -= 1;

            swap(this->m_list[this->m_next],
                this->m_next);
        }

        return entity;
    }

    template <template <class> class Array>
    bool
    Actors<Array>::destroy(usize entity)
    {
        if ( this->m_size != this->m_list.size() ) {
            this->m_size += 1;

            swap(this->m_list[entity],
                this->m_next);

            return true;
        }

        return false;
    }

    template <template <class> class Array>
    usize
    Actors<Array>::version(usize entity)
    {
        return -1;
    }

    template <template <class> class Array>
    usize
    Actors<Array>::identif(usize entity)
    {
        return -1;
    }
} // namespace smal
