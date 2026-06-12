#pragma once
#include <vector>
#include <cstdint>
#include <string>

class Snow2 {
public:
    Snow2();
    void InitCipher(const std::vector<uint8_t>& key, const std::vector<uint8_t>& iv);
    uint32_t StreamNext();
    void ProcessBytes(const std::vector<uint8_t>& input, std::vector<uint8_t>& output);
    void PrintState(const std::string& label);
private:
    uint32_t s[16];
    uint32_t r1, r2;
    int head;
    uint32_t get_fsm_output();
    void clock_fsm(uint32_t fsm_out);
    void clock_internal(bool initialization_mode, uint32_t fsm_out);
    uint32_t a_mul(uint32_t w);
    uint32_t ainv_mul(uint32_t w);
};