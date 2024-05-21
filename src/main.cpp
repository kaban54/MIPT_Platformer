#include <SFML/Graphics.hpp>
#include <stdint.h>
#include "../include/DSL.hpp"
#include "../include/app.hpp"

const unsigned int W = 1600;
const unsigned int H = 900;

int main() {
    MESSAGE_CLEAR();

    sf::RenderWindow sfwindow (sf::VideoMode (W, H), "JIJA");
    sfwindow.setFramerateLimit (260);

    EventManager event_man;

    Vec2 mousepos (0, 0);
    sf::Clock clk;
    uint64_t last_time = 0;

    App app(W, H, event_man, sfwindow);
    app.loadLevel("./levels/test_level.txt");

    while (sfwindow.isOpen()) {
        sf::Event event;

        while (sfwindow.pollEvent (event)) {
            if (event.type == sf::Event::Closed)
                sfwindow.close();
            
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    sfwindow.close();
                KeyboardContext kstate = {event.key.alt, event.key.control, event.key.shift, (Key)event.key.code};
                event_man.keyPress(kstate);
            }

            if (event.type == sf::Event::KeyReleased) {
                KeyboardContext kstate = {event.key.alt, event.key.control, event.key.shift, (Key)event.key.code};
                event_man.keyRelease(kstate);
            }

            if (event.type == sf::Event::MouseMoved) {
                mousepos.x = event.mouseMove.x;
                mousepos.y = event.mouseMove.y;
                event_man.mouseMove(MouseContext(mousepos, MouseButton::Left));
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left )
                    event_man.mousePress(MouseContext(mousepos, MouseButton::Left));
                if (event.mouseButton.button == sf::Mouse::Right)
                    event_man.mousePress(MouseContext(mousepos, MouseButton::Right));
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left )
                    event_man.mouseRelease(MouseContext(mousepos, MouseButton::Left));
                if (event.mouseButton.button == sf::Mouse::Right)
                    event_man.mouseRelease(MouseContext(mousepos, MouseButton::Right));
            }
        }

        uint64_t current_time = clk.getElapsedTime().asMicroseconds();
        if (current_time - last_time >= 10000) {
            double dt = (double)(current_time - last_time) / 1000000;
            event_man.Clock (dt);
            last_time = current_time;
        }

        sfwindow.display();
    }

    return 0;
}