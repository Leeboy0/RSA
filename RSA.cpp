
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int modPow(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

bool is_prime(int number) {
  if (number <= 1) {
    return false;
  }
  for (int i = 2; i <= sqrt(number); i++) {
    if (number % i == 0) {
      return false;
    }
  }
  return true;
}

int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // Inverse doesn't exist
}

char intToChar(int value) {
    switch(value) {
        case 31: return ' ';
        case 32: return '\"';
        case 33: return ',';
        case 34: return '.';
        case 35: return '\'';
        default: return 'A' + value - 5;  // For 5 to 30 (A to Z)
    }
}

int main() {
    int e, n, m;
    cin >> e >> n;
    cin >> m;

    int p = 0, q = 0;

    // Find prime factors of n: p and q
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            p = i;
            q = n / i;
            break;
        }
    }

    if (p <= 0 || q <= 0 || p == q) {
        cout << "Public key is not valid!";
        return 0;
    }

    if (is_prime(p) == false || is_prime(q) == false) {
        cout << "Public key is not valid!";
        return 0;
    }

    int phi_n = (p - 1) * (q - 1);
    int d = modInverse(e, phi_n);

    if (d <= 0) {
        cout << "Public key is not valid!";
        return 0;
    }

    vector<int> ciphertext(m);
    for (int i = 0; i < m; i++) {
        cin >> ciphertext[i];
        if (ciphertext[i] <= 0) {
            return 0;   
        }
    }

    cout << p << " " << q << " " << phi_n << " " << d << endl;

    for (int i = 0; i < m; i++) {
        cout << modPow(ciphertext[i], d, n) << " ";
    }
    cout << endl;

    for (int i = 0; i < m; i++) {
        char decryptedChar = intToChar(modPow(ciphertext[i], d, n));
        cout << decryptedChar;
       
    }
  

    return 0;
}