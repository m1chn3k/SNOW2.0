#include "snow2.hpp"
#include "snow2tab.h"

Snow2::Snow2() : r1(0), r2(0), head(0) {
	for (int i = 0; i < 16; ++i) s[i] = 0;
}

void Snow2::InitCipher(const std::vector<uint8_t>& key, const std::vector<uint8_t>& iv) {

	uint32_t k3 = ((uint32_t)key[0] << 24) | ((uint32_t)key[1] << 16) | ((uint32_t)key[2] << 8) | (uint32_t)key[3];
	uint32_t k2 = ((uint32_t)key[4] << 24) | ((uint32_t)key[5] << 16) | ((uint32_t)key[6] << 8) | (uint32_t)key[7];
	uint32_t k1 = ((uint32_t)key[8] << 24) | ((uint32_t)key[9] << 16) | ((uint32_t)key[10] << 8) | (uint32_t)key[11];
	uint32_t k0 = ((uint32_t)key[12] << 24) | ((uint32_t)key[13] << 16) | ((uint32_t)key[14] << 8) | (uint32_t)key[15];

	uint32_t iv3 = (uint32_t)iv[0] | ((uint32_t)iv[1] << 8) | ((uint32_t)iv[2] << 16) | ((uint32_t)iv[3] << 24);
	uint32_t iv2 = (uint32_t)iv[4] | ((uint32_t)iv[5] << 8) | ((uint32_t)iv[6] << 16) | ((uint32_t)iv[7] << 24);
	uint32_t iv1 = (uint32_t)iv[8] | ((uint32_t)iv[9] << 8) | ((uint32_t)iv[10] << 16) | ((uint32_t)iv[11] << 24);
	uint32_t iv0 = (uint32_t)iv[12] | ((uint32_t)iv[13] << 8) | ((uint32_t)iv[14] << 16) | ((uint32_t)iv[15] << 24);

	s[15] = k3;   s[14] = k2;   s[13] = k1;   s[12] = k0;
	s[11] = ~k3;  s[10] = ~k2;  s[9] = ~k1;  s[8] = ~k0;
	s[7] = k3;   s[6] = k2;   s[5] = k1;   s[4] = k0;
	s[3] = ~k3;  s[2] = ~k2;  s[1] = ~k1;  s[0] = ~k0;

	s[15] ^= iv0;
	s[12] ^= iv1;
	s[10] ^= iv2;
	s[9] ^= iv3;

	r1 = 0;
	r2 = 0;
	head = 0;

	for (int i = 0; i < 32; ++i) {
		uint32_t fsm_out = get_fsm_output();
		clock_fsm(fsm_out);
		clock_internal(true, fsm_out);
} 
};
uint32_t Snow2::StreamNext() {
	// TODO: Generate the next 32-bit word of the keystream based on the current state of the cipher
	return 0;
}

void Snow2::ProcessBytes(const std::vector<uint8_t>& input, std::vector<uint8_t>& output) {
	// TODO: generate the keystream and XOR it with the input to produce the output
}