#ifndef AOC_DAY06_HPP
#define AOC_DAY06_HPP

#include "DaySolution.hpp"
#include "Point.hpp"
#include "Direction.hpp"
#include <string>
#include <vector>

namespace aoc {

class Day06 : public DaySolution {
public:
    explicit Day06();
   
    std::string solvePart1(const std::vector<std::string>& input) override;
    std::string solvePart2(const std::vector<std::string>& input) override;

private:
    // Constants
    static constexpr char WALKED = 'X';
    static constexpr char BLOCK = '#';
    static constexpr char GUARD_NORTH = '^';
    static constexpr char GUARD_SOUTH = 'v';
    static constexpr char GUARD_WEST = '<';
    static constexpr char GUARD_EAST = '>';

    // Member variables
    std::vector<std::vector<char>> m_maze;
    Point m_currentPoint;
    Direction m_currentDirection;
    int m_rows;
    int m_cols;

    // Helper functions
    void parseInput(const std::vector<std::string>& input);
    void findStartingPosition(const std::vector<std::string>& input);
    Direction getDirectionFromChar(char c) const;
    int walkMaze();
    Point getNextPoint() const;
    bool isBlocked(const Point& point) const;
};

} // namespace aoc

#endif // AOC_DAY06_HPP