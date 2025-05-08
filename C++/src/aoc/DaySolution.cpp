#include "DaySolution.hpp"

#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <chrono>


namespace aoc {

DaySolution::DaySolution(int day) : day(day) {
}

int DaySolution::getDay() const {
    return day;
}

std::vector<std::string> DaySolution::readInput() const {
    std::ostringstream filename;
    filename << "day" << std::setfill('0') << std::setw(2) << day << ".txt";
    
    std::string filepath = "resources/" + filename.str();
    std::ifstream file(filepath);
    
    if (!file.is_open()) {
        throw std::runtime_error("Input file not found: " + filepath);
    }
    
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    
    return lines;
}

std::vector<std::string> DaySolution::readTestInput(int testNum) const {
    std::ostringstream filename;
    filename << "day" << std::setfill('0') << std::setw(2) << day 
             << "_test" << testNum << ".txt";
    
    std::string filepath = "resources/" + filename.str();
    std::ifstream file(filepath);
    
    if (!file.is_open()) {
        throw std::runtime_error("Test input file not found: " + filepath +
                                "\nMake sure you've created this file with the example input from the puzzle.");
    }
    
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    
    return lines;
}

void DaySolution::run(PartSolver part) {
    try {
        std::vector<std::string> input = readInput();
        runWithInput(input, part);
    } catch (const std::exception& e) {
        std::cerr << "Error reading input file: " << e.what() << std::endl;
    }
}

void DaySolution::runTest(int testNum, PartSolver part) {
    try {
        std::vector<std::string> input = readTestInput(testNum);
        runWithInput(input, part);
    } catch (const std::exception& e) {
        std::cerr << "Error reading test input file: " << e.what() << std::endl;
    }
}



void DaySolution::runWithInput(const std::vector<std::string>& input, PartSolver part) {
    if (part == PartSolver::PART_ONE || part == PartSolver::BOTH_PARTS) {
        auto start = std::chrono::high_resolution_clock::now();
        std::string result1 = solvePart1(input);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration_ms = end - start;
        
        std::cout << "Day " << day << " - Part 1: " << result1;
        
        if (duration_ms.count() >= 1000.0) {
            double duration_sec = duration_ms.count() / 1000.0;
            std::cout << " (Time: " << std::fixed << std::setprecision(2) 
                      << duration_sec << " s)";
        } else {
            std::cout << " (Time: " << std::fixed << std::setprecision(2) 
                      << duration_ms.count() << " ms)";
        }
        std::cout << std::endl;
    }
    
    if (part == PartSolver::PART_TWO || part == PartSolver::BOTH_PARTS) {
        auto start = std::chrono::high_resolution_clock::now();
        std::string result2 = solvePart2(input);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration_ms = end - start;
        
        std::cout << "Day " << day << " - Part 2: " << result2;
        
        if (duration_ms.count() >= 1000.0) {
            double duration_sec = duration_ms.count() / 1000.0;
            std::cout << " (Time: " << std::fixed << std::setprecision(2) 
                      << duration_sec << " s)";
        } else {
            std::cout << " (Time: " << std::fixed << std::setprecision(2) 
                      << duration_ms.count() << " ms)";
        }
        std::cout << std::endl;
    }
}

} // namespace aoc