#include "snow2.hpp"
#include "snow2tab.h"

Snow2::Snow2() : r1(0), r2(0), head(0) {}

void Snow2::InitCipher(const std::vector<uint8_t>& key, const std::vector<uint8_t>& iv) {
	// TODO: Key and IV setup according to the SNOW 2.0 specification
}

uint32_t Snow2::StreamNext() {
	// TODO: Generate the next 32-bit word of the keystream based on the current state of the cipher
	return 0;
}

void Snow2::ProcessBytes(const std::vector<uint8_t>& input, std::vector<uint8_t>& output) {
	// TODO: generate the keystream and XOR it with the input to produce the output
}