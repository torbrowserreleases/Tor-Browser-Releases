#include <iostream>
#include <vector>
#include <random>

class Obfs4Proxy {
private:
    std::vector<uint8_t> sessionKey;
    
public:
    std::vector<uint8_t> obfuscate(const std::vector<uint8_t>& data) {
        std::vector<uint8_t> obfuscated;
        obfuscated.reserve(data.size() + 16);
        
        // Add random padding header
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 255);
        
        for (int i = 0; i < 16; ++i) {
            obfuscated.push_back(dist(gen));
        }
        
        // XOR with session key
        for (size_t i = 0; i < data.size(); ++i) {
            obfuscated.push_back(data[i] ^ sessionKey[i % sessionKey.size()]);
        }
        
        return obfuscated;
    }
    
    std::vector<uint8_t> deobfuscate(const std::vector<uint8_t>& obfuscated) {
        std::vector<uint8_t> data;
        
        // Skip padding header
        for (size_t i = 16; i < obfuscated.size(); ++i) {
            data.push_back(obfuscated[i] ^ sessionKey[(i - 16) % sessionKey.size()]);
        }
        
        return data;
    }
};