import numpy as np
import matplotlib.pyplot as plt

MAX_MESSAGE_LENGTH = 256
MAX_BINARY_LENGTH = MAX_MESSAGE_LENGTH * 8
SAMPLES_PER_SYMBOL = 20
carrier_frequency = 1.0
symbol_duration = 1.0
sampling_rate = SAMPLES_PER_SYMBOL
error_probability = 0.5

def text_to_binary(text):
    binary = ''.join(format(ord(char), '08b') for char in text)
    return binary

def qam_modulate(binary_message, carrier_frequency, symbol_duration, sampling_rate):
    t = np.linspace(0, symbol_duration, SAMPLES_PER_SYMBOL)
    modulated_signal = np.zeros(len(binary_message) // 2 * SAMPLES_PER_SYMBOL)
    symbols = []

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
            symbols.append(symbol_value)

    return modulated_signal, symbols

def add_noise(signal, snr_db):
    snr_linear = 10**(snr_db / 10.0)
    signal_power = np.mean(signal**2)
    noise_power = signal_power / snr_linear
    noise = np.sqrt(noise_power) * np.random.randn(len(signal))
    return signal + noise

def qam_demodulate(received_signal, carrier_frequency, symbol_duration, sampling_rate):
    t = np.linspace(0, symbol_duration, SAMPLES_PER_SYMBOL)
    demodulated_symbols = []

    for i in range(0, len(received_signal), SAMPLES_PER_SYMBOL):
        sample_chunk = received_signal[i:i+SAMPLES_PER_SYMBOL]

        i_component = np.mean(sample_chunk * np.cos(2 * np.pi * carrier_frequency * t))
        q_component = np.mean(sample_chunk * np.sin(2 * np.pi * carrier_frequency * t))

        # Making decisions on the symbols based on the sign of the samples
        if i_component > 0 and q_component > 0:
            demodulated_symbols.append(complex(1, 1))
        elif i_component > 0 and q_component < 0:
            demodulated_symbols.append(complex(1, -1))
        elif i_component < 0 and q_component > 0:
            demodulated_symbols.append(complex(-1, 1))
        else:
            demodulated_symbols.append(complex(-1, -1))

    return demodulated_symbols

def binary_to_text(binary):
    chars = [binary[i:i+8] for i in range(0, len(binary), 8)]
    return ''.join([chr(int(char, 2)) for char in chars])

def main():
    message = input("Enter the message you'd like to modulate (max {} chars): ".format(MAX_MESSAGE_LENGTH))
    message = message[:MAX_MESSAGE_LENGTH]
    binary_message = text_to_binary(message)

    original_signal, original_symbols = qam_modulate(binary_message, carrier_frequency, symbol_duration, sampling_rate)
    received_signal = add_noise(original_signal, 20)

    I_original = [symbol.real for symbol in original_symbols]
    Q_original = [symbol.imag for symbol in original_symbols]

    I_received = [symbol.real + np.random.normal(0, error_probability) for symbol in original_symbols]
    Q_received = [symbol.imag + np.random.normal(0, error_probability) for symbol in original_symbols]

    demodulated_symbols = qam_demodulate(received_signal, carrier_frequency, symbol_duration, sampling_rate)

    demodulated_binary = ""
    for symbol in demodulated_symbols:
        if symbol == complex(1, 1):
            demodulated_binary += "00"
        elif symbol == complex(1, -1):
            demodulated_binary += "01"
        elif symbol == complex(-1, 1):
            demodulated_binary += "10"
        else:
            demodulated_binary += "11"
    
    demodulated_message = binary_to_text(demodulated_binary)

    print("Original Message:", message)
    print("Demodulated Message:", demodulated_message)

    plt.figure(figsize=(12, 6))
    plt.scatter(I_original, Q_original, c='blue', marker='o', label='Original Symbols')
    plt.scatter(I_received, Q_received, c='red', marker='x', label='Received Symbols (with Noise and Error Simulation)')
    plt.xlabel('I')
    plt.ylabel('Q')
    plt.title('Original vs. Received Symbols')
    plt.grid(True)
    plt.legend()
    plt.axis('equal')
    plt.tight_layout()
    plt.show()

    plt.figure(figsize=(12, 6))
    plt.plot(original_signal, label="Original Signal")
    plt.plot(received_signal, label="Received Signal (with Noise)", linestyle='dashed')
    plt.xlabel('Sample Index')
    plt.ylabel('Amplitude')
    plt.title('Original vs. Received Signal')
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    main()