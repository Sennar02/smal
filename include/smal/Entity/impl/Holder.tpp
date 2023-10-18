#include <smal/Entity/Holder.hpp>

namespace smal
{
    namespace impl
    {
        class Identif
        {
        private:
            inline static usize next = 0;

        public:
            template <class Type>
            inline static const usize of =
                next++;
        };
    } // namespace impl

    template <template <class> class Pool>
    Holder<Pool>::Holder(BaseOrigin* origin)
        : m_array {origin}
    { }

    template <template <class> class Pool>
    template <class Type>
    bool
    Holder<Pool>::has() const
    {
        usize type = impl::Identif::of<Type>;

        if ( this->m_array.length() <= type )
            return false;

        return this->m_array[type] != 0;
    }

    template <template <class> class Pool>
    template <class Type>
    bool
    Holder<Pool>::give(Pool<Type>* pool)
    {
        usize type = impl::Identif::of<Type>;

        if ( this->has<Type>() == true )
            return false;

        if ( this->m_array.length() <= type )
            this->m_array.resize(type + 16);

        if ( this->m_array.length() > type ) {
            this->m_array[type] = pool;

            return true;
        }

        return false;
    }

    template <template <class> class Pool>
    template <class Type>
    bool
    Holder<Pool>::take()
    {
        usize type = impl::Identif::of<Type>;

        if ( this->contains(type) == false )
            return false;

        this->m_array[type] = 0;

        return true;
    }

    template <template <class> class Pool>
    template <class Type>
    Pool<Type>*
    Holder<Pool>::find()
    {
        usize type = impl::Identif::of<Type>;

        if ( this->has<Type>() == true )
            return (Pool<Type>*) this->m_array[type];

        return 0;
    }

    template <template <class> class Pool>
    template <class Type>
    const Pool<Type>*
    Holder<Pool>::find() const
    {
        usize type = impl::Identif::of<Type>;

        if ( this->has<Type>() == true )
            return (Pool<Type>*) this->m_array[type];

        return 0;
    }

    template <template <class> class Pool>
    template <class Type>
    bool
    Holder<Pool>::has(usize entity) const
    {
        usize type = impl::Identif::of<Type>;

        if ( this->has<Type>() == true )
            return ((Pool<Type>*) this->m_array[type])
                ->contains(entity);

        return false;
    }

    template <template <class> class Pool>
    template <class Type>
    bool
    Holder<Pool>::give(usize entity, const Type& attrib)
    {
        usize type = impl::Identif::of<Type>;

        if ( this->has<Type>() == true )
            return ((Pool<Type>*) this->m_array[type])
                ->insert(entity, attrib);

        return false;
    }

    template <template <class> class Pool>
    template <class Type>
    bool
    Holder<Pool>::give(usize entity, Type&& attrib)
    {
        usize type = impl::Identif::of<Type>;

        if ( this->has<Type>() == true )
            return ((Pool<Type>*) this->m_array[type])
                ->insert(entity, move(attrib));

        return false;
    }

    template <template <class> class Pool>
    template <class Type>
    bool
    Holder<Pool>::take(usize entity)
    {
        usize type = impl::Identif::of<Type>;

        if ( this->has<Type>() == true )
            return ((Pool<Type>*) this->m_array[type])
                ->remove(entity);

        return false;
    }

    template <template <class> class Pool>
    template <class Type>
    Type&
    Holder<Pool>::find(usize entity)
    {
        usize type = impl::Identif::of<Type>;

        return ((Pool<Type>*) this->m_array[type])
            ->find(entity);
    }

    template <template <class> class Pool>
    template <class Type>
    const Type&
    Holder<Pool>::find(usize entity) const
    {
        usize type = impl::Identif::of<Type>;

        return ((Pool<Type>*) this->m_array[type])
            ->find(entity);
    }
} // namespace smal
