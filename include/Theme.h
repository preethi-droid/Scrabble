#ifndef THEME_H
#define THEME_H

#include <SFML/Graphics.hpp>
#include <string>

namespace scrabble {

class Theme {
public:
    Theme();
    bool loadFont(const std::string& path);

    sf::Font font;
    sf::Color backgroundColor{240, 240, 245, 255};
    sf::Color boardBackground{200, 190, 175, 255};
    sf::Color normalCellColor{230, 220, 205, 255};
    sf::Color doubleLetterColor{173, 216, 230, 255};
    sf::Color tripleLetterColor{0, 0, 255, 100};
    sf::Color doubleWordColor{255, 182, 193, 255};
    sf::Color tripleWordColor{255, 69, 0, 255};
    sf::Color textColor{20, 20, 20, 255};
    sf::Color tileColor{245, 222, 179, 255};
    sf::Color tileBorderColor{139, 69, 19, 255};
};

}

#endif