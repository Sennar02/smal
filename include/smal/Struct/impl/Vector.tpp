#include <smal/Struct/Vector.hpp>

namespace smal
{
    template <class T>
    Vector<T>::Vector(PageAlloc& origin, PageTable& ptable)
        : m_origin {&origin}
        , m_ptable {&ptable}
        , m_size {0}
    { }

    template <class T>
    Vector<T>::~Vector()
    { }

    template <class T>
    long
    Vector<T>::get_length() const
    {
        long length = this->m_ptable->get_page();
        long number = this->m_ptable->get_size();

        return length / TYPE_SIZE * number;
    }

    template <class T>
    long
    Vector<T>::get_size() const
    {
        return this->m_size;
    }

    template <class T>
    bool
    Vector<T>::expand(long pages)
    {
        long start = this->m_ptable->get_size();

        for ( long i = start; i < start + pages; i++ ) {
            Page page = this->m_origin->reserve();
            bool oper = this->m_ptable->insert(page, i);

            if ( oper == false ) {
                this->m_origin->reclaim(page);

                return false;
            }
        }

        return true;
    }

    template <class T>
    bool
    Vector<T>::shrink(long pages)
    {
        for ( long i = 0; i < pages; i++ ) {
            bool oper = this->m_ptable->remove();

            if ( oper == false )
                return false;
        }

        return true;
    }

    template <class T>
    T&
    Vector<T>::operator[](long index)
    {
        char* addr = this->m_ptable->lookup(
            index, TYPE_SIZE);

        return *(T*) addr;
    }

    template <class T>
    const T&
    Vector<T>::operator[](long index) const
    {
        char* addr = this->m_ptable->lookup(
            index, TYPE_SIZE);

        return *(T*) addr;
    }
} // namespace smal
