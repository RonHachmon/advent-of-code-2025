#include <filesystem>
#include <iostream>
#include "Day01.hpp"
#include "Day05.hpp"
namespace fs = std::filesystem;

int main() {
    aoc::Day05 day05{};
    //day05.runTest(1, aoc::PartSolver::BOTH_PARTS);
    day05.run(aoc::PartSolver::BOTH_PARTS);


    return 0;
}