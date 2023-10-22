#include <smal/Parser/Json/Piece.hpp>

namespace smal
{
    namespace impl
    {
        Json::PieceKind g_piece_kinds[] = {
            Json::PieceKind::Value,
            Json::PieceKind::Value,
            Json::PieceKind::Value,
            Json::PieceKind::Value,
            Json::PieceKind::Value,
            Json::PieceKind::Value,
            Json::PieceKind::Value,
            Json::PieceKind::Value,
            Json::PieceKind::Value,
            Json::PieceKind::Value,
            Json::PieceKind::Delim,
            Json::PieceKind::Delim,
            Json::PieceKind::Extra,
            Json::PieceKind::Extra,
            Json::PieceKind::Extra,
            Json::PieceKind::SIZE,
        };
    } // namespace impl

    namespace Json
    {
        Piece::Piece(const String& string, PieceType type)
            : m_string {string}
            , m_type {type}
        { }

        PieceType
        Piece::type() const
        {
            return this->m_type;
        }

        PieceKind
        Piece::kind() const
        {
            return impl::g_piece_kinds[(usize) this->m_type];
        }

        usize
        Piece::length() const
        {
            return this->m_string.length();
        }

        const char*
        Piece::memory() const
        {
            return this->m_string.memory();
        }
    } // namespace Json
} // namespace smal
