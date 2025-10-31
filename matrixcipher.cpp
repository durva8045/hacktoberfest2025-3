// 🌌 Hacktoberfest 2025 Exclusive Project 🌌
// Project: The Matrix Cipher 🔐

// Description: Encrypts and decrypts text using 3x3 matrix-based modular transformations.
// Difficulty: Advanced (Matrix algebra + modular inverse)

#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

// Matrix size (3x3)
const int N = 3;
const int MOD = 26;

// Function to multiply matrix with vector (mod 26)
vector<int> multiplyMatrix(const vector<vector<int>>& mat, const vector<int>& vec) {
    vector<int> res(N);
    for (int i = 0; i < N; ++i) {
        res[i] = 0;
        for (int j = 0; j < N; ++j)
            res[i] += mat[i][j] * vec[j];
        res[i] %= MOD;
    }
    return res;
}

// Modular inverse (for determinant)
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}

// Compute determinant of 3x3 matrix
int determinant(const vector<vector<int>>& mat) {
    int det = mat[0][0]*(mat[1][1]*mat[2][2] - mat[2][1]*mat[1][2])
            - mat[0][1]*(mat[1][0]*mat[2][2] - mat[1][2]*mat[2][0])
            + mat[0][2]*(mat[1][0]*mat[2][1] - mat[1][1]*mat[2][0]);
    det = ((det % MOD) + MOD) % MOD;
    return det;
}

// Compute inverse matrix mod 26
vector<vector<int>> inverseMatrix(const vector<vector<int>>& mat) {
    int det = determinant(mat);
    int invDet = modInverse(det, MOD);
    if (invDet == -1) throw runtime_error("Matrix not invertible modulo 26");

    vector<vector<int>> inv(N, vector<int>(N));
    inv[0][0] =  (mat[1][1]*mat[2][2] - mat[2][1]*mat[1][2]);
    inv[0][1] = -(mat[0][1]*mat[2][2] - mat[2][1]*mat[0][2]);
    inv[0][2] =  (mat[0][1]*mat[1][2] - mat[1][1]*mat[0][2]);

    inv[1][0] = -(mat[1][0]*mat[2][2] - mat[2][0]*mat[1][2]);
    inv[1][1] =  (mat[0][0]*mat[2][2] - mat[2][0]*mat[0][2]);
    inv[1][2] = -(mat[0][0]*mat[1][2] - mat[1][0]*mat[0][2]);

    inv[2][0] =  (mat[1][0]*mat[2][1] - mat[2][0]*mat[1][1]);
    inv[2][1] = -(mat[0][0]*mat[2][1] - mat[2][0]*mat[0][1]);
    inv[2][2] =  (mat[0][0]*mat[1][1] - mat[1][0]*mat[0][1]);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            inv[i][j] = ((inv[i][j] * invDet) % MOD + MOD) % MOD;

    return inv;
}

// Convert text to uppercase and remove spaces
string normalize(string text) {
    string result;
    for (char c : text)
        if (isalpha(c)) result += toupper(c);
    return result;
}

// Encrypt function
string encrypt(string text, const vector<vector<int>>& key) {
    text = normalize(text);
    while (text.size() % N != 0)
        text += 'X';  // pad with X
    string result;
    for (size_t i = 0; i < text.size(); i += N) {
        vector<int> vec(N);
        for (int j = 0; j < N; j++)
            vec[j] = text[i + j] - 'A';
        auto enc = multiplyMatrix(key, vec);
        for (int x : enc)
            result += char('A' + (x % MOD));
    }
    return result;
}

// Decrypt function
string decrypt(string cipher, const vector<vector<int>>& key) {
    auto invKey = inverseMatrix(key);
    string result;
    for (size_t i = 0; i < cipher.size(); i += N) {
        vector<int> vec(N);
        for (int j = 0; j < N; j++)
            vec[j] = cipher[i + j] - 'A';
        auto dec = multiplyMatrix(invKey, vec);
        for (int x : dec)
            result += char('A' + (x % MOD));
    }
    return result;
}

int main() {
    cout << "🔐 Hacktoberfest 2025: The Matrix Cipher 🔐\n";
    cout << "------------------------------------------\n";

    vector<vector<int>> key = {
        {6, 24, 1},
        {13, 16, 10},
        {20, 17, 15}
    };

    string message;
    cout << "Enter your secret message: ";
    getline(cin, message);

    string cipher = encrypt(message, key);
    cout << "\nEncrypted Text: " << cipher << endl;

    string plain = decrypt(cipher, key);
    cout << "Decrypted Text: " << plain << endl;

    cout << "\n🧠 Encryption complete! Keep contributing to Hacktoberfest 2025! 🌟\n";
    return 0;
}
