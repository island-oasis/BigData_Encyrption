#include <iostream>
#include <bitset>
#include <string>
#include <cstring>
#include <chrono>
#include <iomanip>
#include <openssl/des.h>

using namespace std;
using namespace std::chrono;

int main() {
    DES_cblock key = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef }; // 64-bit key
    DES_key_schedule key_schedule;
    DES_set_key(&key, &key_schedule);

    string plaintext = "Hello, world!";
    int padding = 8 - plaintext.length() % 8;
    plaintext.append(padding, padding);
    cout << "Plaintext: " << plaintext << endl;

    auto start = high_resolution_clock::now();
    string ciphertext = plaintext;
    for (size_t i = 0; i < ciphertext.length(); i += 8) {
        DES_ecb_encrypt((DES_cblock*)&ciphertext[i], (DES_cblock*)&ciphertext[i], &key_schedule, DES_ENCRYPT);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Ciphertext: ";
    for (size_t i = 0; i < ciphertext.length(); i++) {
        cout << hex << (int)ciphertext[i];
    }
    cout << endl;
    cout << "Encryption time: " << duration.count() << " microseconds" << endl;

    return 0;
}
