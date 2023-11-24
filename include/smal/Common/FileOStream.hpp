#ifndef SMAL_COMMON_FILE_OSTREAM_HPP
#define SMAL_COMMON_FILE_OSTREAM_HPP

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
        usize
        write(const char* memory, usize size);

    private:
        /**
         *
         */
        void* m_source;
    };
} // namespace ma

#endif // SMAL_COMMON_FILE_OSTREAM_HPP
