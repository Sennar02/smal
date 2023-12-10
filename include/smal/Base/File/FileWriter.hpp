#ifndef SMAL_BASE_FILE_FILE_WRITER_HPP
#define SMAL_BASE_FILE_FILE_WRITER_HPP

#include <smal/Base/define.hpp>

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

#endif // SMAL_BASE_FILE_FILE_WRITER_HPP
