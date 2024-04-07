
#include<bits/stdc++.h>
using namespace std;

int pow(int base, int exponent, int modulus) {
  int result = 1;
  while (exponent > 0) {
    if (exponent % 2 == 1) {
      result = (result * base) % modulus;
    }
    exponent >>= 1;
    base = (base * base) % modulus;
  }
  return result;
}


int modInverse(int e, int p) {
    for (int i = 1; i < p; i++) {
        if ((e * i) % p == 1) {
            return i;
        }
    }
    throw runtime_error("Modular inverse not found");
}

pair<pair<int, int>, int> generateKeyPair(int p, int g) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, p - 1);

    int a = dis(gen);
    int A = pow(g, a, p);
    return {{p, g}, a}; // Public key, Private key
}

pair<int, int> encrypt(int message, pair<int, int> publicKey) {
    int p = publicKey.first, g = publicKey.second;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, p - 1);

    int k = dis(gen);
    int C1 = pow(g, k, p);
    int C2 = (message * pow(publicKey.second, k, p)) % p;
    return {C1, C2};
}

int decrypt(pair<int, int> ciphertext, int privateKey, int p) {
    int a = privateKey;
    int C1 = ciphertext.first, C2 = ciphertext.second;
    int k_inv = modInverse(C1, p);
    int m = (C2 * k_inv) % p;
    return m;
}

int main() {
    cout<<"Illustratting the EIGamal encryption technique"<<endl;
    int prime = 17;  // Prime number
    int generator = 3;   // Generator

    auto keys = generateKeyPair(prime, generator);
    int message = 5;  // Example message (integer)

    cout << "Public Key: (" << keys.first.first << ", " << keys.first.second << ")"<<endl;;
    cout << "Private Key: " << keys.second << endl;

    auto ciphertext = encrypt(message, keys.first);
    cout << "Ciphertext: (" << ciphertext.first << ", " << ciphertext.second << ")"<<endl;

    int decryptedMessage = decrypt(ciphertext, keys.second, prime);
    cout << "Decrypted Message: " << decryptedMessage << endl;

    return 0;
}
