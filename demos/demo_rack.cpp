// demo_rack: shows RackView alone in a window, using FAKE data.
//  - Move the mouse: the title shows the slot under it.
//  - Left click a slot: toggles the red "selected" border (exchange mode look).
//  - Right click a slot: hides/shows that tile (placed on board or being dragged).
// Run it from the folder that contains assets/ (build\Debug\).
#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

#include "RackView.h"
#include "Theme.h"
#include "Tile.h"

using namespace scrabble;

int main() {
    Theme theme;
    if (!theme.loadFont("assets/fonts/font.ttf")) {
        std::cout << "Cannot open assets/fonts/font.ttf. Run from the folder that contains assets/.\n";
        return 1;
    }

    std::vector<Tile> rack;
    for (const char* c = "QUIZEST"; *c; ++c) rack.emplace_back(*c, Tile::pointsForLetter(*c));
    std::vector<bool> hidden(rack.size(), false);
    std::vector<bool> selected(rack.size(), false);

    sf::RenderWindow window(sf::VideoMode({900u, 780u}), "demo_rack");
    window.setFramerateLimit(60);
    RackView view(theme);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (const auto* moved = event->getIf<sf::Event::MouseMoved>()) {
                int slot = 0;
                if (view.slotAt(static_cast<float>(moved->position.x),
                                static_cast<float>(moved->position.y), slot)) {
                    window.setTitle("demo_rack - slot " + std::to_string(slot));
                } else {
                    window.setTitle("demo_rack - no slot");
                }
            } else if (const auto* press = event->getIf<sf::Event::MouseButtonPressed>()) {
                int slot = 0;
                if (view.slotAt(static_cast<float>(press->position.x),
                                static_cast<float>(press->position.y), slot)) {
                    const std::size_t i = static_cast<std::size_t>(slot);
                    if (press->button == sf::Mouse::Button::Left) selected[i] = !selected[i];
                    if (press->button == sf::Mouse::Button::Right) hidden[i] = !hidden[i];
                }
            }
        }

        window.clear(theme.backgroundColor);
        view.draw(window, rack, hidden, selected);
        window.display();
    }
    return 0;
}
