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
        u32
        write(FileOStream& stream, const String& string);
    };
} // namespace ma

#endif // SMAL_COMMON_FILE_FILE_WRITER_HPP
