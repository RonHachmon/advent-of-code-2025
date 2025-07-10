#ifndef AOC_DAY14_HPP
#define AOC_DAY14_HPP

#include "DaySolution.hpp"
#include <iostream>
#include <utility>
#include <cstdint>
#include <vector>
#include <array>

namespace aoc {



class Day14 : public DaySolution {

struct PointAndVelocity{
    int x;
    int y;
    int dx;
    int dy;
};

public:
    explicit Day14();
   
    std::string solvePart1(const std::vector<std::string>& input) override;
    std::string solvePart2(const std::vector<std::string>& input) override;
   
private:
    static constexpr int ROWS  = 103;
    static constexpr int COLS  = 101;
    // static constexpr int ROWS  = 7;
    // static constexpr int COLS  = 11;

    
    void parseInput(const std::vector<std::string>& input);
    void fillMatrix(int steps);
    uint64_t calculateSafetyFactor();

private:
    std::array<std::array<int,COLS>,ROWS> m_matrix;
    std::vector<PointAndVelocity> m_points;
};

} // namespace aoc

#endif // AOC_DAY14_HPP