#include "Day05.hpp"
#include "ContainerUlits.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <unordered_set>
#include <vector>
#include <deque>

namespace aoc {


struct ProtocolAndOrder{
    int protocol;
    int order;
};

Day05::Day05() : DaySolution(5), prerequisiteMap{}, protocolSequences{} {
}

std::string Day05::solvePart1(const std::vector<std::string>& input) {
    if (input.empty()) {
        return "0";
    }

    parsePrerequisiteMap(input);
    parseProtocolSequences(input);
    return std::to_string(calculateTotalValueFromValidSequences());
}

void Day05::parsePrerequisiteMap(const std::vector<std::string>& input) {
    prerequisiteMap.clear();
    
    for (const auto& line : input) {
        if (line.empty()) {
            break;
        }
        
        size_t delimiterPos = line.find('|');
        if (delimiterPos == std::string::npos) {
            continue;
        }
        
        try {
            int protocol = std::stoi(line.substr(delimiterPos + 1));
            int prerequisite = std::stoi(line.substr(0, delimiterPos));
            prerequisiteMap[protocol].insert(prerequisite);
        } catch (const std::exception& e) {
            std::cerr << "Error parsing line: " << line << " - " << e.what() << std::endl;
        }
    }
}

void Day05::parseProtocolSequences(const std::vector<std::string>& input) {
    protocolSequences.clear();
    bool mapSectionPassed = false;
    
    for (const auto& line : input) {
        if (line.empty()) {
            mapSectionPassed = true;
            continue;
        }
        
        if (!mapSectionPassed) {
            continue;
        }
        
        auto protocols = parseProtocolSequence(line);
        if (!protocols.empty()) {
            std::deque<int> protocolDeque(protocols.begin(), protocols.end());
            protocolSequences.push_back(protocolDeque);
        }
    }
}



std::vector<int> Day05::parseProtocolSequence(const std::string& line) {
    std::vector<int> protocols;
    size_t startPos = 0;
    size_t delimiterPos = line.find(',', startPos);
    
    while (true) {
        try {
            int protocol = std::stoi(line.substr(startPos, delimiterPos - startPos));
            protocols.push_back(protocol);
        } catch (const std::exception& e) {
            std::cerr << "Error parsing protocol: " << line.substr(startPos, delimiterPos - startPos) 
                      << " - " << e.what() << std::endl;
        }
        
        if (delimiterPos == std::string::npos) {
            break;
        }
        
        startPos = delimiterPos + 1;
        delimiterPos = line.find(',', startPos);
    }
    
    return protocols;
}

bool Day05::isValidProtocolSequence(const std::deque<int>& protocols) {
    std::unordered_set<int> seenProtocols(protocols.begin(), protocols.end());
    std::unordered_set<int> executedProtocols;
    
    for (const auto& protocol : protocols) {
        if (!arePrerequisitesSatisfied(protocol, seenProtocols, executedProtocols)) {
            return false;
        }
        executedProtocols.insert(protocol);
    }
    
    return true;
}

bool Day05::arePrerequisitesSatisfied(
    int protocol, 
    const std::unordered_set<int>& seenProtocols,
    const std::unordered_set<int>& executedProtocols
) {
    for (const auto& prerequisite : prerequisiteMap[protocol]) {
        

        if (isInContainer(seenProtocols, prerequisite) && !isInContainer(executedProtocols, prerequisite)) {
            return false;
        }

    }
    
    return true;
}

int Day05::calculateTotalValueFromValidSequences() {
    int totalValue = 0;
    
    for (const auto& sequence : protocolSequences) {
        if (isValidProtocolSequence(sequence)) {
            
            // Calculate the middle value of the sequence
            if (!sequence.empty()) {
                totalValue += sequence.at(sequence.size() / 2);
            }
        }
    }
    
    return totalValue;
}

void Day05:: FixProtocol(
    int protocolTofix,
    std::list<int>& alignedProtocols,  
    const std::unordered_set<int>& seenProtocols,
    const std::unordered_set<int>& executedProtocols,
    std::unordered_set<int>& alignedProtocolsSet
)
{
    auto& prequistedProtocols = prerequisiteMap[protocolTofix];
    for (const auto& prerequisite : prequistedProtocols) {
        if(!isInContainer(seenProtocols, prerequisite)){
            continue;
            
        }

        if (isInContainer(executedProtocols, prerequisite) || isInContainer(alignedProtocolsSet, prerequisite)){
            continue;
        }
        else{
            FixProtocol(prerequisite, alignedProtocols, seenProtocols, executedProtocols, alignedProtocolsSet);

        }
    }
    alignedProtocolsSet.insert(protocolTofix);
    alignedProtocols.push_back(protocolTofix);
    return;
}

int Day05::calculateTotalValueFromInValidSequences() {
    int totalValue = 0;
    
    for (auto& sequence : protocolSequences) {
        if (!isValidProtocolSequence(sequence)) {

            std::vector<int> fixedProtocol{};
            std::unordered_set<int> seenProtocols(sequence.begin(), sequence.end());
            std::unordered_set<int> executedProtocols{};

            std::unordered_set<int> alignedProtocols{};

            
            for (const auto& protocol : sequence) {
                
                if(isInContainer(executedProtocols, protocol)){
                    continue;
                }


                if (!arePrerequisitesSatisfied(protocol, seenProtocols, executedProtocols)) {
                    std::list<int> alignProtocols{};
                    FixProtocol(protocol, alignProtocols, seenProtocols, executedProtocols,alignedProtocols);


                    for(int alignedProtocol :alignProtocols){
                        if(!isInContainer(executedProtocols, alignedProtocol)){
                            executedProtocols.insert(alignedProtocol);
                            fixedProtocol.push_back(alignedProtocol);                            
                        }
                    }
                }
                else {
                    executedProtocols.insert(protocol);
                    fixedProtocol.push_back(protocol);

                }
            
            }

            if (!fixedProtocol.empty()) {
                totalValue += fixedProtocol.at(sequence.size() / 2);
            }
        }
    }
    
    return totalValue;
}

std::string Day05::solvePart2(const std::vector<std::string>& input) {
    // For this implementation, we'll reuse our protocol processing logic
    if (input.empty()) {
        return "0";
    }

    parsePrerequisiteMap(input);
    parseProtocolSequences(input);
    
    return std::to_string(calculateTotalValueFromInValidSequences());
}

} // namespace aoc