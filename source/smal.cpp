#include <smal/Engine/import.hpp>

using namespace ma;

enum Families
{
    Title = 1,
    Level,
    Saver,
};

enum Statuses
{
    Default = 1,
    Cleanup,
};

class TitleScreen
    : public Screen
{
public:
    void
    enter()
    {
        this->set_status(Statuses::Default);
    }

    u16
    handle(const sf::Event& event)
    {
        if ( event.type == sf::Event::Closed )
            return Statuses::Cleanup;

        if ( event.type == sf::Event::KeyReleased ) {
            if ( event.key.code == sf::Keyboard::Escape )
                return this->status();
        }

        return 0;
    }

    void
    render(sf::RenderTarget& target)
    {
        auto size = target.getSize();
        auto rect =
            sf::RectangleShape {(sf::Vector2f) size};

        rect.setFillColor(sf::Color::Green);

        target.draw(rect);
    }
};

class LevelScreen
    : public Screen
{
public:
    void
    enter()
    {
        this->set_status(Families::Saver);
    }

    u16
    handle(const sf::Event& event)
    {
        if ( event.type == sf::Event::Closed )
            return this->status();

        if ( event.type == sf::Event::KeyReleased ) {
            if ( event.key.code == sf::Keyboard::Escape )
                return this->status();
        }

        return 0;
    }

    void
    render(sf::RenderTarget& target)
    {
        auto size = target.getSize();
        auto rect =
            sf::RectangleShape {(sf::Vector2f) size};

        rect.setFillColor(sf::Color::Red);

        target.draw(rect);
    }
};

class SaverScreen
    : public Screen
{
public:
    void
    enter()
    {
        printf("Saving...\n");
    }

    u16
    handle()
    {
        return -1;
    }

    u16
    handle(const sf::Event& event)
    {
        return -1;
    }
};

static const usize size = 128;
static const usize page = 1024 * 128;

static char* memory = 0;

int
main(int argc, const char* argv[])
{
    memory = (char*) calloc(size, page);

    {
        PoolOrigin pool = {memory, size * page, page};
        Engine     game = {&pool, 32};

        game.screens().insert(Families::Title, new TitleScreen);
        game.screens().insert(Families::Level, new LevelScreen);
        game.screens().insert(Families::Saver, new SaverScreen);

        game.screens().insert(Families::Title, Statuses::Default, Families::Level);
        game.screens().insert(Families::Title, Statuses::Cleanup, Families::Saver);
        game.screens().insert(Families::Level, Families::Saver);

        if ( game.is_active() )
            game.loop(Families::Title);
    }

    return 0;
}
