#include "Theme.h"
#include <iostream>

namespace scrabble {

Theme::Theme() {
    if (!font.openFromFile("assets/fonts/font.ttf")) {
        std::cerr << "[Warning] Could not load assets/fonts/font.ttf." << std::endl;
    }
}

bool Theme::loadFont(const std::string& path) {
    return font.openFromFile(path);
}

}