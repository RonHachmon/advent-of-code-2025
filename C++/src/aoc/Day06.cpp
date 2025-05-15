#include "Day06.hpp"
#include "ContainerUlits.hpp"
#include <algorithm>



namespace aoc {

// Constants
static constexpr char WALKED = 'X';
static constexpr char BLOCK = '#';
static constexpr char GUARD_NORTH = '^';
static constexpr char GUARD_SOUTH = 'v';
static constexpr char GUARD_WEST = '<';
static constexpr char GUARD_EAST = '>';

Day06::Day06() 
    : DaySolution(6)
    , m_maze{}
    , m_startingPoint{0, 0}
    , m_currentPoint{0, 0}
    , m_startingDirection{}
    , m_currentDirection{}
    , m_rows{0}
    , m_cols{0}
{
}

std::string Day06::solvePart1(const std::vector<std::string>& input) {
    parseInput(input);
    size_t visitedCount = walkMaze().size();
    return std::to_string(visitedCount);
}

std::string Day06::solvePart2(const std::vector<std::string>& input) {
    parseInput(input);
    int loopCount = countPossibleLoops();
    return std::to_string(loopCount);
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
                m_startingPoint = Point(i, j);
                m_currentPoint = m_startingPoint;
                m_startingDirection = getDirectionFromChar(c);
                m_currentDirection = m_startingDirection;
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

std::unordered_set<Point> Day06::walkMaze() {
    int visitedCount = 0;
    std::unordered_set<Point> visited_points;
    
    while (m_currentPoint.isInBounds(m_rows, m_cols)) {
        // Mark current position as visited
        if(!isInContainer(visited_points, m_currentPoint)){
            ++visitedCount;
            visited_points.insert(m_currentPoint);
            
        }

        
        // Check next position
        Point nextPoint = getNextPoint();
        
        // If next point is out of bounds, we're done
        if (!nextPoint.isInBounds(m_rows, m_cols)) {
            break;
        }
        
        // If next point is blocked, rotate
        if (isBlocked(nextPoint)) {
            m_currentDirection.rotate(Direction::Rotation::ROTATE_90);
        } else {
            // Move forward
            m_currentPoint.move(m_currentDirection);
        }
    }
    
    return visited_points;
}

Point Day06::getNextPoint() const {
    return m_currentPoint.moved(m_currentDirection);
}

bool Day06::isBlocked(const Point& point) const {
    return m_maze[point.getX()][point.getY()] == BLOCK;
}

bool Day06::checkForLoop(const Point& blockPosition) {
    using BlockDirectionPair = std::pair<Point, Direction>;
    using BlockVisitedSet = std::unordered_set<BlockDirectionPair, BlockDirectionHash>;
    
    BlockVisitedSet visitedBlocks;
    
    // Reset to starting position and direction
    m_currentPoint = m_startingPoint;
    m_currentDirection = m_startingDirection;
    
    // Temporarily place the block
    char originalChar = m_maze[blockPosition.getX()][blockPosition.getY()];
    m_maze[blockPosition.getX()][blockPosition.getY()] = BLOCK;
    
    bool isLoop = false;
    
    while (getNextPoint().isInBounds(m_rows, m_cols)) {
        // Check next position
        Point nextPoint = getNextPoint();
                
        // If next point is blocked
        if (isBlocked(nextPoint)) {
            // Create a pair of the blocked position and current direction
            BlockDirectionPair blockState = {nextPoint, m_currentDirection};
            
            // If we've hit this block with this direction before, we have a loop
            if (visitedBlocks.find(blockState) != visitedBlocks.end()) {
                isLoop = true;
                break;
            }
            
            visitedBlocks.insert(blockState);
            m_currentDirection.rotate(Direction::Rotation::ROTATE_90);
        }
        else {
            m_currentPoint.move(m_currentDirection);
        }        
    }
    
    // Restore the original character
    m_maze[blockPosition.getX()][blockPosition.getY()] = originalChar;
    
    return isLoop;
}

int Day06::countPossibleLoops() {
    int loopCount = 0;
    std::unordered_set<Point> visited_points = walkMaze();

    for(auto point : visited_points){
        if (point == m_startingPoint || m_maze[point.getX()][point.getY()] == BLOCK) {
                continue;
        }

        if(checkForLoop(point)){
            ++loopCount;
        }
    }
    
    // // Try placing a block at each empty position
    // for (int i = 0; i < m_rows; ++i) {
    //     for (int j = 0; j < m_cols; ++j) {
    //         Point testPoint(i, j);
            
    //         // Skip if this is the starting position or already has a block
    //         if (testPoint == m_startingPoint || m_maze[i][j] == BLOCK) {
    //             continue;
    //         }
            
    //         // Check if placing a block here creates a loop
    //         if (checkForLoop(testPoint)) {
    //             ++loopCount;
    //         }
    //     }
    // }
    
    return loopCount;
}

} // namespace aoc
