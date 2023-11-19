#include <smal/Engine/import.hpp>
#include <smal/Parser/import.hpp>

using namespace ma;

class TitleScreen
    : public Screen
{
public:
    TitleScreen(const HashMap<String, u16>& names,
        const HashMap<String, u16>&         exits)
        : Screen(names, exits)
    { }

    void
    enter()
    {
        this->set_exit(exits["Default"]);
    }

    u16
    handle(const sf::Event& event)
    {
        if ( event.type == sf::Event::Closed )
            return exits["Cleanup"];

        if ( event.type == sf::Event::KeyReleased ) {
            if ( event.key.code == sf::Keyboard::Escape )
                return this->exit();
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
    LevelScreen(const HashMap<String, u16>& names,
        const HashMap<String, u16>&         exits)
        : Screen(names, exits)
    { }

    void
    enter()
    { }

    u16
    handle(const sf::Event& event)
    {
        if ( event.type == sf::Event::Closed )
            return this->exit();

        if ( event.type == sf::Event::KeyReleased ) {
            if ( event.key.code == sf::Keyboard::Escape )
                return this->exit();
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

class ExitScreen
    : public Screen
{
public:
    ExitScreen(const HashMap<String, u16>& names,
        const HashMap<String, u16>&        exits)
        : Screen(names, exits)
    { }

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
