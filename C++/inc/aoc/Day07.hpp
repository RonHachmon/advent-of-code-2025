#ifndef AOC_DAY07_HPP
#define AOC_DAY07_HPP

#include "DaySolution.hpp"
#include <vector>
#include <string>
#include <memory>

namespace aoc {

// Extract the Operator hierarchy to its own file
class Operator {
public:
    virtual uint64_t operate(uint64_t lhs, uint64_t rhs) const = 0;
    virtual ~Operator() = default;
};

class AdditionOperator : public Operator {
public:
    uint64_t operate(uint64_t lhs, uint64_t rhs) const override {
        return lhs + rhs;
    }
};

class MultiplicationOperator : public Operator {
public:
    uint64_t operate(uint64_t lhs, uint64_t rhs) const override {
        return lhs * rhs;
    }
};

class ConcatenationOperator : public Operator {
public:
    uint64_t operate(uint64_t lhs, uint64_t rhs) const override;
};

// Main solution class
class Day07 : public DaySolution {
public:
    Day07();
    
    std::string solvePart1(const std::vector<std::string>& input) override;
    std::string solvePart2(const std::vector<std::string>& input) override;

private:
    using TargetValue = uint64_t;
    using Number = uint64_t;
    using Numbers = std::vector<Number>;
    using OperatorSet = std::vector<std::shared_ptr<Operator>>;
    
    void parseInput(const std::vector<std::string>& input);
    void parseLine(const std::string& line);
    Numbers parseNumbers(const std::string& numbersStr);


    std::string solveWithOperators(const OperatorSet& operators) const;
    
    bool canReachTarget(TargetValue target, const Numbers& numbers, 
                        const OperatorSet& operators) const;
    
    bool findSolution(TargetValue target, const Numbers& numbers,
                     size_t currentIndex, Number currentValue,
                     const OperatorSet& operators) const;

private:
    std::vector<TargetValue> targets_;
    std::vector<Numbers> numberSets_;
    
    // Operators
    std::shared_ptr<Operator> addOperator_;
    std::shared_ptr<Operator> multiplyOperator_;
    std::shared_ptr<Operator> concatenateOperator_;
    
    OperatorSet part1Operators_;
    OperatorSet part2Operators_;
};

} // namespace aoc
#endif // AOC_DAY07_HPP
