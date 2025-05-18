#ifndef AOC_DAY08_HPP
#define AOC_DAY08_HPP

#include "DaySolution.hpp"
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "Point.hpp"

namespace aoc {

// Extract the Operator hierarchy to its own file

// Main solution class
class Day08 : public DaySolution {
public:
    Day08();
    
    std::string solvePart1(const std::vector<std::string>& input) override;
    std::string solvePart2(const std::vector<std::string>& input) override;

private:
    void parseInput(const std::vector<std::string>& input);
    void extractAntinodes(const std::vector<Point>& points, std::unordered_set<Point>& antinodes);
    void extractAntinodesPartTwo(const std::vector<Point>& points, std::unordered_set<Point>& antinodes);
private:
    std::unordered_map<char, std::vector<Point>> m_antennaMap;
    size_t  m_rows, m_cols;

};

} // namespace aoc
#endif // AOC_DAY08_HPP
