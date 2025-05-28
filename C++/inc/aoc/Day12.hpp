#ifndef AOC_DAY12_HPP
#define AOC_DAY12_HPP

#include "DaySolution.hpp"
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <optional>
#include "Point.hpp"
#include "Direction.hpp"

namespace aoc {

class Day12 : public DaySolution {
public:
    explicit Day12();
   
    std::string solvePart1(const std::vector<std::string>& input) override;
    std::string solvePart2(const std::vector<std::string>& input) override;

    uint64_t splitStoneZeroSpecialized( uint64_t total_splits);

    

private:

    void calcAreaAndPerimeter(char current_field, Point point, uint64_t& area, uint64_t& perimeter, std::unordered_set<Point>& visited);

    void calcAreaAndPerimeter(char current_field, Point point, uint64_t& area, uint64_t& perimeter, std::unordered_set<Point>& visited, std::optional<Direction> prevDirection);

    void parseInput(const std::vector<std::string>& input);


private:
    std::vector<std::vector<char>> m_maze;
    size_t m_rows;
    size_t m_cols;

    std::unordered_map<Direction, std::unordered_set<Point>> m_visitedPermiters;



};

} // namespace aoc

#endif // AOC_DAY12_HPP
