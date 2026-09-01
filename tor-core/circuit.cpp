#include "circuit.h"
#include <random>

std::vector<Relay> Circuit::buildCircuit(int hopCount) {
    std::vector<Relay> path;
    std::random_device rd;
    std::mt19937 gen(rd());
    
    for (int i = 0; i < hopCount; ++i) {
        Relay relay = selectRelay(gen, i == 0, i == hopCount - 1);
        path.push_back(relay);
    }
    
    return path;
}

Relay Circuit::selectRelay(std::mt19937& gen, bool isEntry, bool isExit) {
    // Guard relay selection for entry, exit relay for last hop
    auto& pool = isEntry ? guardRelays : (isExit ? exitRelays : middleRelays);
    std::uniform_int_distribution<> dist(0, pool.size() - 1);
    return pool[dist(gen)];
}