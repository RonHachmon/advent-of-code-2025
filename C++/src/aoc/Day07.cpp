#include "Day07.hpp"
#include <algorithm>
#include <sstream>

namespace aoc {

uint64_t ConcatenationOperator::operate(uint64_t lhs, uint64_t rhs) const {
    uint64_t multiplier = 1;
    uint64_t temp = rhs;
    
    while (temp > 0) {
        temp /= 10;
        multiplier *= 10;
    }
    
    return lhs * multiplier + rhs;
}

Day07::Day07() 
    : DaySolution(7),
      addOperator_(std::make_shared<AdditionOperator>()),
      multiplyOperator_(std::make_shared<MultiplicationOperator>()),
      concatenateOperator_(std::make_shared<ConcatenationOperator>()) {
    
    part1Operators_ = {addOperator_, multiplyOperator_};
    part2Operators_ = {addOperator_, multiplyOperator_, concatenateOperator_};
}

std::string Day07::solvePart1(const std::vector<std::string>& input) {
    parseInput(input);
    return solveWithOperators(part1Operators_);
}

std::string Day07::solvePart2(const std::vector<std::string>& input) {
    parseInput(input);
    return solveWithOperators(part2Operators_);
}

std::string Day07::solveWithOperators(const OperatorSet& operators) const {
    TargetValue sum = 0;
    
    for (size_t i = 0; i < targets_.size(); i++) {
        if (canReachTarget(targets_[i], numberSets_[i], operators)) {
            sum += targets_[i];
        }
    }
    
    return std::to_string(sum);
}

bool Day07::canReachTarget(TargetValue target, const Numbers& numbers, 
                         const OperatorSet& operators) const {
    if (numbers.empty()) {
        return false;
    }
    
    return findSolution(target, numbers, 1, numbers[0], operators);
}

bool Day07::findSolution(TargetValue target, const Numbers& numbers,
                       size_t currentIndex, Number currentValue,
                       const OperatorSet& operators) const {
    // Early termination for efficiency
    if (currentValue > target) {
        return false;
    }
    
    // Base case: we've used all numbers
    if (currentIndex == numbers.size()) {
        return currentValue == target;
    }
    
    // Try each available operator
    for (const auto& op : operators) {
        Number nextValue = op->operate(currentValue, numbers[currentIndex]);
        
        if (findSolution(target, numbers, currentIndex + 1, nextValue, operators)) {
            return true;
        }
    }
    
    return false;
}

void Day07::parseInput(const std::vector<std::string>& input) {
    targets_.clear();
    numberSets_.clear();
    
    targets_.reserve(input.size());
    numberSets_.reserve(input.size());
    
    for (const auto& line : input) {
        parseLine(line);
    }
}

void Day07::parseLine(const std::string& line) {
    size_t delimiterPos = line.find(':');
    TargetValue target = std::stoull(line.substr(0, delimiterPos));
    targets_.push_back(target);
    
    std::string numbersSection = line.substr(delimiterPos + 2);
    numberSets_.push_back(parseNumbers(numbersSection));
}

Day07::Numbers Day07::parseNumbers(const std::string& numbersStr) {
    std::istringstream iss(numbersStr);
    Numbers numbers;
    Number num;
    
    while (iss >> num) {
        numbers.push_back(num);
    }
    
    return numbers;
}

} // namespace aoc
