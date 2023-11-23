#ifndef SMAL_COMMON_FILE_SYSTEM_HPP
#define SMAL_COMMON_FILE_SYSTEM_HPP

#include <smal/Common/String.hpp>

namespace ma
{
    class FileSystem
    {
    public:
        /**
         *
         */
        virtual ~FileSystem() = delete;

        /**
         *
         *
         * @param name
         *
         * @return True.
         * @return False.
         */
        static bool
        exists(String name);

        /**
         *
         *
         * @param name
         *
         * @return True.
         * @return False.
         */
        static File
        create(String name);

        /**
         *
         *
         * @param name
         *
         * @return True.
         * @return False.
         */
        static bool
        destroy(String name);
    };
} // namespace ma

#endif // SMAL_COMMON_FILE_SYSTEM_HPP
