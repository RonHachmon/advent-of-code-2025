#include <filesystem>
#include <iostream>
#include "Day01.hpp"
#include "Day05.hpp"
#include "Day06.hpp"
namespace fs = std::filesystem;

int main() {
    aoc::Day06 day06;
    //day06.runTest(1, aoc::PartSolver::PART_ONE);
    day06.run(aoc::PartSolver::PART_ONE);


    return 0;
}