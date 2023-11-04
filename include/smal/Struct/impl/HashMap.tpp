#include <smal/Struct/Data/HashMap.hpp>
#include <smal/Struct/Algo/Hashing.hpp>

namespace ma
{
    template <class Iden, class Type, template <class> class Array>
    HashMap<Iden, Type, Array>::HashMap()
        : m_nodes {}
        , m_array {}
        , m_count {0}
    { }

    template <class Iden, class Type, template <class> class Array>
    HashMap<Iden, Type, Array>::HashMap(BaseOrigin* origin, usize size)
        : m_nodes {origin, size}
        , m_array {origin, size}
        , m_count {0}
    {
        for ( usize i = 0; i < this->size(); i++ )
            create(this->m_nodes[i]);
    }

    template <class Iden, class Type, template <class> class Array>
    usize
    HashMap<Iden, Type, Array>::size() const
    {
        if constexpr ( sizeof(Node) > sizeof(Type) )
            return this->m_nodes.size();
        else
            return this->m_array.size();
    }

    template <class Iden, class Type, template <class> class Array>
    usize
    HashMap<Iden, Type, Array>::count() const
    {
        return this->m_count;
    }

    template <class Iden, class Type, template <class> class Array>
    f32
    HashMap<Iden, Type, Array>::load() const
    {
        f32 size  = this->size();
        f32 count = this->m_count;

        return Math::div(count, size);
    }

    template <class Iden, class Type, template <class> class Array>
    bool
    HashMap<Iden, Type, Array>::is_empty() const
    {
        return this->m_count == 0;
    }

    template <class Iden, class Type, template <class> class Array>
    bool
    HashMap<Iden, Type, Array>::is_full() const
    {
        return this->m_count == this->size();
    }

    template <class Iden, class Type, template <class> class Array>
    template <class Func>
    bool
    HashMap<Iden, Type, Array>::contains(const Iden& iden, Func comp) const
    {
        const Node* node  = 0;
        usize       start = this->index(iden);
        usize       index = start;

        if ( this->is_empty() == true ) return false;

        do {
            node  = &this->m_nodes[index];
            index = this->next(index);

            if ( node->dist != s_empty ) {
                if ( comp(iden, node->iden) == true )
                    return true;
            } else
                break;
        } while ( start != index );

        return false;
    }

    template <class Iden, class Type, template <class> class Array>
    bool
    HashMap<Iden, Type, Array>::contains(const Iden& iden) const
    {
        auto comp = [](const Iden& value, const Iden& other) {
            return value == other;
        };

        return this->contains(iden, comp);
    }

    template <class Iden, class Type, template <class> class Array>
    template <class Func>
    void
    HashMap<Iden, Type, Array>::for_each(Func oper) const
    {
        const Node* node = 0;

        if ( this->is_empty() == true )
            return;

        for ( usize i = 0; i < this->size(); i++ ) {
            node = &this->m_nodes[i];

            if ( node->dist != s_empty )
                oper(node->iden, this->m_array[i]);
        }
    }

    template <class Iden, class Type, template <class> class Array>
    template <class Func>
    bool
    HashMap<Iden, Type, Array>::insert(const Iden& iden, const Type& value, Func comp)
    {
        Entry entry = {
            value, {iden, 0}
        };

        Node* node  = 0;
        Type* item  = 0;
        usize start = this->index(iden);
        usize index = start;

        if ( this->is_full() == true ) return false;

        if ( this->contains(iden, comp) == false ) {
            do {
                node  = &this->m_nodes[index];
                item  = &this->m_array[index];
                index = this->next(index);

                if ( node->dist == s_empty ) {
                    this->m_count += 1;

                    create(*item, entry.value);
                    create(*node, entry.node);

                    return true;
                }

                if ( node->dist < entry.node.dist ) {
                    swap(*node, entry.node);
                    swap(*item, entry.value);
                }

                entry.node.dist += 1;
            } while ( start != index );
        }

        return false;
    }

