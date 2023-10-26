# QAM4 and QAM16 Modulation README

## Introduction

This README provides an overview of the QAM4 and QAM16 modulation code. Quadrature Amplitude Modulation (QAM) is a modulation scheme that conveys data by changing the amplitude of two carrier waves. These carrier waves, usually sinusoids, are out of phase with each other by 90°.

## Files

1. `QAM4.c`: This file contains the code for QAM4 modulation.
2. `QAM16.c`: This file contains the code for QAM16 modulation.

## Features

- **Message Encoding**: The code takes a string message and encodes it into a sequence of I (In-phase) and Q (Quadrature) components based on the QAM scheme.
  
- **Carrier Wave Modulation**: The I and Q components are then modulated onto a carrier wave, generating the final modulated signal.

- **Console Output**: The modulated values are printed to the console for visualization or further processing.

## Usage

1. **Compilation**:
   ```bash
   gcc QAM4.c -o QAM4 -lm
   gcc QAM16.c -o QAM16 -lm
   ```

2. **Execution**:
   ```bash
   ./QAM4
   ./QAM16
   ```

3. The modulated values will be printed to the console.

## Modulation Details

- **QAM4**:
  - Each character in the message is processed 2 bits at a time.
  - The I and Q components can take values from the set {-1, 1}.

- **QAM16**:
  - Each character in the message is processed 4 bits at a time.
  - The I and Q components can take values from the set {-3, -1, 1, 3}.

## Example Outputs
QAM4 Output
![QAM4](https://github.com/annoyedmilk/QAM/assets/77896841/fbe9447f-1bef-4fb3-a4f0-434d57e44621)

QAM16 Output
![QAM16](https://github.com/annoyedmilk/QAM/assets/77896841/5638a2eb-b877-4b09-8ad9-1fa96bfd9b12)

## Dependencies

- Standard C libraries: `stdio.h`, `string.h`, and `math.h`.

## Conclusion

This code provides a simple implementation of QAM4 and QAM16 modulation schemes. It's useful for understanding the basics of QAM and can be expanded or integrated into larger communication system simulations or projects.
