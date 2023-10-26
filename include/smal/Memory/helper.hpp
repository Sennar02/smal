#ifndef SMAL_MEMORY_HELPER_HPP
#define SMAL_MEMORY_HELPER_HPP

#include <smal/Memory/define.hpp>

namespace ma::Memory
{
    /**
     * Sets the value of a certain amount of bytes
     * in a memory buffer.
     *
     * @param memory Pointer to buffer.
     * @param length Amount of bytes.
     * @param value  Value of each byte.
     */
    void
    set(void* memory, usize length, char value);
} // namespace ma::Memory

#endif // SMAL_MEMORY_HELPER_HPP
