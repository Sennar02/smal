#ifndef SMAL_MEMORY_ALLOC_CHAIN_ALLOC_HPP
#define SMAL_MEMORY_ALLOC_CHAIN_ALLOC_HPP

#include <smal/Memory/Alloc/BaseAlloc.hpp>

namespace ma
{
    template <class Alloc, class... Rest>
    class ChainAlloc<Alloc, Rest...>
        : public BaseAlloc
    {
    public:
        /**
         *
         */
        ChainAlloc();

        /**
         *
         */
        ChainAlloc(const Alloc& alloc, const Rest&... rest);

        /**
         *
         */
        template <u32 Index>
        auto&
        alloc();

        /**
         *
         */
        template <u32 Index>
        const auto&
        alloc() const;

        /**
         *
         */
        virtual u32
        avail() const;

        /**
         *
         */
        virtual bool
        prepare();

        /**
         *
         */
        virtual char*
        acquire(u32 size);

        /**
         *
         */
        virtual bool
        release(void* memory);

        /**
         *
         */
        virtual bool
        release();

    private:
        /**
         *
         */
        Alloc m_alloc;

        /**
         *
         */
        ChainAlloc<Rest...> m_rest;
    };

    template <>
    class ChainAlloc<>
        : public BaseAlloc
    {
    public:
        /**
         *
         */
        ChainAlloc();

        /**
         *
         */
        virtual u32
        avail() const;

        /**
         *
         */
        virtual bool
        prepare();

        /**
         *
         */
        virtual char*
        acquire(u32 size);

        /**
         *
         */
        virtual bool
        release(void* memory);

        /**
         *
         */
        virtual bool
        release();
    };

    template <class... Allocs>
    ChainAlloc(const Allocs&...)
        -> ChainAlloc<Allocs...>;
} // namespace ma

#include <smal/Memory/Alloc/impl/ChainAlloc.tpp>

#endif // SMAL_MEMORY_ALLOC_CHAIN_ALLOC_HPP
