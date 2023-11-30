#ifndef SMAL_COMMON_FILE_FILE_ISTREAM_HPP
#define SMAL_COMMON_FILE_FILE_ISTREAM_HPP

#include <smal/Common/String.hpp>

namespace ma
{
    class FileIStream
    {
    public:
        /**
         *
         */
        FileIStream();

        /**
         *
         */
        FileIStream(String name);

        /**
         *
         */
        bool
        open(String name);

        /**
         *
         */
        bool
        close();

        /**
         *
         */
        u32
        read(char* memory, u32 size);

    private:
        /**
         *
         */
        void* m_source;
    };
} // namespace ma

#endif // SMAL_COMMON_FILE_FILE_ISTREAM_HPP
