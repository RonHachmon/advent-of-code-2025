#include "Day14.hpp"
#include <iostream>
#include <sstream>
#include <numeric>
#include <limits>
#include <regex>
#include <thread>
#include <chrono>

namespace aoc {

Day14::Day14():
DaySolution(14),
m_matrix{0},
m_points{}
{

}

std::string Day14::solvePart1(const std::vector<std::string>& input) {

    parseInput(input);

    // for(auto& p : m_points){
    //     std::cout<< " X:"<< p.x << " Y:"<< p.y << " dx:"<< p.dx << " dy:"<< p.dy <<std::endl;
    // }


    fillMatrix(100);

    // for(int i =0;i <ROWS;++i){
        
    //     for(int j =0 ; j<COLS; ++j){
    //         std::cout<<m_matrix[i][j] << ",";
    //     }

    //     std::cout<< std::endl;
    // }
    uint64_t safetyFactor = calculateSafetyFactor();
    return std::to_string(safetyFactor);
}

std::string Day14::solvePart2(const std::vector<std::string>& input) {

    parseInput(input);
    uint64_t counter = 160;
    while(1){

    int i = 0;
    int j = 0;
    fillMatrix(counter);
    std::cout<< "Counter:" << counter<< std::endl;

    for( i =0;i <ROWS;++i){
        
        
        for( j =0 ; j<COLS-1; ++j){
            
            
            if(m_matrix[i][j] == 0){
                std::cout<<" ";
            }
            else{
                std::cout<<m_matrix[i][j] ;
            }
            
        }

        if(m_matrix[i][j] == 0){
            std::cout<<" "<< std::endl;;
        }
        else{
            std::cout<<m_matrix[i][j] << std::endl;;
        }



    }

    
    counter++;
    std::this_thread::sleep_for(std::chrono::seconds(2)); 
    std::cout<< std::endl;
    std::cout<< std::endl;
    std::cout<< std::endl;
    
    

    }
    return std::to_string(0);
}

void Day14::fillMatrix(int steps) {
    // Clear the matrix first
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            m_matrix[i][j] = 0;
        }
    }
    int counter =0;
    // Process each point
    for (const auto& point : m_points) {
        int x = point.x;
        int y = point.y;
        int dx = point.dx;
        int dy = point.dy;

        if(dx<0){
            x = x - (((dx *-1)*steps) % ROWS);
        }
        else{
                   
            x = x + ((dx*steps) % ROWS);
        }

        if(dy<0){
            y =  y - (((dy * -1) * steps) % COLS);
        }
        else{
                   
            y =  y + ((dy * steps) % COLS);
        }
        
        

        if (x < 0) {
            x += ROWS;
        }
        
        if (y < 0) {
            y += COLS;
        }

        if(x>= ROWS){
            x = x%ROWS;
        }

        if(y>= COLS){
            y = y % COLS;
        }
        
        // Increment count at this position
        m_matrix[x][y]++;
        
    }
}

uint64_t Day14::calculateSafetyFactor() {
    int midX = ROWS / 2;  
    int midY = COLS / 2;  
    
    uint64_t quadrant1 = 0; // Top-right
    uint64_t quadrant2 = 0; // Top-left
    uint64_t quadrant3 = 0; // Bottom-left
    uint64_t quadrant4 = 0; // Bottom-right
    
    // Count robots in each quadrant
    for (int x = 0; x < ROWS; ++x) {
        for (int y = 0; y < COLS; ++y) {
            // Skip robots exactly in the middle (horizontally or vertically)
            if (x == midX || y == midY) {
                continue;
            }
            
            uint64_t robotCount = static_cast<uint64_t>(m_matrix[x][y]);
            
            if (x < midX && y < midY) {
                quadrant2 += robotCount; // Top-left
            }
            else if (x > midX && y < midY) {
                quadrant1 += robotCount; // Top-right
            }
            else if (x < midX && y > midY) {
                quadrant3 += robotCount; // Bottom-left
            }
            else if (x > midX && y > midY) {
                quadrant4 += robotCount; // Bottom-right
            }
        }
    }
    
    // Debug output (optional)
    std::cout << "Quadrant counts: " << quadrant1 << ", " << quadrant2 
              << ", " << quadrant3 << ", " << quadrant4 << std::endl;
    
    // Calculate safety factor
    return quadrant1 * quadrant2 * quadrant3 * quadrant4;
}

void Day14::parseInput(const std::vector<std::string>& input) {
    m_points.clear(); // Clear any existing points
    
    // Regular expression to match p=x,y v=dx,dy format
    std::regex pattern(R"(p=(-?\d+),(-?\d+)\s+v=(-?\d+),(-?\d+))");
    std::smatch matches;
    
    for (const auto& line : input) {
        if (line.empty()) continue; // Skip empty lines
        
        if (std::regex_search(line, matches, pattern)) {
            PointAndVelocity point;
            point.x = std::stoi(matches[2].str());   // x position
            point.y = std::stoi(matches[1].str());   // y position  
            point.dx = std::stoi(matches[4].str());  // x velocity
            point.dy = std::stoi(matches[3].str());  // y velocity
            
            m_points.push_back(point);
        }
    }
}




} // namespace aoc