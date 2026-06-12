#include "snow2.hpp"
#include "snow2tab.h"
#include <iostream> 
#include <iomanip>  
#include <string>   

Snow2::Snow2() : r1(0), r2(0), head(0) {
	for (int i = 0; i < 16; ++i) s[i] = 0;
}

uint32_t Snow2::a_mul(uint32_t w) {
	return (w << 8) ^ Snow2Constants::snow_alpha_mul[w >> 24];
}

uint32_t Snow2::ainv_mul(uint32_t w) {
	return (w >> 8) ^ Snow2Constants::snow_alphainv_mul[w & 0xFF];
}

uint32_t Snow2::get_fsm_output() {
	uint32_t s15 = s[(head + 15) % 16];
	return (r1 + s15) ^ r2;
}

void Snow2::clock_fsm(uint32_t fsm_out) {
	uint32_t s5 = s[(head + 5) % 16];
	uint32_t fsmtmp = r2 + s5;

	uint8_t b0 = r1 & 0xFF;
	uint8_t b1 = (r1 >> 8) & 0xFF;
	uint8_t b2 = (r1 >> 16) & 0xFF;
	uint8_t b3 = (r1 >> 24) & 0xFF;

	r2 = Snow2Constants::snow_T0[b0] ^
		Snow2Constants::snow_T1[b1] ^
		Snow2Constants::snow_T2[b2] ^
		Snow2Constants::snow_T3[b3];

	r1 = fsmtmp;
}

void Snow2::clock_internal(bool initialization_mode, uint32_t fsm_out) {
	uint32_t s0 = s[head];
	uint32_t s2 = s[(head + 2) % 16];
	uint32_t s11 = s[(head + 11) % 16];

	uint32_t new_s = a_mul(s0) ^ s2 ^ ainv_mul(s11);

	if (initialization_mode) {
		new_s ^= fsm_out;
	}

	s[head] = new_s;
	head = (head + 1) % 16;
}
void Snow2::InitCipher(const std::vector<uint8_t>& key, const std::vector<uint8_t>& iv) {
	if ((key.size() != 16 && key.size() != 32) || iv.size() != 16) {
		throw std::invalid_argument("Error: Invalid input size. What's 1000 minus 7?");
	}

	uint32_t iv3 = (uint32_t)iv[12] | ((uint32_t)iv[13] << 8) | ((uint32_t)iv[14] << 16) | ((uint32_t)iv[15] << 24);
	uint32_t iv2 = (uint32_t)iv[8] | ((uint32_t)iv[9] << 8) | ((uint32_t)iv[10] << 16) | ((uint32_t)iv[11] << 24);
	uint32_t iv1 = (uint32_t)iv[4] | ((uint32_t)iv[5] << 8) | ((uint32_t)iv[6] << 16) | ((uint32_t)iv[7] << 24);
	uint32_t iv0 = (uint32_t)iv[0] | ((uint32_t)iv[1] << 8) | ((uint32_t)iv[2] << 16) | ((uint32_t)iv[3] << 24);

	if (key.size() == 16) {
		uint32_t k3 = ((uint32_t)key[0] << 24) | ((uint32_t)key[1] << 16) | ((uint32_t)key[2] << 8) | (uint32_t)key[3];
		uint32_t k2 = ((uint32_t)key[4] << 24) | ((uint32_t)key[5] << 16) | ((uint32_t)key[6] << 8) | (uint32_t)key[7];
		uint32_t k1 = ((uint32_t)key[8] << 24) | ((uint32_t)key[9] << 16) | ((uint32_t)key[10] << 8) | (uint32_t)key[11];
		uint32_t k0 = ((uint32_t)key[12] << 24) | ((uint32_t)key[13] << 16) | ((uint32_t)key[14] << 8) | (uint32_t)key[15];

		s[15] = k3;   s[14] = k2;   s[13] = k1;   s[12] = k0;
		s[11] = ~k3;  s[10] = ~k2;  s[9] = ~k1;  s[8] = ~k0;
		s[7] = k3;   s[6] = k2;   s[5] = k1;   s[4] = k0;
		s[3] = ~k3;  s[2] = ~k2;  s[1] = ~k1;  s[0] = ~k0;
	}
	else {
		uint32_t k7 = ((uint32_t)key[0] << 24) | ((uint32_t)key[1] << 16) | ((uint32_t)key[2] << 8) | (uint32_t)key[3];
		uint32_t k6 = ((uint32_t)key[4] << 24) | ((uint32_t)key[5] << 16) | ((uint32_t)key[6] << 8) | (uint32_t)key[7];
		uint32_t k5 = ((uint32_t)key[8] << 24) | ((uint32_t)key[9] << 16) | ((uint32_t)key[10] << 8) | (uint32_t)key[11];
		uint32_t k4 = ((uint32_t)key[12] << 24) | ((uint32_t)key[13] << 16) | ((uint32_t)key[14] << 8) | (uint32_t)key[15];
		uint32_t k3 = ((uint32_t)key[16] << 24) | ((uint32_t)key[17] << 16) | ((uint32_t)key[18] << 8) | (uint32_t)key[19];
		uint32_t k2 = ((uint32_t)key[20] << 24) | ((uint32_t)key[21] << 16) | ((uint32_t)key[22] << 8) | (uint32_t)key[23];
		uint32_t k1 = ((uint32_t)key[24] << 24) | ((uint32_t)key[25] << 16) | ((uint32_t)key[26] << 8) | (uint32_t)key[27];
		uint32_t k0 = ((uint32_t)key[28] << 24) | ((uint32_t)key[29] << 16) | ((uint32_t)key[30] << 8) | (uint32_t)key[31];

		s[15] = k7;  s[14] = k6;  s[13] = k5;  s[12] = k4;
		s[11] = k3;  s[10] = k2;  s[9] = k1;  s[8] = k0;
		s[7] = ~k7; s[6] = ~k6; s[5] = ~k5; s[4] = ~k4;
		s[3] = ~k3; s[2] = ~k2; s[1] = ~k1; s[0] = ~k0;
	}

	s[15] ^= iv0;
	s[12] ^= iv1;
	s[10] ^= iv2;
	s[9] ^= iv3;

	r1 = 0;
	r2 = 0;
	head = 0;

	PrintState("BEFORE 32 CLOCKS (RAW STATE)");

	for (int i = 0; i < 32; ++i) {
		uint32_t fsm_out = get_fsm_output();
		clock_fsm(fsm_out);
		clock_internal(true, fsm_out);
	}

	PrintState("AFTER 32 CLOCKS (READY FOR STREAM)");
}

