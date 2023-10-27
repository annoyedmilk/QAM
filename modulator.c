// modulator.c
#include <stdio.h>
#include <string.h>
#include <math.h>

const char message[] = "Hello World!";
const float carrierFrequency = 1.0;
const int sync_sequence[] = {1, 1, -1, -1, 1, -1, 1, -1};
const int sync_length = sizeof(sync_sequence) / sizeof(sync_sequence[0]);

int main() {
    int QAM_sequence[2 * strlen(message) * 8 + 2 * sync_length];

    int index = 0;

    // Add sync sequence
    for (int i = 0; i < sync_length; i++) {
        QAM_sequence[index++] = sync_sequence[i];
    }

    for (int i = 0; i < strlen(message); i++) {
        for (int j = 7; j >= 0; j -= 2) {
            int bit1 = (message[i] >> j) & 1;
            int bit2 = (message[i] >> (j - 1)) & 1;

            QAM_sequence[index++] = (bit1 == 0) ? 1 : -1;
            QAM_sequence[index++] = (bit2 == 0) ? 1 : -1;
        }
    }

    FILE *file = fopen("modulated_signal.txt", "w");
    for (int m = 0; m < 2 * strlen(message) * 8 + 2 * sync_length; m += 2) {
        for (float t = 0; t < 2 * M_PI; t += 0.1) {
            float S_i = QAM_sequence[m] * cos(carrierFrequency * t);
            float S_q = QAM_sequence[m + 1] * sin(carrierFrequency * t);
            float S = S_i + S_q;
            fprintf(file, "%f\n", S);
        }
    }
    fclose(file);

    return 0;
}
