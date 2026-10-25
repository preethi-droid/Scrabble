#ifndef RACK_VIEW_H
#define RACK_VIEW_H

// DRAFT v0.1 - owner: Mirudhulaa. SFML allowed (gui side).
#include <SFML/Graphics.hpp>
#include <vector>

#include "Theme.h"
#include "Tile.h"
#include "ViewGeometry.h"

namespace scrabble {

class RackView {
public:
    explicit RackView(const Theme& theme);

    // Draws the 7 slots and the tiles of the rack.
    //  hidden[i]   true -> do not draw tile i (it is placed on the board or being dragged)
    //  selected[i] true -> highlight tile i (exchange mode)
    // Both vectors may be empty or shorter than the rack; missing entries mean false.
    void draw(sf::RenderWindow& window, const std::vector<Tile>& rack,
              const std::vector<bool>& hidden = {},
              const std::vector<bool>& selected = {}) const;

    // Mouse -> rack slot (0..6). Returns false if no slot is under the point.
    bool slotAt(float x, float y, int& slot) const;

    RectF slotRect(int slot) const;

private:
    const Theme& theme_;
};

}  // namespace scrabble

#endif
