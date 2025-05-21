#include "Day11.hpp"
#include <iostream>
#include <sstream>
#include <numeric>
 
#include "ContainerUlits.hpp"

namespace aoc {

Day11::Day11() :
    DaySolution(11),
    m_stones{},
    m_rules{ std::make_shared<Zero>(), std::make_shared<EvenDigits>(), std::make_shared<Default>() }
{
    m_zeroSplit.reserve(10000);
}

std::string Day11::solvePart1(const std::vector<std::string>& input) {
    parseInput(input);

    return std::to_string(findTotalSplits(25));
}

std::string Day11::solvePart2(const std::vector<std::string>& input) {
    parseInput(input);

    
    return std::to_string(findTotalSplits(75));
}

uint64_t Day11::findTotalSplits(size_t blinks) const {
    uint64_t total_count = 0;

    for(auto& stone : m_stones) {
        total_count += splitStoneWithCache(stone, blinks);
    }

    return total_count;
}

struct LevelAndStone
{
    uint64_t split_level;
    uint64_t stone;
};





struct PairHash {
    template <typename T1, typename T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        std::size_t h1 = std::hash<T1>{}(p.first);
        std::size_t h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};


uint64_t Day11::splitStoneWithCache(uint64_t stone, uint64_t remaining_splits) const{

    static std::unordered_map<std::pair<uint64_t, uint64_t>, uint64_t, PairHash> split_cache;

 
    std::pair<uint64_t, uint64_t> cacheKey(stone, remaining_splits);
    

    auto cacheIter = split_cache.find(cacheKey);
    if (cacheIter != split_cache.end()) {
        // Found in cache, return the cached result
        return cacheIter->second;
    }
    
    if (remaining_splits == 0) {
        return 1; // This stone contributes 1 to the count
    }
    
    // Initialize the count for this stone and remaining_splits
    uint64_t totalCount = 0;
    
    // Apply rules and recursively split stones
    for (auto& rule : m_rules) {
        if (rule->is_on_terms(stone)) {
            std::vector<uint64_t> created_stones = rule->applyRules(stone);
            for (auto& new_stone : created_stones) {


                totalCount += splitStoneWithCache(new_stone, remaining_splits - 1);
                
            }
            split_cache[cacheKey] = totalCount;
            break;
            
        }
        
    }
    

    return split_cache[cacheKey];
}


void Day11::parseInput(const std::vector<std::string>& input) {
    m_stones.clear();
    std::istringstream iss(input[0]);
    uint64_t num;
    while (iss >> num)
    {
        m_stones.push_back(num);
    }
}

uint64_t Day11::splitStoneZeroSpecialized(uint64_t total_splits) {


    auto cacheIter = m_zeroSplit.find(total_splits);
    if (cacheIter != m_zeroSplit.end()) {
        // Found in cache, return the cached result
        return cacheIter->second;
    }
    

    std::list<LevelAndStone> splits_stack{};
    splits_stack.push_back({1, 1});


    uint64_t total_split_count = 0;
    uint64_t current_level = 0;
    LevelAndStone level_and_stone;

    level_and_stone = splits_stack.front();
    splits_stack.pop_front();
    while (current_level < total_splits)
    {
        ++current_level;
        total_split_count = 0;
        //do while loop
        do {
            //std::cout << "Level " << level_and_stone.split_level << " , Stone " << level_and_stone.stone << " " << std::endl;
   
            ++total_split_count;

            // Apply rules and recursively split stones
            for (auto& rule : m_rules) {
                if (rule->is_on_terms(level_and_stone.stone)) {
                    std::vector<uint64_t> created_stones = rule->applyRules(level_and_stone.stone);
                    for (auto& new_stone : created_stones) {
                        splits_stack.push_back({level_and_stone.split_level + 1, new_stone});
                    }
                    break;
                }
            }

            level_and_stone = splits_stack.front();
            splits_stack.pop_front();
        } while (level_and_stone.split_level == current_level);

        //std::cout  << std::endl;

        m_zeroSplit[current_level] = total_split_count;
    }
    
    return m_zeroSplit[current_level]; ;
}

} // namespace aoc