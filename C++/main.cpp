#include <filesystem>
#include <iostream>
#include "Day01.hpp"
#include "Day05.hpp"
#include "Day06.hpp"
#include "Day07.hpp"
#include "Day08.hpp"
#include "Day09.hpp"
namespace fs = std::filesystem;

int main() {
    aoc::Day09 day;
    day.runTest(1, aoc::PartSolver::BOTH_PARTS);
    //day.runTest(2, aoc::PartSolver::PART_ONE);
    //day.run(aoc::PartSolver::PART_ONE);


    return 0;
}