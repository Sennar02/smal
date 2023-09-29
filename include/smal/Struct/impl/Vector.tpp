#include <smal/Struct/Vector.hpp>

namespace smal
{
    template <class T>
    Vector<T>::Vector(PageTable& table)
        : m_table {&table}
        , m_size {0}
    { }

    template <class T>
    long
    Vector<T>::get_length() const
    {
        long page = this->m_table->get_page();
        long size = this->m_table->get_size();

        return page / TYPE_SIZE * size;
    }

    template <class T>
    long
    Vector<T>::get_size() const
    {
        return this->m_size;
    }

    template <class T>
    T&
    Vector<T>::operator[](long index)
    {
        char* addr = this->m_table->lookup(
            index, TYPE_SIZE);

        return *(T*) addr;
    }

    template <class T>
    const T&
    Vector<T>::operator[](long index) const
    {
        char* addr = this->m_table->lookup(
            index, TYPE_SIZE);

        return *(T*) addr;
    }
} // namespace smal
