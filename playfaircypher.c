#include <stdio.h>
#include <string.h>

char alphabet_list[] = "abcdefghiklmnopqrstuvwxyz";  // (j is omitted)

void key_matrix(char *key, char matrix[5][5]) {
    char used[26] = {0};
    int i, index = 0;

    for (i = 0; key[i] != '\0'; i++) {
        if (!used[key[i] - 'a']) {
            used[key[i] - 'a'] = 1;
            matrix[index / 5][index % 5] = key[i];
            index++;
        }
    }

    for (i = 0; alphabet_list[i] != '\0'; i++) {
        if (!used[alphabet_list[i] - 'a']) {
            used[alphabet_list[i] - 'a'] = 1;
            matrix[index / 5][index % 5] = alphabet_list[i];
            index++;
        }
    }
}

void search_element(char matrix[5][5], char element, int *row, int *col) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == element) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encrypt_playfair_cipher(char matrix[5][5], char *plaintext, char *ciphertext) {
    int len = strlen(plaintext);
    int i, row1, col1, row2, col2;

    for (i = 0; i < len; i += 2) {
        search_element(matrix, plaintext[i], &row1, &col1);
        search_element(matrix, plaintext[i + 1], &row2, &col2);

        if (row1 == row2) {
            ciphertext[i] = matrix[row1][(col1 + 1) % 5];
            ciphertext[i + 1] = matrix[row2][(col2 + 1) % 5];
        } else if (col1 == col2) {
            ciphertext[i] = matrix[(row1 + 1) % 5][col1];
            ciphertext[i + 1] = matrix[(row2 + 1) % 5][col2];
        } else {
            ciphertext[i] = matrix[row1][col2];
            ciphertext[i + 1] = matrix[row2][col1];
        }
    }
    ciphertext[len] = '\0';
}

// ---------------- DECRYPTION ----------------
void decrypt_playfair_cipher(char matrix[5][5], char *ciphertext, char *plaintext) {
    int len = strlen(ciphertext);
    int i, row1, col1, row2, col2;

    for (i = 0; i < len; i += 2) {
        search_element(matrix, ciphertext[i], &row1, &col1);
        search_element(matrix, ciphertext[i + 1], &row2, &col2);

        if (row1 == row2) {
            plaintext[i] = matrix[row1][(col1 + 4) % 5];  // move LEFT instead of right
            plaintext[i + 1] = matrix[row2][(col2 + 4) % 5];
        } else if (col1 == col2) {
            plaintext[i] = matrix[(row1 + 4) % 5][col1];  // move UP instead of down
            plaintext[i + 1] = matrix[(row2 + 4) % 5][col2];
        } else {
            plaintext[i] = matrix[row1][col2];
            plaintext[i + 1] = matrix[row2][col1];
        }
    }
    plaintext[len] = '\0';
}

int main() {
    char plaintext[] = "krishnarathore";   // original message
    char key[] = "crypto";
    char ciphertext[50], decrypted[50];
    char matrix[5][5];

    key_matrix(key, matrix);

    encrypt_playfair_cipher(matrix, plaintext, ciphertext);
    decrypt_playfair_cipher(matrix, ciphertext, decrypted);

    printf("The Key text: %s\n", key);
    printf("The Plain Text: %s\n", plaintext);
    printf("The CipherText: %s\n", ciphertext);
    printf("The Decrypted Text: %s\n", decrypted);

    return 0;
}
