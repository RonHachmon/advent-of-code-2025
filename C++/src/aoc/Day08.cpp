#include "Day08.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <numeric>

namespace aoc {


Day08::Day08() 
    : DaySolution(8),
    m_antennaMap{},
    m_cols{0},
    m_rows{0}
{
    
}

std::string Day08::solvePart1(const std::vector<std::string>& input) {
    parseInput(input);
    std::unordered_set<Point> antinodesPoints;
    for(auto& antenna : m_antennaMap) {
        extractAntinodes(antenna.second, antinodesPoints);
    }

    return std::to_string( antinodesPoints.size());
}

void Day08::extractAntinodes(const std::vector<Point>& points, std::unordered_set<Point>& antinodes) {

    for(size_t i = 0; i < points.size() - 1; ++i) {
        for(size_t j = i+1; j < points.size(); ++j) {
            int x_diff = points[j].getX() - points[i].getX();
            int y_diff = points[j].getY() - points[i].getY();

            Point first_antinode = Point(points[i].getX() - x_diff, points[i].getY() - y_diff);
            Point second_antinode = Point(points[j].getX() + x_diff, points[j].getY() + y_diff);

            if(first_antinode.isInBounds(m_rows, m_cols)) {
                antinodes.insert(first_antinode);
            }

            if(second_antinode.isInBounds(m_rows, m_cols)) {
                antinodes.insert(second_antinode);
            }

        }
    }
}

std::string Day08::solvePart2(const std::vector<std::string>& input) {
    parseInput(input);
    std::unordered_set<Point> antinodesPoints;
    
    for(auto& antenna : m_antennaMap) {
        extractAntinodesPartTwo(antenna.second, antinodesPoints);
    }
    
    return std::to_string(antinodesPoints.size());
}

void Day08::parseInput(const std::vector<std::string>& input) {
    m_rows = input.size();
    m_cols = input[0].size();

    int i = 0;
    int j = 0;
    for(auto& line : input) {
        j = 0;
        for(auto& c : line) {
        
            if(c == '.'){
                ++j;
                continue;
            }
            
            m_antennaMap[c].push_back(Point(i, j));
            ++j;
        }
        ++i;
    } 
}



// void Day08::extractAntinodesPartTwo(const std::vector<Point>& points, std::unordered_set<Point>& antinodes) {
//     if (points.size() > 1) {
//         for (const Point& p : points) {
//             antinodes.insert(p);
//         }
//     }

//     for(size_t i = 0; i < points.size() - 1; ++i) {
//         for(size_t j = i+1; j < points.size(); ++j) {
//             int x_diff = points[j].getX() - points[i].getX();
//             int y_diff = points[j].getY() - points[i].getY();

//             int gcd = std::gcd(std::abs(x_diff), std::abs(y_diff));
//             if(gcd == 0) continue;

//             int step_x = x_diff / gcd;
//             int step_y = y_diff / gcd;

//             // Insert antinodes BETWEEN the two antennas
//             for (int step = 1; step < gcd; ++step) {
//                 Point p = Point(points[i].getX() + step * step_x,
//                                 points[i].getY() + step * step_y);
//                 if (p.isInBounds(m_rows, m_cols)) {
//                     antinodes.insert(p);
//                 }
//             }

//             // Extend backward
//             Point current = Point(points[i].getX() - step_x, points[i].getY() - step_y);
//             while(current.isInBounds(m_rows, m_cols)) {
//                 antinodes.insert(current);
//                 current = Point(current.getX() - step_x, current.getY() - step_y);
//             }

//             // Extend forward
//             current = Point(points[j].getX() + step_x, points[j].getY() + step_y);
//             while(current.isInBounds(m_rows, m_cols)) {
//                 antinodes.insert(current);
//                 current = Point(current.getX() + step_x, current.getY() + step_y);
//             }
//         }
//     }
// }

void Day08::extractAntinodesPartTwo(const std::vector<Point>& points, std::unordered_set<Point>& antinodes) {
    if (points.size() > 1) {
        for (const Point& p : points) {
            antinodes.insert(p);
        }
    }

    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            int x_diff = points[j].getX() - points[i].getX();
            int y_diff = points[j].getY() - points[i].getY();

            int gcd = std::gcd(std::abs(x_diff), std::abs(y_diff));
            if (gcd == 0) continue;

            int step_x = x_diff / gcd;
            int step_y = y_diff / gcd;

            // Walk backward from point i
            Point current = points[i];
            while (true) {
                current = Point(current.getX() - step_x, current.getY() - step_y);
                if (!current.isInBounds(m_rows, m_cols)) break;
                antinodes.insert(current);
            }

            // Walk forward from point i
            current = points[i];
            while (true) {
                current = Point(current.getX() + step_x, current.getY() + step_y);
                if (!current.isInBounds(m_rows, m_cols)) break;
                antinodes.insert(current);
            }
        }
    }
}




} // namespace aoc
