#include "Day12.hpp"
#include <iostream>
#include <sstream>
#include <numeric>
#include <Array>
 
#include "ContainerUlits.hpp"
#include "Point.hpp"
#include "Direction.hpp"

namespace aoc {

Day12::Day12() :
    DaySolution(12),
    m_maze{},
    m_rows{},
    m_cols{},
    m_visitedPermiters{}
{


}




std::string Day12::solvePart1(const std::vector<std::string>& input) {
    parseInput(input);
    uint64_t area = 0;
    uint64_t perimeter = 0;
    uint64_t res = 0;
    std::unordered_set<Point> visited{};
    Point current_point{};

    for(int i = 0; i < m_rows; i++){
        for(int j = 0; j < m_cols; j++){
            current_point = Point{i,j};

            if(isInContainer(visited, current_point))
            {
                continue;
            }

            calcAreaAndPerimeter(m_maze[i][j], Point{i,j}, area, perimeter, visited);
            std::cout << m_maze[i][j] << " Area: " << area << "   Perm: " << perimeter << std::endl;
            res += area * perimeter;
            area = perimeter = 0;
            m_visitedPermiters.clear();
        }
    }

    
    
    return std::to_string(res);
}

std::string Day12::solvePart2(const std::vector<std::string>& input) {

    
    parseInput(input);
    m_visitedPermiters.clear();
    uint64_t area = 0;
    uint64_t perimeter = 0;
    uint64_t res = 0;
    std::unordered_set<Point> visited{};
    Point current_point{};

    for(int i = 0; i < m_rows; i++){
        for(int j = 0; j < m_cols; j++){
            current_point = Point{i,j};

            if(isInContainer(visited, current_point))
            {
                continue;
            }

            calcAreaAndPerimeter(m_maze[i][j], Point{i,j}, area, perimeter, visited, std::nullopt);
            //std::cout << m_maze[i][j] << " Area: " << area << "   Perm: " << perimeter << std::endl;
            res += area * perimeter;
            area = perimeter = 0;
            m_visitedPermiters.clear();
        }
    }

    
    
    return std::to_string(res);
}



void  Day12::calcAreaAndPerimeter(char current_field, Point point, uint64_t& area, uint64_t& perimeter, std::unordered_set<Point>& visited){
    
    static const std::array<Direction, 4> possible_directions = {Direction::NORTH, Direction::SOUTH, Direction::WEST, Direction::EAST};

   if(!point.isInBounds(m_rows, m_cols) || m_maze[point.getX()][point.getY()] != current_field){
        ++perimeter;
        return;
    }


    if(isInContainer(visited, point)){
        return;
    }



    visited.insert(point);
    ++area;

    for(int i = 0; i < 4; i++){
        calcAreaAndPerimeter(current_field, point.moved(possible_directions[i]), area, perimeter, visited);
    }
}



void  Day12::calcAreaAndPerimeter(char current_field, Point point, uint64_t& area, uint64_t& perimeter, std::unordered_set<Point>& visited, std::optional<Direction> prevDirection){
    static const std::array<Direction, 4> possible_directions = {Direction::NORTH, Direction::WEST, Direction::SOUTH, Direction::EAST};

    if(!point.isInBounds(m_rows, m_cols) || m_maze[point.getX()][point.getY()] != current_field){
        if(prevDirection.has_value()){

            Direction previousDirection = prevDirection.value();
            Direction fenceDirection = prevDirection.value();
            fenceDirection.rotate(Direction::Rotation::ROTATE_90);

            bool isHorizontal = fenceDirection.isHorizontal();


        
            Point neighborPoints[2] = {point.moved(fenceDirection), point.moved(fenceDirection.opposite())}; 

            if(isInContainer(m_visitedPermiters, previousDirection)){
                if(!isInContainer(m_visitedPermiters[previousDirection], neighborPoints[0]) && !isInContainer(m_visitedPermiters[previousDirection], neighborPoints[1])){

                    // if(current_field =='E'){
                    //     std::cout << "New Fence: " << point.getX() << " " << point.getY() << std::endl;
                    // }
                    
                    
                    ++perimeter;
                }

                if(isInContainer(m_visitedPermiters[previousDirection], neighborPoints[0]) && isInContainer(m_visitedPermiters[previousDirection], neighborPoints[1])){
                    --perimeter;
                }
            }
            else{
                std::unordered_set<Point> fencePoints{};
                m_visitedPermiters[previousDirection] = fencePoints;

                    // if(current_field =='E'){
                    //     std::cout << "New Fence: " << point.getX() << " " << point.getY() << std::endl;
                    // }
                    
                ++perimeter;
            }

            m_visitedPermiters[previousDirection].insert(point);


        }
        return;
    }

    if(isInContainer(visited, point)){
        return;
    }


    visited.insert(point);
    ++area;

    for(int i = 0; i < 4; i++){
        calcAreaAndPerimeter(current_field, point.moved(possible_directions[i]), area, perimeter, visited, possible_directions[i]);
    }


}


void Day12::parseInput(const std::vector<std::string>& input) {

    m_maze.clear();

    
    if (input.empty()) {
        m_rows = m_cols = 0;
        return;
    }
    
    // Set dimensions
    m_cols = input[0].size();
    m_rows = input.size();
    
    // Parse maze
    m_maze.reserve(m_rows);
    for (const auto& line : input) {
        std::vector<char> row;
        row.reserve(m_cols);
        
        for (char c : line) {
            row.push_back(c);
        }
        
        m_maze.push_back(std::move(row));
    }
}



} // namespace aoc