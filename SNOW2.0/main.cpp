#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "snow2.hpp"

int main(int argc, char* argv[]) {
    std::vector<uint8_t> test_key = {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
        0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10
    };

    std::vector<uint8_t> test_iv = {
        0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
        0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00
    };

    std::string secret_text = "SNOW 2.0 crypto-core operational!";

    std::vector<uint8_t> input_bytes(secret_text.begin(), secret_text.end());
    std::vector<uint8_t> encrypted_bytes;
    std::vector<uint8_t> decrypted_bytes;

    std::cout << "============= SNOW 2.0 SYSTEM TEST =============\n\n";

    Snow2 enc_cipher;
    enc_cipher.InitCipher(test_key, test_iv);
    enc_cipher.ProcessBytes(input_bytes, encrypted_bytes);

    Snow2 dec_cipher;
    dec_cipher.InitCipher(test_key, test_iv);
    dec_cipher.ProcessBytes(encrypted_bytes, decrypted_bytes);

    std::cout << "Original Text:  " << secret_text << "\n\n";

    std::cout << "Ciphertext (HEX): ";
    for (uint8_t b : encrypted_bytes) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)b << " ";
    }
    std::cout << "\n\n";

    std::string recovered_text(decrypted_bytes.begin(), decrypted_bytes.end());
    std::cout << "Recovered Text: " << recovered_text << "\n\n";

    std::cout << "------------------------------------------------\n";
    if (secret_text == recovered_text) {
        std::cout << "[ STATUS: SUCCESS ] Encryption/Decryption match perfectly!\n";
    }
    else {
        std::cout << "[ STATUS: ERROR ] Text mismatch! Check the byte logic.\n";
    }
    std::cout << "================================================\n";

    return 0;
}