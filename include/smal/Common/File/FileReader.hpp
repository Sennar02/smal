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
        FileReader(char* memory = 0, u32 size = 0);

        /**
         *
         */
        u32
        size() const;

        /**
         *
         */
        u32
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
        u32
        read(FileIStream& stream);

    private:
        /**
         *
         */
        char* m_memory;

        /**
         *
         */
        u32 m_size;

        /**
         *
         */
        u32 m_count;
    };
} // namespace ma

#endif // SMAL_COMMON_FILE_FILE_READER_HPP
