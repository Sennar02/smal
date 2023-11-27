#ifndef SMAL_COMMON_FILE_FILE_WRITER_HPP
#define SMAL_COMMON_FILE_FILE_WRITER_HPP

#include <smal/Common/define.hpp>

namespace ma
{
    class FileWriter
    {
    public:
        /**
         *
         */
        FileWriter();

        /**
         *
         */
        usize
        write(FileOStream& stream, const String& string);
    };
} // namespace ma

#endif // SMAL_COMMON_FILE_FILE_WRITER_HPP