uint32_t Snow2::StreamNext() {
	uint32_t old_s0 = s[head];
	uint32_t old_s1 = s[(head + 1) % 16];

	clock_internal(false, 0);

	uint32_t fsm_out = get_fsm_output();
	clock_fsm(fsm_out);

	return (r1 + old_s0) ^ r2 ^ old_s1;
}

void Snow2::ProcessBytes(const std::vector<uint8_t>& input, std::vector<uint8_t>& output) {
	output.resize(input.size());
	size_t i = 0;

	while (i + 4 <= input.size()) {

		uint32_t keystream_word = StreamNext();

		uint32_t input_word = (uint32_t)input[i] |
			((uint32_t)input[i + 1] << 8) |
			((uint32_t)input[i + 2] << 16) |
			((uint32_t)input[i + 3] << 24);

		uint32_t output_word = input_word ^ keystream_word;

		output[i] = output_word & 0xFF;
		output[i + 1] = (output_word >> 8) & 0xFF;
		output[i + 2] = (output_word >> 16) & 0xFF;
		output[i + 3] = (output_word >> 24) & 0xFF;

		i += 4;
	}

	if (i < input.size()) {
		uint32_t keystream_word = StreamNext();
		int byte_shift = 0;
		while (i < input.size()) {
			uint8_t keystream_byte = (keystream_word >> (byte_shift * 8)) & 0xFF;
			output[i] = input[i] ^ keystream_byte;
			i++;
			byte_shift++;
		}
	}
}

void Snow2::PrintState(const std::string& label) {
	std::cout << "=== " << label << " ===\n";
	std::cout << "r1:   0x" << std::hex << std::setw(8) << std::setfill('0') << r1 << "\n";
	std::cout << "r2:   0x" << std::hex << std::setw(8) << std::setfill('0') << r2 << "\n";
	std::cout << "head: " << std::dec << head << "\n";
	std::cout << "Register s:\n";
	for (int i = 0; i < 4; ++i) {
		std::cout << "  ";
		for (int j = 0; j < 4; ++j) {
			int idx = i * 4 + j;
			std::cout << "s[" << std::setw(2) << std::dec << idx << "]:0x"
				<< std::hex << std::setw(8) << std::setfill('0') << s[idx] << "  ";
		}
		std::cout << "\n";
	}
	std::cout << "===========================\n\n";
}