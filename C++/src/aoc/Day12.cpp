#include "Day12.hpp"
#include <iostream>
#include <sstream>
#include <numeric>
#include "ContainerUlits.hpp"
#include "Point.hpp"
#include "Direction.hpp"
#include <array>

namespace aoc {



Day12::Day12() : 
    DaySolution(12),
    gardenMap_{},
    mapRows_{0},
    mapCols_{0},
    visitedFenceSegments_{}
{}

std::string Day12::solvePart1(const std::vector<std::string>& input) {
    parseGardenMap(input);
    uint64_t totalCost = calculateTotalFencingCost(false);
    return std::to_string(totalCost);
}

std::string Day12::solvePart2(const std::vector<std::string>& input) {
    parseGardenMap(input);
    uint64_t totalCost = calculateTotalFencingCost(true);
    return std::to_string(totalCost);
}

void Day12::parseGardenMap(const std::vector<std::string>& input) {
    gardenMap_.clear();
    
    if (input.empty()) {
        mapRows_ = mapCols_ = 0;
        return;
    }
    
    mapCols_ = input[0].size();
    mapRows_ = input.size();
    
    gardenMap_.reserve(mapRows_);
    for (const auto& line : input) {
        std::vector<char> row;
        row.reserve(mapCols_);
        
        for (char plantType : line) {
            row.push_back(plantType);
        }
        
        gardenMap_.push_back(std::move(row));
    }
}

uint64_t Day12::calculateTotalFencingCost(bool useBulkDiscount) {
    uint64_t totalCost = 0;
    std::unordered_set<Point> globalVisited;
    
    for (size_t row = 0; row < mapRows_; ++row) {
        for (size_t col = 0; col < mapCols_; ++col) {
            Point currentPoint{static_cast<int>(row), static_cast<int>(col)};
            
            if (isInContainer(globalVisited, currentPoint)) {
                continue;
            }
            
            RegionMetrics metrics;
            char plantType = getPlantTypeAt(currentPoint);
            
            exploreRegion(plantType, currentPoint, metrics, globalVisited, useBulkDiscount);
                        
            totalCost += metrics.calculateCost();
            visitedFenceSegments_.clear();
        }
    }
    
    return totalCost;
}

void Day12::exploreRegion(char plantType, Point startPoint, RegionMetrics& metrics, 
                         std::unordered_set<Point>& globalVisited, bool useBulkDiscount) {
    if (useBulkDiscount) {
        calculateBulkDiscountPerimeter(plantType, startPoint, metrics, globalVisited, std::nullopt);
    } else {
        calculateBasicPerimeter(plantType, startPoint, metrics, globalVisited);
    }
}

void Day12::calculateBasicPerimeter(char plantType, Point currentPoint, RegionMetrics& metrics, 
                                   std::unordered_set<Point>& regionVisited) {

    static const  std::array<Direction, 4> CARDINAL_DIRECTIONS = {
        Direction::NORTH, Direction::SOUTH, Direction::WEST, Direction::EAST
    };


    if (!isValidGardenCell(currentPoint, plantType)) {
        ++metrics.perimeter;
        return;
    }
    
    if (isInContainer(regionVisited, currentPoint)) {
        return;
    }
    
    regionVisited.insert(currentPoint);
    ++metrics.area;
    
    for (const Direction& direction : CARDINAL_DIRECTIONS) {
        Point nextPoint = currentPoint.moved(direction);
        calculateBasicPerimeter(plantType, nextPoint, metrics, regionVisited);
    }
}

void Day12::calculateBulkDiscountPerimeter(char plantType, Point currentPoint, RegionMetrics& metrics, 
                                         std::unordered_set<Point>& regionVisited, 
                                         std::optional<Direction> previousDirection) {

    static const std::array<Direction, 4> CLOCKWISE_DIRECTIONS = {
        Direction::NORTH, Direction::WEST, Direction::SOUTH, Direction::EAST
    };

    if (!isValidGardenCell(currentPoint, plantType)) {
        if (previousDirection.has_value()) {
            Direction fenceDirection = previousDirection.value();
            
            // Initialize fence direction tracking if needed
            if (!isInContainer(visitedFenceSegments_, fenceDirection)) {
                std::unordered_set<Point> fencePoints;
                visitedFenceSegments_[fenceDirection] = fencePoints;
                ++metrics.perimeter;
            } else {
                
                if (shouldIncrementPerimeter(currentPoint, fenceDirection)) {
                    ++metrics.perimeter;
                }

                //coonecting fence loop
                if (shouldDecrementPerimeter(currentPoint, fenceDirection)) {
                    --metrics.perimeter;
                }
            }
            
            recordFencePoint(currentPoint, fenceDirection);
        }
        return;
    }
    
    if (isInContainer(regionVisited, currentPoint)) {
        return;
    }
    
    regionVisited.insert(currentPoint);
    ++metrics.area;
    
    for (const Direction& direction : CLOCKWISE_DIRECTIONS) {
        Point nextPoint = currentPoint.moved(direction);
        calculateBulkDiscountPerimeter(plantType, nextPoint, metrics, regionVisited, direction);
    }
}

bool Day12::isValidGardenCell(const Point& point, char expectedPlantType) const {
    return !isOutOfBounds(point) && getPlantTypeAt(point) == expectedPlantType;
}

bool Day12::isOutOfBounds(const Point& point) const {
    return !point.isInBounds(static_cast<int>(mapRows_), static_cast<int>(mapCols_));
}

char Day12::getPlantTypeAt(const Point& point) const {
    return gardenMap_[point.getX()][point.getY()];
}

bool Day12::shouldIncrementPerimeter(const Point& fencePoint, Direction fenceDirection) const {
    if (!isInContainer(visitedFenceSegments_, fenceDirection)) {
        return true;
    }
    
    Direction perpendicularDirection = fenceDirection;
    perpendicularDirection.rotate(Direction::Rotation::ROTATE_90);
    
    Point neighborPoints[2] = {
        fencePoint.moved(perpendicularDirection), 
        fencePoint.moved(perpendicularDirection.opposite())
    };
    
    const auto& existingFencePoints = visitedFenceSegments_.at(fenceDirection);
    return !isInContainer(existingFencePoints, neighborPoints[0]) && 
           !isInContainer(existingFencePoints, neighborPoints[1]);
}

bool Day12::shouldDecrementPerimeter(const Point& fencePoint, Direction fenceDirection) const {
    if (!isInContainer(visitedFenceSegments_, fenceDirection)) {
        return false;
    }
    
    Direction perpendicularDirection = fenceDirection;
    perpendicularDirection.rotate(Direction::Rotation::ROTATE_90);
    
    Point neighborPoints[2] = {
        fencePoint.moved(perpendicularDirection), 
        fencePoint.moved(perpendicularDirection.opposite())
    };
    
    const auto& existingFencePoints = visitedFenceSegments_.at(fenceDirection);
    return isInContainer(existingFencePoints, neighborPoints[0]) && 
           isInContainer(existingFencePoints, neighborPoints[1]);
}

void Day12::recordFencePoint(const Point& fencePoint, Direction fenceDirection) {
    visitedFenceSegments_[fenceDirection].insert(fencePoint);
}

} // namespace aoc
