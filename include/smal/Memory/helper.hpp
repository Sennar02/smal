#ifndef SMAL_MEMORY_HELPER_HPP
#define SMAL_MEMORY_HELPER_HPP

#include <smal/Memory/define.hpp>

namespace smal::Memory
{
    /**
     * @brief
     *
     * @param memory
     * @param length
     * @param value
     */
    void
    set(void* memory, usize length, char value);
} // namespace smal::Memory

#endif // SMAL_MEMORY_HELPER_HPP
