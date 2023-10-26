#include <smal/Parser/Json/Lexeme.hpp>

namespace ma
{
    namespace impl
    {
        Json::LexKind g_names[] = {
            Json::LexKind::Literal,
            Json::LexKind::Literal,
            Json::LexKind::Keyword,
            Json::LexKind::Keyword,
            Json::LexKind::Separator,
            Json::LexKind::Separator,
            Json::LexKind::Separator,
            Json::LexKind::Separator,
            Json::LexKind::Separator,
            Json::LexKind::Separator,
            Json::LexKind::Auxiliary,
            Json::LexKind::Auxiliary,

            Json::LexKind::SIZE,
        };
    } // namespace impl

    namespace Json
    {
        Lexeme::Lexeme(const String& string, LexType type, u32 flag)
            : m_string {string}
            , m_type {type}
            , m_flag {flag}
        { }

        LexType
        Lexeme::type() const
        {
            return this->m_type;
        }

        LexKind
        Lexeme::kind() const
        {
            return impl::g_names[(usize) this->m_type];
        }

        usize
        Lexeme::length() const
        {
            return this->m_string.length();
        }

        u32
        Lexeme::flag() const
        {
            return this->m_flag;
        }

        const char*
        Lexeme::memory() const
        {
            return this->m_string.memory();
        }
    } // namespace Json
} // namespace ma
