#include "Day13.hpp"
#include <iostream>
#include <sstream>
#include <numeric>
#include <limits>

namespace aoc {

Day13::Day13() : DaySolution(13), equationPairs_{} {}

std::string Day13::solvePart1(const std::vector<std::string>& input) {
    parseClawMachines(input, false);
    uint64_t totalTokens = calculateMinimumTokensForAllMachines();
    return std::to_string(totalTokens);
}

std::string Day13::solvePart2(const std::vector<std::string>& input) {
    parseClawMachines(input, true);
    uint64_t totalTokens = calculateMinimumTokensForAllMachines();
    return std::to_string(totalTokens);
}

void Day13::parseClawMachines(const std::vector<std::string>& input, bool applyPrizeOffset) {
    equationPairs_.clear();
    
    for (size_t i = 0; i < input.size(); i += 4) {
        if (i + 2 >= input.size()) break;
        
        ClawMachineConfig config = parseClawMachineFromLines(input, i, applyPrizeOffset);
        
        // Create linear equations: ax*numA + bx*numB = px, ay*numA + by*numB = py
        LinearEquation xConstraint(config.buttonAX, config.buttonBX, config.prizeX);
        LinearEquation yConstraint(config.buttonAY, config.buttonBY, config.prizeY);
        
        equationPairs_.emplace_back(xConstraint, yConstraint);
    }
}

ClawMachineConfig Day13::parseClawMachineFromLines(const std::vector<std::string>& input, 
                                                   size_t startIndex, 
                                                   bool applyPrizeOffset) const {
    ClawMachineConfig config{};
    
    auto [buttonAX, buttonAY] = parseButtonValues(input[startIndex]);
    auto [buttonBX, buttonBY] = parseButtonValues(input[startIndex + 1]);
    auto [prizeX, prizeY] = parsePrizeValues(input[startIndex + 2]);
    
    config.buttonAX = buttonAX;
    config.buttonAY = buttonAY;
    config.buttonBX = buttonBX;
    config.buttonBY = buttonBY;
    config.prizeX = applyPrizeOffset ? prizeX + PART2_PRIZE_OFFSET : prizeX;
    config.prizeY = applyPrizeOffset ? prizeY + PART2_PRIZE_OFFSET : prizeY;
    
    return config;
}

std::pair<int32_t, int32_t> Day13::parseButtonValues(const std::string& buttonLine) const {
    int32_t xValue = 0, yValue = 0;
    
    size_t xPos = buttonLine.find("X+");
    if (xPos != std::string::npos) {
        size_t commaPos = buttonLine.find(",", xPos);
        xValue = std::stoi(buttonLine.substr(xPos + 2, commaPos - xPos - 2));
    }
    
    size_t yPos = buttonLine.find("Y+");
    if (yPos != std::string::npos) {
        yValue = std::stoi(buttonLine.substr(yPos + 2));
    }
    
    return {xValue, yValue};
}

std::pair<int64_t, int64_t> Day13::parsePrizeValues(const std::string& prizeLine) const {
    int32_t xValue = 0, yValue = 0;
    
    size_t xPos = prizeLine.find("X=");
    if (xPos != std::string::npos) {
        size_t commaPos = prizeLine.find(",", xPos);
        xValue = std::stoi(prizeLine.substr(xPos + 2, commaPos - xPos - 2));
    }
    
    size_t yPos = prizeLine.find("Y=");
    if (yPos != std::string::npos) {
        yValue = std::stoi(prizeLine.substr(yPos + 2));
    }
    
    return {xValue, yValue};
}

uint64_t Day13::calculateMinimumTokensForAllMachines() const {
    uint64_t totalTokens = 0;
    
    for (const auto& equationPair : equationPairs_) {
        uint64_t machineTokens = calculateTokensForMachine(equationPair);
        
        if (wouldCauseOverflow(totalTokens, machineTokens)) {
            std::cout << "Overflow detected during token calculation" << std::endl;
            break;
        }
        
        totalTokens += machineTokens;
    }
    
    return totalTokens;
}

uint64_t Day13::calculateTokensForMachine(const std::pair<LinearEquation, LinearEquation>& equations) const {
    const auto& [xEquation, yEquation] = equations;
    auto [numButtonA, numButtonB] = xEquation.solveSystemWith(yEquation);
    
    if (isValidSolution(numButtonA, numButtonB)) {
        return static_cast<uint64_t>(numButtonA * COST_BUTTON_A + numButtonB * COST_BUTTON_B);
    }
    
    return 0;
}

bool Day13::isValidSolution(double valueA, double valueB) const {
    return valueA > 0 && valueB > 0 && 
           isWholeNumber(valueA) && isWholeNumber(valueB);
}

bool Day13::isWholeNumber(double value) const {
    return std::abs(value - std::round(value)) < EPSILON;
}

bool Day13::wouldCauseOverflow(uint64_t currentSum, uint64_t tokensToAdd) const {
    return std::numeric_limits<uint64_t>::max() - tokensToAdd <= currentSum;
}

} // namespace aoc