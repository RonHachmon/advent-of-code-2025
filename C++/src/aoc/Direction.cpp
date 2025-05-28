#include "Direction.hpp"
#include <stdexcept>

namespace aoc {

// Private constructor
Direction::Direction(int dx, int dy) : dx(dx), dy(dy) {}

// Static instances
const Direction Direction::NORTH(-1, 0);
const Direction Direction::NORTHEAST(-1, 1);
const Direction Direction::EAST(0, 1);
const Direction Direction::SOUTHEAST(1, 1);
const Direction Direction::SOUTH(1, 0);
const Direction Direction::SOUTHWEST(1, -1);
const Direction Direction::WEST(0, -1);
const Direction Direction::NORTHWEST(-1, -1);

// Array of all directions
const Direction* const Direction::ALL_DIRECTIONS[8] = {
    &NORTH, &NORTHEAST, &EAST, &SOUTHEAST,
    &SOUTH, &SOUTHWEST, &WEST, &NORTHWEST
};


Direction Direction::opposite() const {
    // Map each direction to its opposite
    if (*this == NORTH) return SOUTH;
    if (*this == NORTHEAST) return SOUTHWEST;
    if (*this == EAST) return WEST;
    if (*this == SOUTHEAST) return NORTHWEST;
    if (*this == SOUTH) return NORTH;
    if (*this == SOUTHWEST) return NORTHEAST;
    if (*this == WEST) return EAST;
    if (*this == NORTHWEST) return SOUTHEAST;
    
    throw std::logic_error("Unknown direction");
}

void Direction::rotate(Rotation angle) {
    // Get current index

    int currentIndex = -1;
    for(int i = 0; i < 8; i++) {
        if(*this == *ALL_DIRECTIONS[i]) {
            currentIndex = i;
            break;
        }
    }
    
    // Calculate rotation steps (each step is 45 degrees)
    int steps = static_cast<int>(angle) / 45;
    
    // Calculate new index with wrapping
    size_t newIndex = (currentIndex + steps) % 8;
    *this = *ALL_DIRECTIONS[newIndex];
  
}

Direction Direction::rotated(Rotation angle) const {
    // Get current index

    Direction result = *this;
    int currentIndex = -1;
    for(int i = 0; i < 8; i++) {
        if(*this == *ALL_DIRECTIONS[i]) {
            currentIndex = i;
            break;
        }
    }
    
    // Calculate rotation steps (each step is 45 degrees)
    int steps = static_cast<int>(angle) / 45;
    
    // Calculate new index with wrapping
    size_t newIndex = (currentIndex + steps) % 8;
    result = *ALL_DIRECTIONS[newIndex];

    return result;
  
}

bool Direction::operator==(const Direction& other) const {
    return this->dx == other.dx && this->dy == other.dy;
}

bool Direction::operator!=(const Direction& other) const {
    return this != &other;
}

} // namespace aoc
