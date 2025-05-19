#include "Day09.hpp"
#include <iostream>
#include <numeric>
#include "ContainerUlits.hpp"

namespace aoc {

Day09::Day09() : 
    DaySolution(9),
    m_memory_blocks{},
    m_fit_map{}
{
}

void Day09::parseInput(const std::vector<std::string>& input) {
    clearDataStructures();
    
    if (input.empty()) {
        return;
    } 

    const std::string& diskMap = input[0];
    parseDiskMap(diskMap);
}

void Day09::clearDataStructures() {
    m_memory_blocks.clear();
    for (auto& list : m_fit_map) {
        list.clear();
    }
}

void Day09::parseDiskMap(const std::string& diskMap) {
    size_t fileId = 0;
    
    for (size_t i = 0; i < diskMap.size(); i += 2) {
        uint8_t blockedSpace = diskMap[i] - '0';
        uint8_t freeSpace = (i + 1 < diskMap.size()) ? (diskMap[i + 1] - '0') : 0;
        
        MemoryBlock memoryBlock(fileId, blockedSpace, freeSpace);
        m_memory_blocks.push_back(memoryBlock);
        m_fit_map[blockedSpace].emplace_front(memoryBlock);

        fileId++;
    }
}

std::string Day09::solvePart1(const std::vector<std::string>& input) {
    parseInput(input);
    
    std::vector<MemoryBlock> compactMap = createFirstFitCompactMap();
    
    uint64_t result = calculateResult(compactMap);
    return std::to_string(result);
}

std::vector<Day09::MemoryBlock> Day09::createFirstFitCompactMap() {
    std::vector<MemoryBlock> compactMap;
    
    size_t left = 0;
    size_t right = m_memory_blocks.size() - 1;

    while (left < right) {
        compactMap.emplace_back(m_memory_blocks[left].id, m_memory_blocks[left].blockedSpace, 0);
    
        while (left < right && m_memory_blocks[left].freeSpace > 0) {
            if (m_memory_blocks[right].blockedSpace <= m_memory_blocks[left].freeSpace) {
                compactMap.emplace_back(m_memory_blocks[right].id, m_memory_blocks[right].blockedSpace, 0);

                m_memory_blocks[left].freeSpace -= m_memory_blocks[right].blockedSpace;
                m_memory_blocks[right].blockedSpace = 0;
                --right;
            } else {
                compactMap.emplace_back(m_memory_blocks[right].id, m_memory_blocks[left].freeSpace, 0);
                m_memory_blocks[right].blockedSpace -= m_memory_blocks[left].freeSpace;
                m_memory_blocks[left].freeSpace = 0;
            }
        }
        ++left;
    }

    // Handle the case when left equals right
    if (left == right && m_memory_blocks[left].blockedSpace != 0) {
        compactMap.emplace_back(m_memory_blocks[left].id, m_memory_blocks[left].blockedSpace, 0);
    }

    return compactMap;
}

std::string Day09::solvePart2(const std::vector<std::string>& input) {
    parseInput(input);
    
    std::vector<MemoryBlock> compactMap = createBestFitCompactMap();
    
    uint64_t result = calculateResult(compactMap);
    return std::to_string(result);
}

std::vector<Day09::MemoryBlock> Day09::createBestFitCompactMap() {
    std::vector<MemoryBlock> compactMap;
    std::unordered_set<size_t> insertedIds;

    size_t index = 0;

    while (insertedIds.size() < m_memory_blocks.size()) {
        auto& currentBlock = m_memory_blocks[index];
        ++index;
        
        if (isInContainer(insertedIds, currentBlock.id)) {
            continue;
        }
        
        compactMap.emplace_back(currentBlock.id, currentBlock.blockedSpace, 0);
        insertedIds.insert(currentBlock.id);
    
        while (insertedIds.size() < m_memory_blocks.size() && currentBlock.freeSpace > 0) {
            auto bestFitBlock = findBestFitBlock(currentBlock.freeSpace, insertedIds);
            
            if (bestFitBlock.has_value()) {
                compactMap.emplace_back(bestFitBlock->id, bestFitBlock->blockedSpace, 0);
                insertedIds.insert(bestFitBlock->id);
                currentBlock.freeSpace -= bestFitBlock->blockedSpace;
            } else {
                compactMap.emplace_back(0, currentBlock.freeSpace, 0);
                currentBlock.freeSpace = 0;
            }
        }    
    }

    return compactMap;
}

std::optional<Day09::MemoryBlock> Day09::findBestFitBlock(uint8_t availableSpace, 
                                                          const std::unordered_set<size_t>& insertedIds) {
    int maxId = 0;
    int bestFitSize = -1;

    for (int i = availableSpace; i >= 1; --i) {
        if (!m_fit_map[i].empty()) {
            const auto& frontBlock = m_fit_map[i].front();
            if (frontBlock.id > maxId && !isInContainer(insertedIds, frontBlock.id)) {
                bestFitSize = i;
                maxId = frontBlock.id;
            }
        }
    }

    if (bestFitSize != -1) {
        MemoryBlock bestFitBlock = m_fit_map[bestFitSize].front();
        m_fit_map[bestFitSize].pop_front();
        return bestFitBlock;
    }
    
    return std::nullopt;
}

uint64_t Day09::calculateResult(const std::vector<MemoryBlock>& compactMap) {
    uint64_t result = 0;
    size_t position = 0;

    for (const auto& block : compactMap) {
        for (int i = 0; i < block.blockedSpace; i++) {
            result += position * block.id;
            position++;
        }
    }

    return result;
}

} // namespace aoc
