# Error Detection and Correction System with Hamming Code

## Project Overview
This project implements error detection and correction using the Hamming Code algorithm in Embedded C to ensure reliable data transmission over UART. The system is further enhanced by integrating a PS/2 Keyboard for real-time user input and interfacing transmitter and receiver modules using the I2C communication protocol.

Key features include:
- **Hamming Code Implementation**: Encoding on the transmitter (Tx) side and decoding with error correction on the receiver (Rx) side.
- **UART Communication**: Reliable data transmission between components.
- **PS/2 Keyboard Integration**: Seamless real-time input from the user.
- **I2C Protocol**: Effective communication between the transmitter and receiver.

## Features
- **Error Detection and Correction**: Developed and implemented Hamming Code to detect and correct single-bit errors during data transmission.
- **PS/2 Keyboard Interfacing**: Enabled real-time data entry for the system using a PS/2 keyboard.
- **Reliable Communication**: Ensured robust data transfer by combining UART and I2C protocols.

## System Architecture
1. **PS/2 Keyboard Input**:
   - The keyboard is interfaced with the microcontroller to provide real-time data input.
   - Data from the keyboard is processed and prepared for transmission.

2. **Data Transmission**:
   - Data is encoded using Hamming Code on the transmitter side to add error detection and correction capabilities.
   - Encoded data is sent over I2C communication protocol to the receiver.

3. **Data Reception**:
   - The receiver decodes the Hamming-encoded data, identifies errors (if any), and corrects them.
   - Decoded data is output for further use.

## Tools and Technologies
- **Language**: Embedded C
- **Communication Protocols**: UART and I2C
- **Microcontroller Integration**: PS/2 keyboard interfacing and communication between Tx and Rx
- **Error Handling**: Hamming Code for robust error management

## How to Run
1. Clone this repository:
   ```bash
   git clone https://github.com/xeomatrix/Data-error-detect-and-correct.git
   ```
2. Open the project files in your preferred Embedded C IDE (e.g.,arduino ide Keil, MPLAB, or STM32CubeIDE).
3. Compile and upload the code to your microcontroller using ardhino frame work.
4. Connect the PS/2 keyboard and verify the UART and I2C communication setup.
5. Run the system and monitor the output for error detection and correction in real-time.

## Project Directory Structure
```
├── src
│   ├── Reciver.c        # Hamming Code encoding and decoding implementation
│   ├── Transmitter.c   # I2C protocol implementation
│   └── Tx_ps2_keyboard.c         # PS/2 keyboard interface driver
```

## Future Enhancements
- Extend support for multi-bit error detection and correction.
- Add support for additional input devices.
- Enhance error correction algorithms for faster performance.

## License
This project is licensed under the [MIT License](LICENSE).

## Contact
For any queries or contributions, feel free to contact:
- **Name**: Mohammed Hamza
- **Email**: mohammedhamza6174@gmail.com

---
Thank you for exploring this project! Contributions are welcome.

