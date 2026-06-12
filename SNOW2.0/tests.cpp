#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <stdexcept>
#include "snow2.hpp"

void test_encryption_mode(const std::string& mode_name, const std::vector<uint8_t>& key, const std::vector<uint8_t>& iv, const std::string& plaintext) {
    std::cout << "\n================================================\n";
    std::cout << "RUNNING: " << mode_name << "\n";
    std::cout << "================================================\n";

    std::vector<uint8_t> input_bytes(plaintext.begin(), plaintext.end());
    std::vector<uint8_t> encrypted;
    std::vector<uint8_t> decrypted;

    try {
        Snow2 enc;
        enc.InitCipher(key, iv);
        enc.ProcessBytes(input_bytes, encrypted);

        Snow2 dec;
        dec.InitCipher(key, iv);
        dec.ProcessBytes(encrypted, decrypted);

        std::string recovered(decrypted.begin(), decrypted.end());
        
        std::cout << "Original Text:  " << plaintext << "\n";
        
        std::cout << "Ciphertext HEX: ";
        for (size_t i = 0; i < encrypted.size() && i < 16; ++i) { 
            std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)encrypted[i] << " ";
        }
        if (encrypted.size() > 16) std::cout << "...";
        std::cout << "\n";
        
        std::cout << "Recovered Text: " << recovered << "\n\n";

        if (plaintext == recovered) {
            std::cout << "[ STATUS: SUCCESS ] The ghoul has been fed (Data matched perfectly!)\n";
        } else {
            std::cout << "[ STATUS: ERROR ] Tragedy happened! Text mismatch.\n";
        }
    } catch (const std::exception& e) {
        std::cout << "[ EXCEPTION CAUGHT ] " << e.what() << "\n";
    }
}

void run_official_test_vectors() {
    std::vector<uint8_t> iv = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00};
    
    std::vector<uint8_t> key_128 = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10};
    
    std::vector<uint8_t> key_256 = {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10,
        0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20
    };
    
    std::vector<uint8_t> bad_key = {0xDE, 0xAD};

    std::string anime_quote_1 = "Oshiete, oshiete yo sono shikumi wo";
    std::string anime_quote_2 = "I am a ghoul. You are my prey.";

    test_encryption_mode("128-BIT KANEKI MODE", key_128, iv, anime_quote_1);
    test_encryption_mode("256-BIT CENTIPEDE MODE", key_256, iv, anime_quote_2);
    test_encryption_mode("FOOL-PROOF EXCEPTION TEST", bad_key, iv, "This should trigger the 1000-7 error.");
}