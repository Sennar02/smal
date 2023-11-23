#ifndef SMAL_COMMON_READER_HPP
#define SMAL_COMMON_READER_HPP

#include <smal/Common/define.hpp>

namespace ma
{
    class FileReader
    {
    public:
        /**
         *
         *
         * @param memory
         * @param size
         */
        FileReader(char* memory = 0, usize size = 0);

        /**
         *
         *
         * @return
         */
        usize
        size() const;

        /**
         *
         *
         * @return
         */
        usize
        count() const;

        /**
         *
         *
         * @return
         */
        const char*
        memory() const;

        /**
         *
         *
         * @return
         */
        String
        string() const;

        /**
         *
         *
         * @param stream
         *
         * @return
         */
        usize
        read(File& stream);

    private:
        /**
         *
         */
        char* m_memory;

        /**
         *
         */
        usize m_size;

        /**
         *
         */
        usize m_count;
    };
} // namespace ma

#endif // SMAL_COMMON_READER_HPP
