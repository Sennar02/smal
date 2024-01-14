#include <smal/Memory/Array.hpp>

namespace ma
{
    template <class Item, class Layout>
    template <class Origin, class... Args>
    Array<Item, Layout>::Array(Origin& origin, u32 items, Args&&... args)
        : Layout(origin, items, s_size, forw<Args>(args)...)
    { }

    template <class Item, class Layout>
    Array<Item, Layout>::Array(const Layout& layout)
        : Layout(layout)
    { }

    template <class Item, class Layout>
    u32
    Array<Item, Layout>::length() const
    {
        return Layout::length(s_size);
    }

    template <class Item, class Layout>
    bool
    Array<Item, Layout>::resize(u32 length)
    {
        return Layout::resize(length, s_size);
    }

    template <class Item, class Layout>
    Item&
    Array<Item, Layout>::find(u32 index) const
    {
        return (Item&) Layout::find(index, s_size);
    }

    template <class Item, class Layout>
    Item&
    Array<Item, Layout>::operator[](u32 index) const
    {
        return (Item&) Layout::find(index, s_size);
    }
} // namespace ma