    template <class Iden, class Type, template <class> class Array>
    bool
    HashMap<Iden, Type, Array>::insert(const Iden& iden, const Type& value)
    {
        auto comp = [](auto& value, auto& other) {
            return value == other;
        };

        return this->insert(iden, value, comp);
    }

    template <class Iden, class Type, template <class> class Array>
    template <class Func>
    bool
    HashMap<Iden, Type, Array>::remove(const Iden& iden, Func comp)
    {
        Node* node  = 0;
        usize start = this->index(iden);
        usize index = start;

        if ( this->contains(iden, comp) == true ) {
            do {
                node  = &this->m_nodes[index];
                index = this->next(index);

                if ( node->dist != s_empty ) {
                    if ( comp(iden, node->iden) ) {
                        this->m_count -= 1;
                        node->dist = s_empty;

                        return true;
                    }
                } else
                    break;
            } while ( start != index );
        }

        return false;
    }

    template <class Iden, class Type, template <class> class Array>
    bool
    HashMap<Iden, Type, Array>::remove(const Iden& iden)
    {
        auto comp = [](auto& value, auto& other) {
            return value == other;
        };

        return this->remove(iden, comp);
    }

    template <class Iden, class Type, template <class> class Array>
    Array<Type>&
    HashMap<Iden, Type, Array>::values()
    {
        return this->m_array;
    }

    template <class Iden, class Type, template <class> class Array>
    const Array<Type>&
    HashMap<Iden, Type, Array>::values() const
    {
        return this->m_array;
    }

    template <class Iden, class Type, template <class> class Array>
    template <class Func>
    Type&
    HashMap<Iden, Type, Array>::find(const Iden& iden, Func comp)
    {
        Node* node  = 0;
        Type* item  = 0;
        usize start = this->index(iden);
        usize index = start;

        if ( this->contains(iden, comp) == true ) {
            do {
                node  = &this->m_nodes[index];
                item  = &this->m_array[index];
                index = this->next(index);

                if ( node->dist != s_empty ) {
                    if ( comp(iden, node->iden) )
                        return *item;
                } else
                    break;
            } while ( start != index );
        }

        return *(Type*) 0;
    }

    template <class Iden, class Type, template <class> class Array>
    template <class Func>
    const Type&
    HashMap<Iden, Type, Array>::find(const Iden& iden, Func comp) const
    {
        Node* node  = 0;
        Type* item  = 0;
        usize start = this->index(iden);
        usize index = start;

        if ( this->contains(iden, comp) == true ) {
            do {
                node  = &this->m_nodes[index];
                item  = &this->m_array[index];
                index = this->next(index);

                if ( node->dist != s_empty ) {
                    if ( comp(iden, node->iden) )
                        return *item;
                } else
                    break;
            } while ( start != index );
        }

        return *(Type*) 0;
    }

    template <class Iden, class Type, template <class> class Array>
    Type&
    HashMap<Iden, Type, Array>::find(const Iden& iden)
    {
        auto comp = [](auto& value, auto& other) {
            return value == other;
        };

        return this->find(iden, comp);
    }

    template <class Iden, class Type, template <class> class Array>
    const Type&
    HashMap<Iden, Type, Array>::find(const Iden& iden) const
    {
        auto comp = [](auto& value, auto& other) {
            return value == other;
        };

        return this->find(iden, comp);
    }

    template <class Iden, class Type, template <class> class Array>
    Type&
    HashMap<Iden, Type, Array>::operator[](const Iden& iden)
    {
        return this->find(iden);
    }

    template <class Iden, class Type, template <class> class Array>
    const Type&
    HashMap<Iden, Type, Array>::operator[](const Iden& iden) const
    {
        return this->find(iden);
    }

    template <class Iden, class Type, template <class> class Array>
    usize
    HashMap<Iden, Type, Array>::index(const Iden& iden) const
    {
        return Math::mod(hash(iden), this->size());
    }

    template <class Iden, class Type, template <class> class Array>
    usize
    HashMap<Iden, Type, Array>::next(usize index) const
    {
        return Math::mod(index + 1, this->size());
    }
} // namespace ma
