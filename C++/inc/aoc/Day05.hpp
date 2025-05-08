#ifndef AOC_DAY05_HPP
#define AOC_DAY05_HPP

#include "DaySolution.hpp"
#include <string>
#include <vector>
#include <deque>
#include <unordered_map>
#include <unordered_set>

namespace aoc {

class Day05 : public DaySolution {
public:
    explicit Day05();
    
    std::string solvePart1(const std::vector<std::string>& input) override;
    std::string solvePart2(const std::vector<std::string>& input) override;

private:
    // Maps protocol IDs to their prerequisite protocols
    std::unordered_map<int, std::unordered_set<int>> prerequisiteMap;
    
    // List of protocol sequences stored as deques
    std::vector<std::deque<int>> protocolSequences;
    
    // Helper methods for clarity and separation of concerns
    void parsePrerequisiteMap(const std::vector<std::string>& input);
    void parseProtocolSequences(const std::vector<std::string>& input);

    int calculateTotalValueFromValidSequences();

    int calculateTotalValueFromInValidSequences();

    std::vector<int> parseProtocolSequence(const std::string& line);


    void Day05:: FixProtocol(
        int protocolTofix,
        std::list<int>& alignedProtocols,  
        const std::unordered_set<int>& seenProtocols,
        const std::unordered_set<int>& executedProtocols,
        std::unordered_set<int>& alignedProtocolsSet
    );
    

    bool isValidProtocolSequence(const std::deque<int>& protocols);
    bool arePrerequisitesSatisfied(
        int protocol, 
        const std::unordered_set<int>& seenProtocols,
        const std::unordered_set<int>& executedProtocols
    );

};

} // namespace aoc

#endif // AOC_DAY05_HPP