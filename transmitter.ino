#include <LiquidCrystal.h>
#define TX_RATE 5
#define TX_DATA 3
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7
#define LCD_RS 8
#define LCD_EN 9
const char *message  = "Hello, World!";

void setup() {
  pinMode(TX_DATA, OUTPUT);
  //initialize lcd
  LiquidCrystal lcd(LCD_RS,LCD_EN,LCD_D4,LCD_D5,LCD_D6,LCD_D7);
  lcd.begin(16,2);
  lcd.setCursor(0, 0);
  lcd.print(message);

  for (int byte_idx=0; byte_idx < strlen(message); byte_idx++)
  {
    char tx_byte = message[byte_idx];

    //clear the second line of display
    lcd.noCursor();
    lcd.setCursor(0, 1);
    lcd.print("        ");
    lcd.setCursor(byte_idx,0);
    lcd.cursor();


    for(int bit_idx=0; bit_idx<8; bit_idx++)
    {
      bool tx_bit = tx_byte & (0x80>>bit_idx);
      digitalWrite(TX_DATA, tx_bit);

      //Update the LCD
      lcd.noCursor();
      lcd.setCursor(bit_idx, 1);
      lcd.print(tx_bit ?"1":"0");
      lcd.setCursor(byte_idx, 0);
      lcd.cursor();

      delay(1000/TX_RATE);  
    }
  }
  digitalWrite(TX_DATA,LOW);

}

void loop() {
  // put your main code here, to run repeatedly:

}
