int encode_hamming(int msg[]) {
    // Extract individual data bits
    int D1 = (msg[0]) & 1;
    int D2 = (msg[1]) & 1;
    int D3 = (msg[2]) & 1;
    int D4 = (msg[3]) & 1;
    int D5 = (msg[4]) & 1;
    int D6 = (msg[5]) & 1;
    int D7 = (msg[6]) & 1;
    int D8 = (msg[7]) & 1;

    // Calculate parity bits
    int P1 = D1 ^ D2 ^ D4 ^ D5 ^ D7;
    int P2 = D1 ^ D3 ^ D4 ^ D6 ^ D7;
    int P4 = D2 ^ D3 ^ D4 ^ D8;
    int P8 = D5 ^ D6 ^ D7 ^ D8;

    // Combine parity and data bits into a 12-bit code
    uint16_t hammingCode = (P1 << 0) | (P2 << 1) | (D1 << 2) | (P4 << 3) |
                           (D2 << 4) | (D3 << 5) | (D4 << 6) | (P8 << 7) |
                           (D5 << 8) | (D6 << 9) | (D7 << 10) | (D8 << 11);

    return hammingCode;
}
