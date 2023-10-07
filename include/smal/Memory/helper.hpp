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
     * @param byte
     */
    void
    set(void* memory, long length, char byte);
} // namespace smal::Memory

#endif // SMAL_MEMORY_HELPER_HPP
