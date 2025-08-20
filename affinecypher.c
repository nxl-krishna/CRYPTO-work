#include <stdio.h>

int mod_inverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    // Extended Euclidean Algorithm
    while (a > 1) {
        q = a / m;
        t = m;

        m = a % m;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

int main() {
    int size;
    scanf("%d", &size); // Read number of characters

    int a, b;
    scanf("%d", &a);
    scanf("%d", &b);

    int x[size], c[size];
    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char input[size + 1]; // +1 for null terminator

    // Read the input string (skip spaces/newlines)
    for (int i = 0; i < size; i++) {
        scanf(" %c", &input[i]); // " %c" skips whitespace
    }
    input[size] = '\0';

    // Convert each letter to its alphabet index
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 26; j++) {
            if (input[i] == alphabet[j]) {
                x[i] = j;
                break;
            }
        }
    }

    // Encryption: E(x) = (a*x + b) % 26
    for (int i = 0; i < size; i++) {
        c[i] = (a * x[i] + b) % 26;
    }

    printf("Encrypted: ");
    for (int i = 0; i < size; i++) {
        printf("%c", alphabet[c[i]]);
    }
    printf("\n");

    // Find modular inverse of a
    int a_inverse = mod_inverse(a, 26);

    // Decryption: D(x) = a_inv * (y - b) % 26
    int y[size];
    for (int i = 0; i < size; i++) {
        y[i] = (a_inverse * (c[i] - b + 26)) % 26; // +26 to avoid negative
    }

    printf("Decrypted: ");
    for (int i = 0; i < size; i++) {
        printf("%c", alphabet[y[i]]);
    }
    printf("\n");

    return 0;
}
