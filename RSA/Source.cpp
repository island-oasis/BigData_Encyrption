#include <iostream>
#include <cstdlib>
#include <cmath>
#include <chrono>

using namespace std;

// Function to check if a number is prime
bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// Function to generate a random prime number between min and max
int generatePrime(int min, int max) {
    int num = (rand() % (max - min + 1)) + min;
    while (!isPrime(num)) {
        num = (rand() % (max - min + 1)) + min;
    }
    return num;
}

// Function to calculate the greatest common divisor of a and b
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Function to calculate the modular inverse of a modulo m
int modInverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    if (m == 1) return 0;
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) x1 += m0;
    return x1;
}

// Function to generate the public and private keys for RSA encryption
void generateKeys(int p, int q, int& n, int& e, int& d) {
    n = p * q;
    int phi = (p - 1) * (q - 1);
    e = generatePrime(2, phi - 1);
    while (gcd(e, phi) != 1) {
        e = generatePrime(2, phi - 1);
    }
    d = modInverse(e, phi);
}

// Function to encrypt a message using RSA encryption
int encrypt(int message, int e, int n) {
    int cipher = pow(message, e);
    cipher = cipher % n;
    return cipher;
}

// Function to decrypt a message using RSA encryption
int decrypt(int cipher, int d, int n) {
    int message = pow(cipher, d);
    message = message % n;
    return message;
}

int main() {
    // Seed the random number generator
    srand(time(NULL));

    // Generate two random prime numbers
    int p = generatePrime(100, 1000);
    int q = generatePrime(100, 1000);

    // Generate the public and private keys
    int n, e, d;
    auto start = chrono::high_resolution_clock::now();
    generateKeys(p, q, n, e, d);
    auto end = chrono::high_resolution_clock::now();
    double timeTaken = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // Encrypt a message
    int message = 123;
    start = chrono::high_resolution_clock::now();
    int cipher = encrypt(message, e, n);
    end = chrono::high_resolution_clock::now();
    double encryptionTime = chrono::duration_cast<chrono::microseconds>(end - start).count();
    start = chrono::high_resolution_clock::now();
    int decryptedMessage = decrypt(cipher, d, n);
    end = chrono::high_resolution_clock::now();
    double decryptionTime = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Decrypted message: " << decryptedMessage << endl;

    // Print the timing information in microseconds
    cout << "Key generation time: " << timeTaken << " microseconds" << endl;
    cout << "Encryption time: " << encryptionTime << " microseconds" << endl;
    cout << "Decryption time: " << decryptionTime << " microseconds" << endl;

    return 0;
}
