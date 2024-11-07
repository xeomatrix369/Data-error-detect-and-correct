int decode_hamming(int en_msg[]){
  int P1 = (en_msg[11]) & 1;
  int P2 = (en_msg[10]) & 1;
  int D1 = (en_msg[9]) & 1;
  int P4 = (en_msg[8]) & 1;
  int D2 = (en_msg[7]) & 1;
  int D3 = (en_msg[6]) & 1;
  int D4 = (en_msg[5]) & 1;
  int P8 = (en_msg[4]) & 1;
  int D5 = (en_msg[3]) & 1;
  int D6 = (en_msg[2]) & 1;
  int D7 = (en_msg[1]) & 1;
  int D8 = (en_msg[0]) & 1; 
   // Calculate the syndrome bits
   // injecting error
  D8^=1;
  int C1 = P1 ^ D1 ^ D2 ^ D4 ^ D5 ^ D7;
  int C2 = P2 ^ D1 ^ D3 ^ D4 ^ D6 ^ D7;
  int C4 = P4 ^ D2 ^ D3 ^ D4 ^ D8;
  int C8 = P8 ^ D5 ^ D6 ^ D7 ^ D8;
  int errorPos = (C8 << 3) | (C4 << 2) | (C2 << 1) | C1;
  if (errorPos != 0) {
    Serial.println("error at");
    Serial.println(errorPos);
//    received ^= (1 << (errorPos - 1));
    en_msg[errorPos-1]^=1;
  }
  else{
    Serial.println("no error");
  }
  P1 = (en_msg[11]) & 1;
  P2 = (en_msg[10]) & 1;
  D1 = (en_msg[9]) & 1;
  P4 = (en_msg[8]) & 1;
  D2 = (en_msg[7]) & 1;
  D3 = (en_msg[6]) & 1;
  D4 = (en_msg[5]) & 1;
  P8 = (en_msg[4]) & 1;
  D5 = (en_msg[3]) & 1;
  D6 = (en_msg[2]) & 1;
  D7 = (en_msg[1]) & 1;
  D8 = (en_msg[0]) & 1;
  
  // Extract the original 8 data bits
  int decodedData = (D1 << 0) | (D2 << 1) | (D3 << 2) | (D4 << 3) | (D5 << 4) | (D6 << 5) | (D7 << 6) | (D8 << 7);
  
  return decodedData;
}
