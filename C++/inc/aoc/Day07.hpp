// In Day07.hpp
#ifndef AOC_DAY07_HPP
#define AOC_DAY07_HPP
#include "DaySolution.hpp"
#include <vector>
#include <string>
#include <memory> // For shared_ptr

namespace aoc {

// Operator interface
class Operator {
public:
    virtual uint64_t operate(uint64_t a, uint64_t b) const = 0;
    virtual ~Operator() = default; // Virtual destructor
};

// Multiplication implementation
class MultiplicationOperator : public Operator {
public:
    uint64_t operate(uint64_t a, uint64_t b) const override {
        return a * b;
    }
};

// Addition implementation
class AdditionOperator : public Operator {
public:
    uint64_t operate(uint64_t a, uint64_t b) const override {
        return a + b;
    }
};

// Concatenation implementation
class ConcatenationOperator : public Operator {
public:
    uint64_t operate(uint64_t a, uint64_t b) const override {
        uint64_t digit_in_b = 1;
        uint64_t temp_b = b;
        while(temp_b > 0) {
            temp_b /= 10;
            digit_in_b *= 10;
        }
        return a * digit_in_b + b;
    }
};

class Day07 : public DaySolution {
public:
    explicit Day07();
   
    std::string solvePart1(const std::vector<std::string>& input) override;
    std::string solvePart2(const std::vector<std::string>& input) override;
private:

    void parseInput(const std::vector<std::string>& input);

    std::string solveWithOperators(const std::vector<std::shared_ptr<Operator>>& operators);

    bool calcPossibleCombinations(uint64_t target, const std::vector<uint64_t>& combination, 
                                 const std::vector<std::shared_ptr<Operator>>& operators);

    bool helperCalcPossibleCombinations(uint64_t target, const std::vector<uint64_t>& combination,
                                      size_t index, uint64_t subTarget, 
                                      const std::vector<std::shared_ptr<Operator>>& operators);
private:
    std::vector<uint64_t> m_target_results;
    std::vector<std::vector<uint64_t>> m_combinations;
    
    // Shared operator instances
    std::shared_ptr<Operator> m_add_op;
    std::shared_ptr<Operator> m_mult_op;
    std::shared_ptr<Operator> m_concat_op;
    
    // References to operators for each part
    std::vector<std::shared_ptr<Operator>> m_part1_operators; // For part 1: + and *
    std::vector<std::shared_ptr<Operator>> m_part2_operators; // For part 2: +, * and concat
};
} // namespace aoc
#endif // AOC_DAY07_HPP