#ifndef SMAL_MEMORY_DEFINE_HPP
#define SMAL_MEMORY_DEFINE_HPP

namespace smal
{
    namespace Memory
    {
        /**
         * @brief
         *
         * @param memory
         * @param length
         * @param byte
         */
        void
        set(void* memory, long length, char byte);
    }; // namespace Memory

    class Page;
    class PageAlloc;
} // namespace smal

#endif // SMAL_MEMORY_DEFINE_HPP
