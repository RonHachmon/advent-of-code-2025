#include <filesystem>
#include <iostream>
// #include "Day01.hpp"
// #include "Day05.hpp"
// #include "Day06.hpp"
// #include "Day07.hpp"
// #include "Day08.hpp"
// #include "Day09.hpp"
// #include "Day10.hpp"
#include "Day11.hpp"
#include "Day12.hpp"
#include "Day13.hpp"
#include "Day14.hpp"

int main() {
    aoc::Day14 day{};

    //day.runTest(1, aoc::PartSolver::PART_ONE);
    // day.runTest(2, aoc::PartSolver::PART_TWO);
    // day.runTest(3, aoc::PartSolver::PART_TWO);
    // //day.runTest(2, aoc::PartSolver::PART_ONE);
    //day.runTest(1,aoc::PartSolver::PART_ONE);
    day.run(aoc::PartSolver::PART_TWO);

    // // auto res = equation1.findXAmdY(equation2);

    // // std::cout << "A "<< res.first <<std::endl;
    // // std::cout << "B "<< res.second <<std::endl;

    // aoc::BinaryEqueation equation1{26, 67, 12748};
    // aoc::BinaryEqueation equation2{66, 21, 12176};
    // auto res = equation1.findXAmdY(equation2);

    // std::cout << "A "<< res.first <<std::endl;
    // std::cout << "B "<< res.second <<std::endl;
   

    // std::cout << "Splited Stones "<< day.splitStoneZeroSpecialized(25) <<std::endl;
    // std::cout << "Splited Stones "<< day.splitStoneZeroSpecialized(75) <<std::endl;


    return 0;
}