#include "Day10.hpp"
#include <iostream>
#include <numeric>
#include "ContainerUlits.hpp"

namespace aoc {

Day10::Day10() : 
    DaySolution(10),
    m_maze{},
    m_reachablePeaks{},
    m_pathsToPeak{},
    m_rows(0),
    m_cols(0)
{
}

std::string Day10::solvePart1(const std::vector<std::string>& input) {
    parseInput(input);
    return std::to_string(countReachablePeaksFromAllValleys());
}

std::string Day10::solvePart2(const std::vector<std::string>& input) {
    parseInput(input);
    return std::to_string(countTotalPathsToPeaksFromAllValleys());
}

void Day10::parseInput(const std::vector<std::string>& input) {
    // Clear previous data
    m_maze.clear();
    m_reachablePeaks.clear();
    m_pathsToPeak.clear();
    
    if (input.empty()) {
        m_rows = m_cols = 0;
        return;
    }
    
    // Set dimensions
    m_cols = input[0].size();
    m_rows = input.size();
    
    // Parse maze
    m_maze.reserve(m_rows);
    for (const auto& line : input) {
        std::vector<int> row;
        row.reserve(m_cols);
        
        for (char c : line) {
            row.push_back(static_cast<int>(c - '0'));
        }
        
        m_maze.push_back(std::move(row));
    }
}

uint64_t Day10::countReachablePeaksFromAllValleys() const {
    uint64_t totalReachablePeaks = 0;
    
    for (size_t i = 0; i < m_rows; i++) {
        for (size_t j = 0; j < m_cols; j++) {
            if (isValley(i, j)) {
                const auto& peaks = findReachablePeaks(Point(i, j));
                totalReachablePeaks += peaks.size();
            }
        }
    }
    
    return totalReachablePeaks;
}

uint64_t Day10::countTotalPathsToPeaksFromAllValleys() const {
    uint64_t totalPaths = 0;
    
    for (size_t i = 0; i < m_rows; i++) {
        for (size_t j = 0; j < m_cols; j++) {
            if (isValley(i, j)) {
                totalPaths += findTotalPathsToPeak(Point(i, j));
            }
        }
    }
    
    return totalPaths;
}

bool Day10::isValley(size_t row, size_t col) const {
    return m_maze[row][col] == 0;
}

bool Day10::isPeak(const Point& point) const {
    return m_maze[point.getX()][point.getY()] == 9;
}

bool Day10::isValidStep(const Point& current, const Point& previous) const {
    if (!current.isInBounds(m_rows, m_cols)) {
        return false;
    }
    
    int currentHeight = m_maze[current.getX()][current.getY()];
    int previousHeight = m_maze[previous.getX()][previous.getY()];
    
    return currentHeight == previousHeight + 1;
}

std::unordered_set<Point> Day10::findReachablePeaks(const Point& startingPoint) const {
    std::unordered_set<Point> reachablePeaks;
    
    // Try all four directions
    addReachablePeaks(reachablePeaks, explorePathToPeaks(startingPoint.moved(Direction::NORTH), startingPoint));
    addReachablePeaks(reachablePeaks, explorePathToPeaks(startingPoint.moved(Direction::SOUTH), startingPoint));
    addReachablePeaks(reachablePeaks, explorePathToPeaks(startingPoint.moved(Direction::EAST), startingPoint));
    addReachablePeaks(reachablePeaks, explorePathToPeaks(startingPoint.moved(Direction::WEST), startingPoint));
    
    return reachablePeaks;
}

void Day10::addReachablePeaks(std::unordered_set<Point>& destination, 
                              const std::unordered_set<Point>& source) const {
    destination.insert(source.begin(), source.end());
}

std::unordered_set<Point> Day10::explorePathToPeaks(const Point& currentPoint, 
                                                    const Point& previousPoint) const {
    // Base cases
    if (!currentPoint.isInBounds(m_rows, m_cols)) {
        return {};
    }
    
    if (!isValidStep(currentPoint, previousPoint)) {
        return {};
    }
    
    if (isPeak(currentPoint)) {
        return {currentPoint};
    }
    
    // Check cache
    if (isInContainer(m_reachablePeaks, currentPoint)) {
        return m_reachablePeaks[currentPoint];
    }
    
    // Recursive exploration
    std::unordered_set<Point> reachablePeaks;
    
    // Try all four directions
    addReachablePeaks(reachablePeaks, explorePathToPeaks(currentPoint.moved(Direction::NORTH), currentPoint));
    addReachablePeaks(reachablePeaks, explorePathToPeaks(currentPoint.moved(Direction::SOUTH), currentPoint));
    addReachablePeaks(reachablePeaks, explorePathToPeaks(currentPoint.moved(Direction::EAST), currentPoint));
    addReachablePeaks(reachablePeaks, explorePathToPeaks(currentPoint.moved(Direction::WEST), currentPoint));
    
    // Cache result
    m_reachablePeaks[currentPoint] = reachablePeaks;
    
    return reachablePeaks;
}

size_t Day10::findTotalPathsToPeak(const Point& startingPoint) const {
    size_t totalPaths = 0;
    
    // Try all four directions
    totalPaths += countPathsToPeak(startingPoint.moved(Direction::NORTH), startingPoint);
    totalPaths += countPathsToPeak(startingPoint.moved(Direction::SOUTH), startingPoint);
    totalPaths += countPathsToPeak(startingPoint.moved(Direction::EAST), startingPoint);
    totalPaths += countPathsToPeak(startingPoint.moved(Direction::WEST), startingPoint);
    
    return totalPaths;
}

size_t Day10::countPathsToPeak(const Point& currentPoint, const Point& previousPoint) const {
  
    if (!currentPoint.isInBounds(m_rows, m_cols)) {
        return 0;
    }
    
    if (!isValidStep(currentPoint, previousPoint)) {
        return 0;
    }
    
    if (isPeak(currentPoint)) {
        return 1;
    }
    

    if (isInContainer(m_pathsToPeak, currentPoint)) {
        return m_pathsToPeak[currentPoint];
    }
    

    size_t totalPaths = 0;
    
   
    totalPaths += countPathsToPeak(currentPoint.moved(Direction::NORTH), currentPoint);
    totalPaths += countPathsToPeak(currentPoint.moved(Direction::SOUTH), currentPoint);
    totalPaths += countPathsToPeak(currentPoint.moved(Direction::EAST), currentPoint);
    totalPaths += countPathsToPeak(currentPoint.moved(Direction::WEST), currentPoint);
    
    
    m_pathsToPeak[currentPoint] = totalPaths;
    
    return totalPaths;
}

} // namespace aoc
