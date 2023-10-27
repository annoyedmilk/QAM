#include <stdio.h>
#include <math.h>
#include <string.h>
#include <complex.h>

#define MAX_MESSAGE_LENGTH 256
#define MAX_BINARY_LENGTH (MAX_MESSAGE_LENGTH * 8)
#define SAMPLES_PER_SYMBOL 20

void text_to_binary(const char* text, char* binary) {
    for (int i = 0; i < strlen(text); i++) {
        char byte = text[i];
        for (int j = 7; j >= 0; j--) {
            binary[i * 8 + (7 - j)] = (byte & (1 << j)) ? '1' : '0';
        }
    }
    binary[strlen(text) * 8] = '\0';  // Null-terminate the binary string
}

double complex get_qam16_symbol(const char* symbol) {
    if (strcmp(symbol, "0000") == 0) return -3 - 3*I;
    if (strcmp(symbol, "0001") == 0) return -3 - 1*I;
    if (strcmp(symbol, "0010") == 0) return -3 + 3*I;
    if (strcmp(symbol, "0011") == 0) return -3 + 1*I;
    if (strcmp(symbol, "0100") == 0) return -1 - 3*I;
    if (strcmp(symbol, "0101") == 0) return -1 - 1*I;
    if (strcmp(symbol, "0110") == 0) return -1 + 3*I;
    if (strcmp(symbol, "0111") == 0) return -1 + 1*I;
    if (strcmp(symbol, "1000") == 0) return  3 - 3*I;
    if (strcmp(symbol, "1001") == 0) return  3 - 1*I;
    if (strcmp(symbol, "1010") == 0) return  3 + 3*I;
    if (strcmp(symbol, "1011") == 0) return  3 + 1*I;
    if (strcmp(symbol, "1100") == 0) return  1 - 3*I;
    if (strcmp(symbol, "1101") == 0) return  1 - 1*I;
    if (strcmp(symbol, "1110") == 0) return  1 + 3*I;
    if (strcmp(symbol, "1111") == 0) return  1 + 1*I;
    return 0;  // Error case (shouldn't happen)
}

void qam16_modulate(const char* binary_message, double carrier_frequency, double symbol_duration, int sampling_rate, double* modulated_signal) {
    double t[SAMPLES_PER_SYMBOL];
    for (int i = 0; i < SAMPLES_PER_SYMBOL; i++) {
        t[i] = i * (symbol_duration / sampling_rate);
    }

    int signal_index = 0;
    for (int i = 0; i < strlen(binary_message); i += 4) {
        char symbol[5] = {binary_message[i], binary_message[i+1], binary_message[i+2], binary_message[i+3], '\0'};
        double complex symbol_value = get_qam16_symbol(symbol);
        
        for (int j = 0; j < SAMPLES_PER_SYMBOL; j++) {
            double carrier_i = cos(2 * M_PI * carrier_frequency * t[j]);
            double carrier_q = sin(2 * M_PI * carrier_frequency * t[j]);
            modulated_signal[signal_index] = creal(symbol_value) * carrier_i + cimag(symbol_value) * carrier_q;
            signal_index++;
        }
    }
}

int main() {
    char message[MAX_MESSAGE_LENGTH];
    printf("Enter the message you'd like to modulate: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0;  // Remove trailing newline

    char binary_message[MAX_BINARY_LENGTH];
    text_to_binary(message, binary_message);

    double carrier_frequency = 1.0;
    double symbol_duration = 1.0;
    int sampling_rate = SAMPLES_PER_SYMBOL;

    double modulated_signal[strlen(binary_message) / 4 * SAMPLES_PER_SYMBOL];
    qam16_modulate(binary_message, carrier_frequency, symbol_duration, sampling_rate, modulated_signal);

    for (int i = 0; i < strlen(binary_message) / 4 * SAMPLES_PER_SYMBOL; i++) {
        printf("%f\n", modulated_signal[i]);
    }
    printf("\n");

    return 0;
}