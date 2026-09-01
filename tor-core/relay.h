#pragma once
#include <string>
#include <vector>

struct Relay {
    std::string nickname;
    std::string fingerprint;
    std::string address;
    uint16_t orPort;
    uint16_t dirPort;
    std::vector<uint8_t> identity;
    bool isGuard;
    bool isExit;
    uint64_t bandwidth;
};