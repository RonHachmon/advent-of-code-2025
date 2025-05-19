#include <filesystem>
#include <iostream>
#include "Day01.hpp"
#include "Day05.hpp"
#include "Day06.hpp"
#include "Day07.hpp"
#include "Day08.hpp"
#include "Day09.hpp"
#include "Day10.hpp"
namespace fs = std::filesystem;

int main() {
    aoc::Day10 day;
    //day.runTest(1, aoc::PartSolver::BOTH_PARTS);
    //day.runTest(2, aoc::PartSolver::PART_ONE);
    day.run(aoc::PartSolver::BOTH_PARTS);


    return 0;
}