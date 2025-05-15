#ifndef AOC_DAY06_HPP
#define AOC_DAY06_HPP

#include "DaySolution.hpp"
#include "Point.hpp"
#include "Direction.hpp"
#include <string>
#include <vector>
#include <unordered_set>
#include <utility>

namespace aoc {

// Custom hash function for pair<Point, Direction>
struct BlockDirectionHash {
    std::size_t operator()(const std::pair<Point, Direction>& pd) const {
        auto h1 = std::hash<int>{}(pd.first.getX());
        auto h2 = std::hash<int>{}(pd.first.getY());
        auto h3 = std::hash<int>{}(pd.second.getDx());
        auto h4 = std::hash<int>{}(pd.second.getDy());
        return h1 ^ (h2 << 2) ^ (h3 << 3) ^ (h4 << 4);
    }
};

class Day06 : public DaySolution {
public:
    explicit Day06();
   
    std::string solvePart1(const std::vector<std::string>& input) override;
    std::string solvePart2(const std::vector<std::string>& input) override;


private:
    void parseInput(const std::vector<std::string>& input);

    void findStartingPosition(const std::vector<std::string>& input);

    Direction getDirectionFromChar(char c) const;
    
    std::unordered_set<Point> walkMaze();
    
    Point getNextPoint() const;
    
    bool isBlocked(const Point& point) const;
    
    // Part 2 specific functions
    bool checkForLoop(const Point& blockPosition);
    
    int countPossibleLoops();

private:

    // Member variables
    std::vector<std::vector<char>> m_maze;
    Point m_startingPoint;
    Point m_currentPoint;
    Direction m_startingDirection;
    Direction m_currentDirection;
    int m_rows;
    int m_cols;


};

} // namespace aoc

#endif // AOC_DAY06_HPP