
#include <LiquidCrystal.h>
#include "hamming_enc.h"
#define TX_RATE 0.005
#define TX_DATA 3
#define TX_CONV 10
#define TX_CLOCK 2
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7
#define LCD_RS 8
#define LCD_EN 9
//const char *message  = "Hi";
int hamm[12];
char letter;


// Lookup table (in: SHIFT state and PS2 scancode => out: desired ASCII code) change for your country
// QWERTZ layout
char ScancodeToASCII[2][128] = {
  { 0,0,0,0,0,0,0,0,         0,0,0,0,0,9,94,0,         0,0,0,0,0,113,49,0,       0,0,121,115,97,119,50,0,    // w/o SHIFT or ALT(GR)
    0,99,120,100,101,52,51,0,0,32,118,102,116,114,53,0,0,110,98,104,103,122,54,0,0,0,109,106,117,55,56,0,
    0,44,107,105,111,48,57,0,0,46,45,108,148,112,0,0,  0,0,132,0,129,96,0,0,     0,0,10,43,0,35,0,0,
    0,60,0,0,0,0,8,0,        0,0,0,0,0,0,0,0,          0,0,0,0,0,0,27,0,         0,0,0,0,0,0,0,0  },
  { 0,0,0,0,0,0,0,0,         0,0,0,0,0,0,248,0,        0,0,0,0,0,81,33,0,        0,0,89,83,65,87,34,0,       // with SHIFT
    0,67,88,68,69,36,0,0,    0,0,86,70,84,82,37,0,     0,78,66,72,71,90,38,0,    0,0,77,74,85,47,40,0,
    0,59,75,73,79,61,41,0,   0,58,95,76,153,80,63,0,   0,0,142,0,154,0,0,0,      0,0,0,42,0,39,0,0,
    0,62,0,0,0,0,0,0,        0,0,0,0,0,0,0,0,          0,0,0,0,0,0,0,0,          0,0,0,0,0,0,0,0  } };

// QWERTY layout
/*
char ScancodeToASCII[2][128] = {
  { 0,0,0,0,0,27,27,0,         0,0,0,0,0,9,96,0,         0,0,0,0,0,113,49,0,       0,0,122,115,97,119,50,0,    // w/o SHIFT or ALT(GR)
    0,99,120,100,101,52,51,0,0,32,118,102,116,114,53,0,0,110,98,104,103,121,54,0,0,0,109,106,117,55,56,0,
    0,44,107,105,111,48,57,0,0,46,47,108,59,112,45,0,  0,0,39,0,91,61,0,0,     0,0,10,93,0,124,0,0,
    0,60,0,0,0,0,8,0,        0,49,0,52,55,0,0,0,          0,46,50,53,54,56,27,0,         0,43,51,45,42,57,0,0  },
  { 0,0,0,0,0,0,0,0,         0,0,0,0,0,0,126,0,        0,0,0,0,0,81,33,0,        0,0,90,83,65,87,64,35,       // with SHIFT
    0,67,88,68,69,36,35,0,    0,32,86,70,84,82,37,0,     0,78,66,72,71,89,94,0,    0,0,77,74,85,38,42,0,
    0,60,75,73,79,41,40,0,   0,62,63,76,58,80,95,0,   0,0,34,0,123,43,0,0,      0,0,0,125,0,92,0,0,
    0,62,0,0,0,0,0,0,        0,0,0,0,0,0,0,0,          0,0,0,0,0,0,0,0,          0,0,0,0,0,0,0,0  } };
*/

