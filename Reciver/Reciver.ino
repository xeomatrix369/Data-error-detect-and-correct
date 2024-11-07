#include <LiquidCrystal.h>
#include "hamming_dec.h"
// Pin assignments
#define RX_CLOCK 2
#define RX_DATA 3
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7
#define LCD_RS 8
#define LCD_EN 9

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

char message[16];
int en_msg[12];
int decodedData;
volatile byte rx_byte = 0;
volatile int bit_position = 0;
volatile bool update_lcd = true;

void setup() {
  Serial.begin(9600);
  pinMode(RX_DATA, INPUT);
  strcpy(message, "");
  lcd.begin(16, 2);
  attachInterrupt(digitalPinToInterrupt(RX_CLOCK), onClockPulse, RISING);
}

void onClockPulse() {
  bool rx_bit = digitalRead(RX_DATA);

  if (bit_position == 12) {
    rx_byte = 0;
    bit_position = 0;
  }
  
  if (rx_bit) {
//    rx_byte |= (0x80 >> bit_position);/
    en_msg[bit_position]=1;
  }

  bit_position += 1;

  if (bit_position == 12) {
    decodedData=0;
    decodedData=decode_hamming(en_msg);
    uint8_t rx_byte = (uint8_t)decodedData;
    strncat(message, (const char *)&rx_byte, 1);
    memset(en_msg, 0, sizeof(en_msg));
  }
  
  update_lcd = true;
}
void loop() {
  if (update_lcd) {
    update_lcd = false;
    
    lcd.noCursor();
    lcd.setCursor(0, 0);
    lcd.print(message);
    lcd.setCursor(0, 1);
    for (int i = 0; i < 12; i += 1) {
      Serial.print(en_msg[i]);
      if (i < bit_position) {
//        lcd.print(rx_byte & (0x80 >> i) ? "1" : "0");/
        lcd.print(en_msg[i]? "1" : "0");
      } else {
        lcd.print(" ");
      }
    }
    Serial.println();
    lcd.setCursor(strlen(message), 0);
    lcd.cursor();
  }
}
