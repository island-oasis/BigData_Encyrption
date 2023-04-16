#include <iostream>
#include <cstring>
#include <chrono>
#include <cstdlib>
#include <openssl/aes.h>

using namespace std;

// AES encryption function
void aes_encrypt(unsigned char* plaintext, unsigned char* key, unsigned char* ciphertext)
{
    AES_KEY aesKey;
    AES_set_encrypt_key(key, 128, &aesKey);
    AES_encrypt(plaintext, ciphertext, &aesKey);
}

// AES decryption function
void aes_decrypt(unsigned char* ciphertext, unsigned char* key, unsigned char* plaintext)
{
    AES_KEY aesKey;
    AES_set_decrypt_key(key, 128, &aesKey);
    AES_decrypt(ciphertext, plaintext, &aesKey);
}

int main()
{
    unsigned char plaintext[] = "This is a secret message";
    unsigned char key[] = "This is the secret key";

    // Display the plain text message
    cout << "Plain text message: " << plaintext << endl;

    // Start the timer
    auto start = chrono::high_resolution_clock::now();

    // Encrypt the plain text message
    unsigned char ciphertext[strlen((char*)plaintext)];
    aes_encrypt(plaintext, key, ciphertext);

    // Display the encrypted message
    cout << "Encrypted message: ";
    for (int i = 0; i < strlen((char*)plaintext); i++)
        printf("%02x", ciphertext[i]);
    cout << endl;

    // Decrypt the encrypted message
    unsigned char decryptedtext[strlen((char*)plaintext)];
    aes_decrypt(ciphertext, key, decryptedtext);

    // Display the decrypted message
    cout << "Decrypted message: " << decryptedtext << endl;

    // Stop the timer and display the running time
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Running time: " << duration.count() << " microseconds" << endl;

    return 0;
}
