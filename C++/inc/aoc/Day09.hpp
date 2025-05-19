#ifndef AOC_DAY09_HPP
#define AOC_DAY09_HPP

#include "DaySolution.hpp"
#include <vector>
#include <string>
#include <unordered_map>
#include <optional>
#include <array>
#include <list>
#include <unordered_set>
#include "Point.hpp"

namespace aoc {

class Day09 : public DaySolution {
public:
    struct MemoryBlock {
        MemoryBlock(size_t id, uint8_t blockedSpace, uint8_t freeSpace) :
            id(id),
            blockedSpace(blockedSpace),
            freeSpace(freeSpace) 
        {
        }
        
        size_t id = 0;
        uint8_t blockedSpace = 0;
        uint8_t freeSpace = 0;
    };

public:
    explicit Day09();
   
    std::string solvePart1(const std::vector<std::string>& input) override;
    std::string solvePart2(const std::vector<std::string>& input) override;

private:
    void parseInput(const std::vector<std::string>& input);
    void clearDataStructures();
    void parseDiskMap(const std::string& diskMap);
    
    std::vector<MemoryBlock> createFirstFitCompactMap();
    std::vector<MemoryBlock> createBestFitCompactMap();
    std::optional<MemoryBlock> findBestFitBlock(uint8_t availableSpace, 
                                                const std::unordered_set<size_t>& insertedIds);
    uint64_t calculateResult(const std::vector<MemoryBlock>& compactMap);

private:
    std::vector<MemoryBlock> m_memory_blocks;
    std::array<std::list<MemoryBlock>, 10> m_fit_map;
};

} // namespace aoc

#endif // AOC_DAY09_HPP
