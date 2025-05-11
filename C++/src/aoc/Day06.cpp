#include "Day06.hpp"
#include <algorithm>

namespace aoc {

Day06::Day06() 
    : DaySolution(6)
    , m_maze{}
    , m_currentPoint{0, 0}
    , m_currentDirection{}
    , m_rows{0}
    , m_cols{0}
{
}

std::string Day06::solvePart1(const std::vector<std::string>& input) {
    parseInput(input);
    int visitedCount = walkMaze();
    return std::to_string(visitedCount);
}

std::string Day06::solvePart2(const std::vector<std::string>& input) {
    // Placeholder for part 2 implementation
    return std::to_string(5);
}

void Day06::parseInput(const std::vector<std::string>& input) {
    m_rows = input.size();
    m_cols = input[0].size();
    
    m_maze.clear();
    m_maze.reserve(m_rows);
    
    for (int i = 0; i < m_rows; ++i) {
        std::vector<char> row;
        row.reserve(m_cols);
        
        for (int j = 0; j < m_cols; ++j) {
            row.push_back(input[i][j]);
        }
        m_maze.push_back(std::move(row));
    }
    
    findStartingPosition(input);
}

void Day06::findStartingPosition(const std::vector<std::string>& input) {
    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            char c = input[i][j];
            
            if (c == GUARD_NORTH || c == GUARD_EAST || 
                c == GUARD_SOUTH || c == GUARD_WEST) {
                m_currentPoint = Point(i, j);
                m_currentDirection = getDirectionFromChar(c);
                return;
            }
        }
    }
}

Direction Day06::getDirectionFromChar(char c) const {
    switch (c) {
        case GUARD_NORTH: return Direction::NORTH;
        case GUARD_EAST:  return Direction::EAST;
        case GUARD_SOUTH: return Direction::SOUTH;
        case GUARD_WEST:  return Direction::WEST;
        default:          return Direction::NORTH; // Default fallback
    }
}

int Day06::walkMaze() {
    int visitedCount = 0;
    
    while (m_currentPoint.isInBounds(m_rows, m_cols)) {
        // Mark current position as visited
        if (m_maze[m_currentPoint.getX()][m_currentPoint.getY()] != WALKED) {
            ++visitedCount;
            m_maze[m_currentPoint.getX()][m_currentPoint.getY()] = WALKED;
        }
        

        Point nextPoint = getNextPoint();
        
        if (!nextPoint.isInBounds(m_rows, m_cols)) {
            break;
        }

        if (isBlocked(nextPoint)) {
            m_currentDirection.rotate(Direction::Rotation::ROTATE_90);
        }
        

        m_currentPoint.move(m_currentDirection);
    }
    
    return visitedCount;
}

Point Day06::getNextPoint() const
{
    return m_currentPoint.moved(m_currentDirection);
}

bool Day06::isBlocked(const Point& point) const
{
    return m_maze[point.getX()][point.getY()] == BLOCK;
}

} // namespace aoc
