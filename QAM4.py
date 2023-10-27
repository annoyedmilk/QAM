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
    I = []
    Q = []
    
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
        
        I.append(symbol_value.real)
        Q.append(symbol_value.imag)
        
        for j in range(SAMPLES_PER_SYMBOL):
            carrier_i = np.cos(2 * np.pi * carrier_frequency * t[j])
            carrier_q = np.sin(2 * np.pi * carrier_frequency * t[j])
            modulated_signal[i // 2 * SAMPLES_PER_SYMBOL + j] = symbol_value.real * carrier_i + symbol_value.imag * carrier_q
            
    return modulated_signal, I, Q

def main():
    message = input("Enter the message you'd like to modulate: ")
    binary_message = text_to_binary(message)
    
    carrier_frequency = 1.0
    symbol_duration = 1.0
    sampling_rate = SAMPLES_PER_SYMBOL

    modulated_signal, I, Q = qam_modulate(binary_message, carrier_frequency, symbol_duration, sampling_rate)

    # Plot the modulated signal
    plt.figure(figsize=(12, 5))
    
    plt.subplot(1, 2, 1)
    plt.plot(modulated_signal)
    plt.xlabel('Sample Index')
    plt.ylabel('Amplitude')
    plt.title('QAM Modulated Signal')
    plt.grid(True)
    
    # Plot the constellation diagram
    plt.subplot(1, 2, 2)
    plt.scatter(I, Q, color='red')
    plt.xlim(-1.5, 1.5)
    plt.ylim(-1.5, 1.5)
    plt.xlabel('In-Phase (I)')
    plt.ylabel('Quadrature (Q)')
    plt.title('Constellation Diagram')
    plt.grid(True)
    plt.tight_layout()
    
    plt.show()

if __name__ == "__main__":
    main()