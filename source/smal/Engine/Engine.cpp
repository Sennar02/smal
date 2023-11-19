#include <smal/Engine/Engine.hpp>

namespace ma
{
    Engine::Engine(BaseOrigin* origin, usize size)
        : m_window {}
        , m_clock {}
        , m_screens {origin, size}
        , m_active {true}
    { }

    bool
    Engine::is_active() const
    {
        return this->m_active;
    }

    void
    Engine::loop(u16 code, usize frames)
    {
        sf::Time  slice = sf::seconds(1.f / frames);
        sf::Time  delta;
        sf::Event event;

        this->m_active = this->m_screens.launch(code);

        if ( this->m_active ) {
            this->m_window.create(
                sf::VideoMode {1280, 720},
                "SMAL",
                sf::Style::Default);
        } else
            return;

        while ( true ) {
            delta += this->m_clock.restart();

            while ( this->m_window.pollEvent(event) )
                this->handle(event);

            this->handle();

            if ( this->m_active ) {
                for ( ; delta < slice; delta -= slice )
                    this->update(slice.asSeconds());

                this->render();
            } else
                break;
        }

        this->m_screens.finish();
        this->m_window.close();
    }

    ScreenMachine&
    Engine::screens()
    {
        return this->m_screens;
    }

    const ScreenMachine&
    Engine::screens() const
    {
        return this->m_screens;
    }

    void
    Engine::handle()
    {
        Screen* screen = this->m_screens.active();
        u16     code = 0;
        u16     exit = 0;

        if ( screen != 0 ) {
            code = screen->code();
            exit = screen->handle();

            if ( exit != 0 ) {
                this->m_active = this->m_screens.launch(
                    code, exit);
            }
        } else
            this->m_active = false;
    }

    void
    Engine::handle(const sf::Event& event)
    {
        Screen* screen = this->m_screens.active();
        u16     code = 0;
        u16     exit = 0;

        if ( screen != 0 ) {
            code = screen->code();
            exit = screen->handle(event);

            if ( exit != 0 ) {
                this->m_active = this->m_screens.launch(
                    code, exit);
            }
        } else
            this->m_active = false;
    }

    void
    Engine::update(f32 delta)
    {
        Screen* screen = this->m_screens.active();

        if ( screen != 0 )
            screen->update(delta);
    }

    void
    Engine::render()
    {
        Screen* screen = this->m_screens.active();

        this->m_window.clear(sf::Color::White);

        if ( screen != 0 )
            screen->render(this->m_window);

        this->m_window.display();
    }
} // namespace ma
