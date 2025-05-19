#ifndef AOC_DAY10_HPP
#define AOC_DAY10_HPP

#include "DaySolution.hpp"
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "Point.hpp"
#include "Direction.hpp"

namespace aoc {

class Day10 : public DaySolution {
public:
    explicit Day10();
   
    std::string solvePart1(const std::vector<std::string>& input) override;
    std::string solvePart2(const std::vector<std::string>& input) override;

private:
    // Input parsing
    void parseInput(const std::vector<std::string>& input);
    
    // Part 1 - Reachable peaks methods
    uint64_t countReachablePeaksFromAllValleys() const;
    std::unordered_set<Point> findReachablePeaks(const Point& startingPoint) const;
    std::unordered_set<Point> explorePathToPeaks(const Point& currentPoint, const Point& previousPoint) const;
    void addReachablePeaks(std::unordered_set<Point>& destination, const std::unordered_set<Point>& source) const;
    
    // Part 2 - Path counting methods
    uint64_t countTotalPathsToPeaksFromAllValleys() const;
    size_t findTotalPathsToPeak(const Point& startingPoint) const;
    size_t countPathsToPeak(const Point& currentPoint, const Point& previousPoint) const;
    
    // Helper methods
    bool isValley(size_t row, size_t col) const;
    bool isPeak(const Point& point) const;
    bool isValidStep(const Point& current, const Point& previous) const;

private:
    // Maze data
    std::vector<std::vector<int>> m_maze;
    
    // Memoization caches
    mutable std::unordered_map<Point, std::unordered_set<Point>> m_reachablePeaks;
    mutable std::unordered_map<Point, size_t> m_pathsToPeak;
    
    // Maze dimensions
    size_t m_rows;
    size_t m_cols;
};

} // namespace aoc

#endif // AOC_DAY10_HPP
