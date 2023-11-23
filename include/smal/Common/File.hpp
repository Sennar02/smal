#ifndef SMAL_COMMON_FILE_HPP
#define SMAL_COMMON_FILE_HPP

#include <smal/Common/String.hpp>

namespace ma
{
    enum class FileMode : u8
    {
        // Read operation, fails if file does not exist.
        Read,
        // Write operation, appends if file exists.
        WritePast,
        // Write operation, clears if file exists.
        WriteWipe,

        SIZE,
    };

    class File
    {
    public:
        /**
         *
         */
        File(String name = {});

        /**
         *
         */
        virtual ~File() = default;

        /**
         *
         *
         * @return True.
         * @return False.
         */
        bool
        is_open() const;

        /**
         *
         *
         * @param mode
         *
         * @return True.
         * @return False.
         */
        bool
        is_open(FileMode mode) const;

        /**
         *
         *
         * @return
         */
        String
        name() const;

        /**
         *
         *
         * @param mode
         * @param name
         *
         * @return
         */
        File&
        open(FileMode mode, String name = {});

        /**
         *
         *
         * @param mode
         * @param oper
         * @param name
         *
         * @return
         */
        template <class Func>
        File&
        open(FileMode mode, Func oper, String name = {});

        /**
         *
         *
         * @return
         */
        File&
        close();

        /**
         *
         *
         * @param oper
         *
         * @return
         */
        template <class Func>
        File&
        close(Func oper);

        /**
         *
         *
         * @param mode
         * @param oper
         * @param name
         *
         * @return
         */
        template <class Func>
        File&
        call(FileMode mode, Func oper, String name = {});

        /**
         *
         *
         * @param memory
         * @param size
         *
         * @return
         */
        usize
        read(char* memory, usize size);

        /**
         *
         *
         * @param memory
         * @param size
         *
         * @return
         */
        usize
        write(const char* memory, usize size);

    private:
        /**
         *
         */
        String m_name;

        /**
         *
         */
        FILE* m_file;

        /**
         *
         */
        FileMode m_mode;

        /**
         *
         */
        bool m_open;
    };
} // namespace ma

#include <smal/Common/impl/File.tpp>

#endif // SMAL_COMMON_FILE_HPP
