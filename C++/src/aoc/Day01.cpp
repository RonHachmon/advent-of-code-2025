#include "Day01.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <numeric>

namespace aoc {

Day01::Day01():
DaySolution(1)
{
}

std::string Day01::solvePart1(const std::vector<std::string>& input)
{
    // Initialize data structures for part 1
    initializePartOneStructures();

    // Parse input and populate data structures
    parseInputForPartOne(input);

    // Calculate total distance
    long totalDistance = calculateTotalDistance();

    std::ostringstream result;
    result << totalDistance;
    return result.str();
}

void Day01::initializePartOneStructures()
{
    // Clear any existing data
    while (!leftSide.empty()) leftSide.pop();
    while (!rightSide.empty()) rightSide.pop();
}

void Day01::parseInputForPartOne(const std::vector<std::string>& input)
{
    for (const auto& line : input) {
        std::istringstream iss(line);
        int leftValue, rightValue;
        
        if (iss >> leftValue >> rightValue) {
            leftSide.push(leftValue);
            rightSide.push(rightValue);
        }
    }
}

long Day01::calculateTotalDistance()
{
    long totalDistance = 0;

    while (!leftSide.empty() && !rightSide.empty()) {
        int leftValue = leftSide.top();
        leftSide.pop();
        
        int rightValue = rightSide.top();
        rightSide.pop();
        
        int distance = std::abs(rightValue - leftValue);
        totalDistance += distance;
    }

    return totalDistance;
}

std::string Day01::solvePart2(const std::vector<std::string>& input)
{
    // Initialize data structures for part 2
    initializePartTwoStructures();

    // Parse input and populate data structures
    parseInputForPartTwo(input);

    // Calculate the result based on occurrences
    long result = calculateOccurrenceBasedResult();

    std::ostringstream resultStream;
    resultStream << result;
    return resultStream.str();
}

void Day01::initializePartTwoStructures() 
{
    leftSideNumbers.clear();
    numberToOccurrence.clear();
}

void Day01::parseInputForPartTwo(const std::vector<std::string>& input)
{
    for (const auto& line : input) {
        std::istringstream iss(line);
        int leftValue, rightValue;
        
        if (iss >> leftValue >> rightValue) {
            leftSideNumbers.push_back(leftValue);
            numberToOccurrence[rightValue]++;
        }
    }
}

long Day01::calculateOccurrenceBasedResult() 
{
    long result = 0;
    for (const auto& leftValue : leftSideNumbers) {
        auto it = numberToOccurrence.find(leftValue);
        int occurrences = (it != numberToOccurrence.end()) ? it->second : 0;
        result += static_cast<long>(leftValue) * occurrences;
    }
    return result;
}

} // namespace aoc
