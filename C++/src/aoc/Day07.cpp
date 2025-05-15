// In Day07.cpp
#include "Day07.hpp"
#include "ContainerUlits.hpp"
#include <algorithm>
#include <sstream>

namespace aoc {

Day07::Day07() :
    DaySolution(7),
    m_target_results{},
    m_combinations{},
    m_add_op{std::make_shared<AdditionOperator>()},
    m_mult_op{std::make_shared<MultiplicationOperator>()},
    m_concat_op{std::make_shared<ConcatenationOperator>()},
    m_part1_operators{},
    m_part2_operators{}
{
    m_part1_operators = {m_add_op, m_mult_op};
    m_part2_operators = {m_add_op, m_mult_op, m_concat_op};
}

std::string Day07::solvePart1(const std::vector<std::string>& input) {
    parseInput(input);
    return solveWithOperators(m_part1_operators);
}

std::string Day07::solvePart2(const std::vector<std::string>& input) {
    parseInput(input);
    return solveWithOperators(m_part2_operators);
}

std::string Day07::solveWithOperators(const std::vector<std::shared_ptr<Operator>>& operators) {
    
    uint64_t res = 0;
    for(int i = 0; i < m_target_results.size(); i++) {
        if(calcPossibleCombinations(m_target_results[i], m_combinations[i], operators)){
            res += m_target_results[i];
        }
    }
    return std::to_string(res);
}


bool Day07::calcPossibleCombinations(uint64_t target, const std::vector<uint64_t>& combination,
                                    const std::vector<std::shared_ptr<Operator>>& operators) {
    if (combination.empty()) {
        return false;
    }
    return helperCalcPossibleCombinations(target, combination, 1, combination[0], operators);
}

bool Day07::helperCalcPossibleCombinations(uint64_t target, const std::vector<uint64_t>& combination, 
                                         size_t index, uint64_t subTarget,
                                         const std::vector<std::shared_ptr<Operator>>& operators)
{
    if(subTarget > target)
    {
        return false;
    }
    if(index == combination.size()) {
        return subTarget == target;
    }
    
    // Try each operator and check if any path leads to a solution
    for (const auto& op : operators) {
        if (helperCalcPossibleCombinations(target, combination, index + 1, 
                                          op->operate(subTarget, combination[index]), 
                                          operators)) {
            return true;
        }
    }
    
    return false;
}

void Day07::parseInput(const std::vector<std::string>& input)
{
    m_target_results.clear();
    m_combinations.clear();
    m_target_results.reserve(input.size());
    m_combinations.reserve(input.size());
    
    for(auto line : input) {
        size_t delimiterPos = line.find(':');
        m_target_results.push_back(std::stoull(line.substr(0, delimiterPos)));


        std::string target_combination = line.substr(delimiterPos + 2);
        std::istringstream iss(target_combination);
        std::vector<uint64_t> current_combination;
        uint64_t num;
        while (iss >> num) {
            current_combination.push_back(num);
        }
        m_combinations.push_back(std::move(current_combination));
    }
}

} // namespace aoc
