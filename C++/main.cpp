#include <filesystem>
#include <iostream>
#include "Day01.hpp"
#include "Day05.hpp"
#include "Day06.hpp"
namespace fs = std::filesystem;

int main() {
    aoc::Day06 day06;
    //day06.runTest(1, aoc::PartSolver::BOTH_PARTS);
    day06.run(aoc::PartSolver::BOTH_PARTS);


    return 0;
}