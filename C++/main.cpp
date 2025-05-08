#include <filesystem>
#include <iostream>
#include "Day01.hpp"
#include "Day05.hpp"
namespace fs = std::filesystem;

int main() {
    aoc::Day05 day05{};
    //day05.runTest(1, aoc::PartSolver::BOTH_PARTS);
    day05.run(aoc::PartSolver::PART_TWO);


    // std::cout << "?????nt path is " << fs::current_path() << '\n'; // (1)
    // fs::current_path(fs::temp_directory_path()); // (3)
    // std::cout << "Current path is " << fs::current_path() << '\n';

    return 0;
}