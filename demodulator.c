// demodulator.c
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

const float carrierFrequency = 1.0;
const int sync_sequence[] = {1, 1, -1, -1, 1, -1, 1, -1};
const int sync_length = sizeof(sync_sequence) / sizeof(sync_sequence[0]);

#define FILTER_SIZE 5
float filter[FILTER_SIZE] = {0};

float moving_average_filter(float input) {
    float sum = 0;
    for (int i = 0; i < FILTER_SIZE - 1; i++) {
        filter[i] = filter[i + 1];
        sum += filter[i];
    }
    filter[FILTER_SIZE - 1] = input;
    sum += input;
    return sum / FILTER_SIZE;
}

bool detect_sync(int *received, int length) {
    // ... [same as before] ...
}

void demodulate(float *received, int length, char *demodulated_message) {
    // ... [same as before, but with filtering] ...

    for (int i = 0; i < length; i++) {
        received[i] = moving_average_filter(received[i]);
    }

    // ... [rest of the demodulation] ...
}

int main() {
    FILE *file = fopen("modulated_signal.txt", "r");
    float received[10000];  // Assuming a max size
    int index = 0;

    while (fscanf(file, "%f", &received[index]) != EOF) {
        index++;
    }
    fclose(file);

    char demodulated_message[100];
    demodulate(received, index, demodulated_message);

    printf("Demodulated Message: %s\n", demodulated_message);

    return 0;
}
