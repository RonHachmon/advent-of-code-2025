#pragma once

#include "DaySolution.hpp" // Assuming this is your base class
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

namespace aoc {

class Day01 : public DaySolution {
public:
    explicit Day01();
    
    std::string solvePart1(const std::vector<std::string>& input) override;
    std::string solvePart2(const std::vector<std::string>& input) override;

private:
    // Part 1 methods
    void initializePartOneStructures();
    void parseInputForPartOne(const std::vector<std::string>& input);
    long calculateTotalDistance();
    
    // Part 2 methods
    void initializePartTwoStructures();
    void parseInputForPartTwo(const std::vector<std::string>& input);
    long calculateOccurrenceBasedResult();
    
private:
    // Part 1 fields
    std::priority_queue<int, std::vector<int>, std::greater<int>> leftSide;  // Min heap
    std::priority_queue<int, std::vector<int>, std::greater<int>> rightSide; // Min heap
    
    // Part 2 fields
    std::vector<int> leftSideNumbers;
    std::unordered_map<int, int> numberToOccurrence;
};

} // namespace aoc