#include "RackView.h"

#include "BoardView.h"   // drawLetterTile

namespace scrabble {

RackView::RackView(const Theme& theme) : theme_(theme) {}

bool RackView::slotAt(float x, float y, int& slot) const { return rackSlotAt(x, y, slot); }

RectF RackView::slotRect(int slot) const { return rackSlotRect(slot); }

void RackView::draw(sf::RenderWindow& window, const std::vector<Tile>& rack,
                    const std::vector<bool>& hidden,
                    const std::vector<bool>& selected) const {
    // Wooden holder behind the slots.
    sf::RectangleShape holder({layout::kRackWidth + 16.0f, layout::kSlotSize + 16.0f});
    holder.setPosition({layout::kRackX - 8.0f, layout::kRackY - 8.0f});
    holder.setFillColor(theme_.boardBackground);
    window.draw(holder);

    for (int i = 0; i < RACK_SIZE; ++i) {
        const RectF r = rackSlotRect(i);
        sf::RectangleShape slot({r.w, r.h});
        slot.setPosition({r.x, r.y});
        slot.setFillColor(theme_.normalCellColor);
        window.draw(slot);

        const std::size_t idx = static_cast<std::size_t>(i);
        if (idx >= rack.size()) continue;
        if (idx < hidden.size() && hidden[idx]) continue;

        const bool isSelected = idx < selected.size() && selected[idx];
        drawLetterTile(window, theme_, r, rack[idx].getLetter(), rack[idx].getPoints(),
                       isSelected);
    }
}

}  // namespace scrabble
