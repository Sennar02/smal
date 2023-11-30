#ifndef SMAL_COMMON_FILE_FILE_OSTREAM_HPP
#define SMAL_COMMON_FILE_FILE_OSTREAM_HPP

#include <smal/Common/String.hpp>

namespace ma
{
    class FileOStream
    {
    public:
        /**
         *
         */
        FileOStream();

        /**
         *
         */
        FileOStream(String name);

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
        write(const char* memory, u32 size);

    private:
        /**
         *
         */
        void* m_source;
    };
} // namespace ma

#endif // SMAL_COMMON_FILE_FILE_OSTREAM_HPP
