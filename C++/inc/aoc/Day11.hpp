#ifndef AOC_DAY11_HPP
#define AOC_DAY11_HPP

#include "DaySolution.hpp"
#include <list>
#include <vector>
#include <cmath> 
#include <memory> 
#include <unordered_map>

namespace aoc {


    
class Rule {
public:
    virtual bool is_on_terms(uint64_t value) const = 0;
    virtual std::vector<uint64_t> applyRules(uint64_t value) const = 0;
    virtual ~Rule() = default;
};

class Zero : public Rule {
public:

    bool is_on_terms(uint64_t value) const override {
        return value == 0;
    }

    std::vector<uint64_t> applyRules(uint64_t value) const override {
        return {1};
    }
};

class EvenDigits : public Rule {
public:
    bool is_on_terms(uint64_t value) const override {
        return (count_digits(value) % 2) == 0;
    }

    std::vector<uint64_t> applyRules(uint64_t value) const override {
        int digits = count_digits(value)/2;
        uint64_t num = 1;

        for (int i = 0; i < digits; i++) {
            num *= 10;
        }
        return {value/num, value%num};
    }
private:
    int count_digits(uint64_t num) const {
        if (num == 0){
            return 1;
        } 

        return floor(log10(num)) + 1;
    }
};

class Default : public Rule {
public:
    bool is_on_terms(uint64_t value) const override {
        return true;
    }

    std::vector<uint64_t> applyRules(uint64_t value) const override {
        return {value * 2024};
    }
};

class Day11 : public DaySolution {
public:
    explicit Day11();
   
    std::string solvePart1(const std::vector<std::string>& input) override;
    std::string solvePart2(const std::vector<std::string>& input) override;

    uint64_t splitStoneZeroSpecialized( uint64_t total_splits);

    

private:

    uint64_t findTotalSplits(size_t blinks) const;

    void parseInput(const std::vector<std::string>& input);

    uint64_t splitStoneWithCache(uint64_t stone, uint64_t remaining_splits) const;

    


private:
    std::vector<uint64_t> m_stones;
    std::vector<std::shared_ptr<Rule>> m_rules;

    std::unordered_map<uint64_t, uint64_t> m_zeroSplit;


};

} // namespace aoc

#endif // AOC_DAY11_HPP
