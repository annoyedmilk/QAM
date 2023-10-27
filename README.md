# QAM4 and QAM16 Modulation

## Introduction

Welcome to the QAM4 and QAM16 modulation repository, providing implementations in both C and Python. Quadrature Amplitude Modulation (QAM) conveys data by changing the amplitude of two carrier waves, typically sinusoids, which are out of phase by 90°.

## 📁 Files

### C Implementations:

- `QAM4.c`: QAM4 modulation.
- `QAM16.c`: QAM16 modulation.

### Python Implementations:

- `QAM4.py`: QAM4 modulation with visualization.
- `QAM16.py`: QAM16 modulation with visualization.

## 🌟 Features

- **Message Encoding**: Convert string messages into I (In-phase) and Q (Quadrature) components.
- **Carrier Wave Modulation**: Modulate the I and Q components onto a carrier wave.
- **Visualization (Python only)**: Visualize modulation, symbol errors, and waveforms.
- **Console Output(C only)**: View modulated values directly in the console.

## 🚀 Usage

### C Implementations:

1. Compilation:
   ```bash
   gcc QAM4.c -o QAM4 -lm
   gcc QAM16.c -o QAM16 -lm
   ```

2. Execution:
   ```bash
   ./QAM4
   ./QAM16
   ```

### Python Implementations:

1. Execution:
   ```bash
   python QAM4.py
   python QAM16.py
   ```

## 🔍 Modulation Details

- **QAM4**:
  - Process each character 2 bits at a time.
  - I and Q values: {-1, 1}

- **QAM16**:
  - Process each character 4 bits at a time.
  - I and Q values: {-3, -1, 1, 3}

## 🖼️ Example Outputs

![QAM4 Output](https://github.com/annoyedmilk/QAM/assets/77896841/341eb6e2-e702-468f-9d83-06cff69f03ac)

![QAM16 Output](https://github.com/annoyedmilk/QAM/assets/77896841/6c432ae8-b27c-449b-b4d3-1136145cbc10)

## 📚 Dependencies

### C: 
- `stdio.h`
- `string.h`
- `math.h`

### Python:
- `numpy`
- `matplotlib`

## 📜 Conclusion

This repository offers a clear and comprehensive implementation of QAM4 and QAM16 modulation schemes in both C and Python. It serves as a foundation for those looking to delve into the world of QAM or for those looking to integrate these implementations into larger projects.
