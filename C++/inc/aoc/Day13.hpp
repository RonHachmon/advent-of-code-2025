#ifndef AOC_DAY13_HPP
#define AOC_DAY13_HPP

#include "DaySolution.hpp"
#include <iostream>
#include <utility>
#include <cstdint>
#include <vector>

namespace aoc {

class LinearEquation {
public:
    explicit LinearEquation(int64_t coefficientA, int64_t coefficientB, int64_t targetValue)
        : coefficientA_{coefficientA}, coefficientB_{coefficientB}, targetValue_{targetValue} {}
       
    int64_t getCoefficientA() const { return coefficientA_; }
    int64_t getCoefficientB() const { return coefficientB_; }
    int64_t getTargetValue() const { return targetValue_; }
   
    LinearEquation multiplyBy(int64_t factor) const {
        return LinearEquation{
            coefficientA_ * factor, 
            coefficientB_ * factor, 
            targetValue_ * factor
        };
    }
   
    LinearEquation add(const LinearEquation& other) const {
        return LinearEquation{
            coefficientA_ + other.getCoefficientA(),
            coefficientB_ + other.getCoefficientB(),
            targetValue_ + other.getTargetValue()
        };
    }
   
    LinearEquation subtract(const LinearEquation& other) const {
        return LinearEquation{
            coefficientA_ - other.getCoefficientA(),
            coefficientB_ - other.getCoefficientB(),
            targetValue_ - other.getTargetValue()
        };
    }
   
    double solveForA(double valueB) const {
        return (static_cast<double>(targetValue_) - static_cast<double>(coefficientB_) * valueB) 
               / static_cast<double>(coefficientA_);
    }
   
    double solveForB(double valueA) const {
        return (static_cast<double>(targetValue_) - static_cast<double>(coefficientA_) * valueA) 
               / static_cast<double>(coefficientB_);
    }
   
    void printEquation() const {
        std::cout << "Equation: " << coefficientA_ << "a + " << coefficientB_ 
                  << "b = " << targetValue_ << std::endl;
    }
   
    std::pair<double, double> solveSystemWith(const LinearEquation& secondEquation) const {
        // Use elimination method to solve system of linear equations
        LinearEquation eliminationEq1 = secondEquation.multiplyBy(this->getCoefficientA());
        LinearEquation eliminationEq2 = this->multiplyBy(secondEquation.getCoefficientA());
        LinearEquation deltaEquation = eliminationEq1.subtract(eliminationEq2);
        
        double valueB = deltaEquation.solveForB(0.0);
        double valueA = secondEquation.solveForA(valueB);
        
        return {valueA, valueB};
    }

private:
    int64_t coefficientA_;
    int64_t coefficientB_;
    int64_t targetValue_;
};

struct ClawMachineConfig {
    int32_t buttonAX;
    int32_t buttonAY;
    int32_t buttonBX;
    int32_t buttonBY;
    int64_t prizeX;
    int64_t prizeY;
};

class Day13 : public DaySolution {
public:
    explicit Day13();
   
    std::string solvePart1(const std::vector<std::string>& input) override;
    std::string solvePart2(const std::vector<std::string>& input) override;
   
private:
    static constexpr int64_t PART2_PRIZE_OFFSET = 10000000000000;
    static constexpr double EPSILON = 1e-9;
    static constexpr int COST_BUTTON_A = 3;
    static constexpr int COST_BUTTON_B = 1;
    
    void parseClawMachines(const std::vector<std::string>& input, bool applyPrizeOffset = false);
    ClawMachineConfig parseClawMachineFromLines(const std::vector<std::string>& input, 
                                                size_t startIndex, 
                                                bool applyPrizeOffset) const;
    std::pair<int32_t, int32_t> parseButtonValues(const std::string& buttonLine) const;
    std::pair<int64_t, int64_t> parsePrizeValues(const std::string& prizeLine) const;
    
    uint64_t calculateMinimumTokensForAllMachines() const;
    uint64_t calculateTokensForMachine(const std::pair<LinearEquation, LinearEquation>& equations) const;
    bool isValidSolution(double valueA, double valueB) const;
    bool isWholeNumber(double value) const;
    bool wouldCauseOverflow(uint64_t currentSum, uint64_t tokensToAdd) const;
   
    std::vector<std::pair<LinearEquation, LinearEquation>> equationPairs_;
};

} // namespace aoc

#endif // AOC_DAY13_HPP