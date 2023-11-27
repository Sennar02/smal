#ifndef SMAL_COMMON_FILE_FILE_READER_HPP
#define SMAL_COMMON_FILE_FILE_READER_HPP

#include <smal/Common/define.hpp>

namespace ma
{
    class FileReader
    {
    public:
        /**
         *
         */
        FileReader(char* memory = 0, usize size = 0);

        /**
         *
         */
        usize
        size() const;

        /**
         *
         */
        usize
        count() const;

        /**
         *
         */
        const char*
        memory() const;

        /**
         *
         */
        String
        string() const;

        /**
         *
         */
        usize
        read(FileIStream& stream);

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

#endif // SMAL_COMMON_FILE_FILE_READER_HPP
