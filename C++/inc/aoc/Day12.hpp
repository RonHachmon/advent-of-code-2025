#ifndef AOC_DAY12_HPP
#define AOC_DAY12_HPP

#include "DaySolution.hpp"
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <optional>
#include "Point.hpp"
#include "Direction.hpp"

namespace aoc {

struct RegionMetrics {
    uint64_t area = 0;
    uint64_t perimeter = 0;
    
    void reset() {
        area = 0;
        perimeter = 0;
    }
    
    uint64_t calculateCost() const {
        return area * perimeter;
    }
};

class Day12 : public DaySolution {
public:
    explicit Day12();
   
    std::string solvePart1(const std::vector<std::string>& input) override;
    std::string solvePart2(const std::vector<std::string>& input) override;
   
private:
    void parseGardenMap(const std::vector<std::string>& input);
    uint64_t calculateTotalFencingCost(bool useBulkDiscount = false);
    
    void exploreRegion(char plantType, Point startPoint, RegionMetrics& metrics, 
                      std::unordered_set<Point>& globalVisited, bool useBulkDiscount = false);
    
    void calculateBasicPerimeter(char plantType, Point currentPoint, RegionMetrics& metrics, 
                               std::unordered_set<Point>& regionVisited);
    
    void calculateBulkDiscountPerimeter(char plantType, Point currentPoint, RegionMetrics& metrics, 
                                      std::unordered_set<Point>& regionVisited, 
                                      std::optional<Direction> previousDirection);
    
    bool isValidGardenCell(const Point& point, char expectedPlantType) const;
    bool isOutOfBounds(const Point& point) const;
    char getPlantTypeAt(const Point& point) const;
    
    bool shouldIncrementPerimeter(const Point& fencePoint, Direction fenceDirection) const;
    bool shouldDecrementPerimeter(const Point& fencePoint, Direction fenceDirection) const;
    void recordFencePoint(const Point& fencePoint, Direction fenceDirection);
    
    std::vector<std::vector<char>> gardenMap_;
    size_t mapRows_;
    size_t mapCols_;
    std::unordered_map<Direction, std::unordered_set<Point>> visitedFenceSegments_;

};

} // namespace aoc

#endif // AOC_DAY12_HPP
