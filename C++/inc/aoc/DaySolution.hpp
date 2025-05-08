#pragma once

#include <string>
#include <vector>
#include <stdexcept>

namespace aoc {

enum class PartSolver {
    PART_ONE,
    PART_TWO,
    BOTH_PARTS
};

/**
 * Enhanced base template for Advent of Code solutions.
 */
class DaySolution {
public:
    /**
     * Constructor
     */
    explicit DaySolution(int day);
    
    /**
     * Virtual destructor for proper cleanup
     */
    virtual ~DaySolution() = default;
    
    /**
     * Get the day number
     */
    int getDay() const;
    
    /**
     * Solve part one of the day's challenge.
     */
    virtual std::string solvePart1(const std::vector<std::string>& input) = 0;
    
    /**
     * Solve part two of the day's challenge.
     */
    virtual std::string solvePart2(const std::vector<std::string>& input) = 0;
    
    /**
     * Read the main input file for the day.
     */
    std::vector<std::string> readInput() const;
    
    /**
     * Read a test input file for the day.
     *
     * @param testNum The test number (for multiple test files)
     */
    std::vector<std::string> readTestInput(int testNum) const;
    
    /**
     * Run the solution with main input file.
     */
    void run(PartSolver part = PartSolver::BOTH_PARTS);
    
    /**
     * Run the solution with test input file.
     */
    void runTest(int testNum, PartSolver part);
    
private:
    int day;
    
    /**
     * Run the appropriate part(s) with the given input.
     */
    void runWithInput(const std::vector<std::string>& input, PartSolver part);
};

} // namespace aoc
