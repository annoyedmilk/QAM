import numpy as np
import matplotlib.pyplot as plt

MAX_MESSAGE_LENGTH = 256
MAX_BINARY_LENGTH = MAX_MESSAGE_LENGTH * 8
SAMPLES_PER_SYMBOL = 20

def text_to_binary(text):
    binary = ''.join(format(ord(char), '08b') for char in text)
    return binary

def get_qam16_symbol(symbol):
    qam16_map = {
        '0000': complex(-3, -3),
        '0001': complex(-3, -1),
        '0010': complex(-3,  3),
        '0011': complex(-3,  1),
        '0100': complex(-1, -3),
        '0101': complex(-1, -1),
        '0110': complex(-1,  3),
        '0111': complex(-1,  1),
        '1000': complex( 3, -3),
        '1001': complex( 3, -1),
        '1010': complex( 3,  3),
        '1011': complex( 3,  1),
        '1100': complex( 1, -3),
        '1101': complex( 1, -1),
        '1110': complex( 1,  3),
        '1111': complex( 1,  1)
    }
    return qam16_map.get(symbol, complex(0, 0))

def qam16_modulate(binary_message, carrier_frequency, symbol_duration, sampling_rate):
    t = np.linspace(0, symbol_duration, SAMPLES_PER_SYMBOL)
    modulated_signal = np.zeros(len(binary_message) // 4 * SAMPLES_PER_SYMBOL)
    
    for i in range(0, len(binary_message), 4):
        symbol = binary_message[i:i+4]
        symbol_value = get_qam16_symbol(symbol)
        
        for j in range(SAMPLES_PER_SYMBOL):
            carrier_i = np.cos(2 * np.pi * carrier_frequency * t[j])
            carrier_q = np.sin(2 * np.pi * carrier_frequency * t[j])
            modulated_signal[i // 4 * SAMPLES_PER_SYMBOL + j] = symbol_value.real * carrier_i + symbol_value.imag * carrier_q
            
    return modulated_signal

def main():
    message = input("Enter the message you'd like to modulate: ")
    binary_message = text_to_binary(message)
    
    carrier_frequency = 1.0
    symbol_duration = 1.0
    sampling_rate = SAMPLES_PER_SYMBOL

    modulated_signal = qam16_modulate(binary_message, carrier_frequency, symbol_duration, sampling_rate)

    # Plot the modulated signal
    plt.plot(modulated_signal)
    plt.xlabel('Sample Index')
    plt.ylabel('Amplitude')
    plt.title('QAM16 Modulated Signal')
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    main()