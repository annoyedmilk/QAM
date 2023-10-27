import numpy as np
import matplotlib.pyplot as plt

MAX_MESSAGE_LENGTH = 256
MAX_BINARY_LENGTH = MAX_MESSAGE_LENGTH * 8
SAMPLES_PER_SYMBOL = 20

def text_to_binary(text):
    binary = ''.join(format(ord(char), '08b') for char in text)
    return binary

def qam_modulate(binary_message, carrier_frequency, symbol_duration, sampling_rate):
    t = np.linspace(0, symbol_duration, SAMPLES_PER_SYMBOL)
    modulated_signal = np.zeros(len(binary_message) // 2 * SAMPLES_PER_SYMBOL)
    
    for i in range(0, len(binary_message), 2):
        symbol = binary_message[i:i+2]
        if symbol == "00": 
            symbol_value = complex(1, 1)
        elif symbol == "01":
            symbol_value = complex(1, -1)
        elif symbol == "10":
            symbol_value = complex(-1, 1)
        elif symbol == "11":
            symbol_value = complex(-1, -1)
        
        for j in range(SAMPLES_PER_SYMBOL):
            carrier_i = np.cos(2 * np.pi * carrier_frequency * t[j])
            carrier_q = np.sin(2 * np.pi * carrier_frequency * t[j])
            modulated_signal[i // 2 * SAMPLES_PER_SYMBOL + j] = symbol_value.real * carrier_i + symbol_value.imag * carrier_q
            
    return modulated_signal

def main():
    message = input("Enter the message you'd like to modulate: ")
    binary_message = text_to_binary(message)
    
    carrier_frequency = 1.0
    symbol_duration = 1.0
    sampling_rate = SAMPLES_PER_SYMBOL

    modulated_signal = qam_modulate(binary_message, carrier_frequency, symbol_duration, sampling_rate)

    # Plot the modulated signal
    plt.plot(modulated_signal)
    plt.xlabel('Sample Index')
    plt.ylabel('Amplitude')
    plt.title('QAM Modulated Signal')
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    main()