void blink_green()
{
  digitalWrite(TX_CONV,LOW);
  delay(500);
  digitalWrite(TX_CONV,HIGH);
  delay(500);
  digitalWrite(TX_CONV,LOW);
  delay(500);
  digitalWrite(TX_CONV,HIGH);
  delay(500);
  digitalWrite(TX_CONV,LOW);
  delay(500);
  digitalWrite(TX_CONV,HIGH);
  delay(500);
  digitalWrite(TX_CONV,LOW);


}
void Hamm_conv(int tx_data[8])
{ 
  int parity[4];
  int i=0;
  int j=0;
  int c=0;
  
     
  parity[0]=tx_data[0]^tx_data[1]^tx_data[3]^tx_data[4]^tx_data[6];
  parity[1]=tx_data[0]^tx_data[2]^tx_data[3]^tx_data[5]^tx_data[6];
  parity[2]=tx_data[1]^tx_data[2]^tx_data[3]^tx_data[7];
  parity[3]=tx_data[4]^tx_data[5]^tx_data[6]^tx_data[7];


  while(i<12)
  {
    if(i==0||i==1||i==3||i==7)
    { hamm[i] = parity[j];
      j++;
      i++;
    }
    else{
      hamm[i]=tx_data[c];
      c++;
      i++;
    }
  
  }
    
      
}
void setup()
{
  
  noInterrupts();
    PCICR = 0b00000010;   // enable Port C pin change interrupt PCI "PCINT1"
    PCMSK1 = 0b00010000;  // unmask Pin A4 pin change interrupt PCI
  interrupts();
  Serial.begin(9600);
   int data_byte[8];
  

  pinMode(TX_DATA, OUTPUT);
  pinMode(TX_CONV, OUTPUT);
  pinMode(TX_CLOCK, OUTPUT);
  
  
}

void loop() {}

ISR(PCINT1_vect)      // interrupt service routine
{
  int val = 0;
  for(int i=0; i<11; i++)
  {
    while(bitRead(PINC, 4) == true);
    val |= bitRead(PINC, 3)<<i;
    while(bitRead(PINC, 4) == false);    
  }
  val = (val>>1) & 255;

  static bool shiftIsActive = false;      // state of the SHIFT key
  static bool nextIsReleased = false;     // indicating that the next key was released

  switch (val)
  {
    case 18: case 89: shiftIsActive = !nextIsReleased; nextIsReleased = false; break;  // SHIFT LEFT, SHIFT RIGHT     
    case 240: nextIsReleased = true; break;                                            // key release indicator      
    default:                                                                           // any other key
      if (!nextIsReleased)                // is it a 'key pressed' event?
      {
        letter=ScancodeToASCII[shiftIsActive][val & 127];
        Serial.print(letter);                       // do lookup raw -> ASCII
        LiquidCrystal lcd(LCD_RS,LCD_EN,LCD_D4,LCD_D5,LCD_D6,LCD_D7);
        lcd.begin(16,2);
        lcd.setCursor(0,0);
        lcd.print("                    ");
    
       lcd.setCursor(0, 0);
       lcd.print(letter);
       char tx_byte = letter;
       int data_byte[8];
       for(int bit_idx=0; bit_idx<8; bit_idx++)
       { //build up data
         bool tx_bit = tx_byte & (0x80>>bit_idx);
         //store the data in the array
         if(tx_bit)
         {
           data_byte[7-bit_idx]=1;
         }
         else {
           data_byte[7-bit_idx]=0;
         }
         
          
         digitalWrite(TX_DATA, tx_bit);
         delay((1000/TX_RATE)/5);
    
         //Update the LCD
         lcd.noCursor();
         lcd.setCursor(bit_idx, 1);
         lcd.print(tx_bit ?"1":"0");
         lcd.cursor();
         //pulse the clock
//         digitalWrite(TX_CLOCK, HIGH);
//         delay((1000/TX_RATE)/5);
//         digitalWrite(TX_CLOCK, LOW);
         
       }
          delay(300000);      
         Hamm_conv(data_byte);

         lcd.setCursor(0, 1);
         lcd.print("                    ");
         lcd.noCursor();
         //show hamm generated
         lcd.setCursor(0, 0);
         lcd.print("                    ");
         lcd.setCursor(0, 0);
         lcd.print("Hamming code "+String(tx_byte));
         for(int k=11;k>=0;k--)
         { bool hann_bit;
      
          lcd.setCursor((11-k),1);
            //load hamming code
            if(hamm[k]==1){
              lcd.print("1");
              hann_bit=1;        
              }
            else if(hamm[k]==0){
              lcd.print("0");
              hann_bit=0;        
              }
            
            digitalWrite(TX_CONV, hann_bit);
      
            digitalWrite(TX_DATA,LOW);
      
            delay((1000/TX_RATE)/5);
            digitalWrite(TX_CLOCK, HIGH);
            delay((1000/TX_RATE)/5);
            digitalWrite(TX_CLOCK, LOW);  
          
          }
          digitalWrite(TX_CONV, LOW);
       }
       
      nextIsReleased = false;
      break;
  }
  PCIFR = 0x02;                           // clears the PCI flag 1
}
