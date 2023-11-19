#include <smal/Engine/import.hpp>
#include <smal/Parser/import.hpp>

using namespace ma;

struct ScreenTransit
{
    u16 active;
    u16 coming;
    u16 exit;
};

class Loader
    : public Client
{
public:
    Loader(BaseOrigin* origin)
        : names {origin, 64}
        , exits {origin, 64}
        , table {origin, 64}
    { }

    bool
    string(const char* string, usize length)
    {
        if ( this->m_status == 1 ) {
            if ( strncmp("names", this->m_name, this->m_size) == 0 )
                this->names.insert({string, length}, ++this->m_names);

            if ( strncmp("exits", this->m_name, this->m_size) == 0 )
                this->exits.insert({string, length}, ++this->m_exits);
        }

        if ( this->m_status == 2 ) {
            if ( strncmp("active", this->m_name, this->m_size) == 0 )
                this->m_screen.active = this->names[{string, length}];

            if ( strncmp("coming", this->m_name, this->m_size) == 0 )
                this->m_screen.coming = this->names[{string, length}];

            if ( strncmp("exit", this->m_name, this->m_size) == 0 )
                this->m_screen.exit = this->exits[{string, length}];
        }

        return true;
    }

    bool
    name(const char* string, usize length)
    {
        this->m_name = string;
        this->m_size = length;

        if ( strncmp("definitions", string, length) == 0 )
            this->m_status = 1;

        if ( strncmp("transitions", string, length) == 0 )
            this->m_status = 2;

        return true;
    }

    bool
    object_stop(usize, usize)
    {
        if ( this->m_status == 2 ) {
            if ( this->m_screen.active != (u16) -1 && this->m_screen.coming != (u16) -1 )
                this->table.insert(this->m_screen);

            this->m_screen.active = (u16) -1;
            this->m_screen.coming = (u16) -1;
            this->m_screen.exit   = (u16) -1;
        }

        return true;
    }

public:
    ma::HashMap<ma::String, u16> names;
    ma::HashMap<ma::String, u16> exits;
    ma::ArrayList<ScreenTransit> table;

private:
    usize         m_names  = 0;
    usize         m_exits  = 0;
    const char*   m_name   = 0;
    usize         m_size   = 0;
    usize         m_status = 0;
    ScreenTransit m_screen = {};
};
