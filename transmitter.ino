#include <LiquidCrystal.h>
#define TX_RATE 5
#define TX_DATA 3
#define TX_CONV 10
#define TX_CLOCK 2
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7
#define LCD_RS 8
#define LCD_EN 9
const char *message  = "Om namah Shivah";
int hamm[12];



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


void setup() {
  
  int data_byte[8];
  

  pinMode(TX_DATA, OUTPUT);
  pinMode(TX_CONV, OUTPUT);
  pinMode(TX_CLOCK, OUTPUT);
 
  

  //initialize lcd
  LiquidCrystal lcd(LCD_RS,LCD_EN,LCD_D4,LCD_D5,LCD_D6,LCD_D7);
  lcd.begin(16,2);
 
  for (int byte_idx=0; byte_idx < strlen(message); byte_idx++)
  {
    char tx_byte = message[byte_idx];
    //reinitalize screen
    lcd.setCursor(0,0);
    lcd.print("                    ");
    
    lcd.setCursor(0, 0);
    lcd.print(message);
   
    //clear the second line of display
    lcd.noCursor();
    lcd.setCursor(0, 1);
    lcd.print("                 ");
    lcd.setCursor(byte_idx,0);
    lcd.cursor();


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
      lcd.setCursor(byte_idx, 0);
      lcd.cursor();
      //pulse the clock
      digitalWrite(TX_CLOCK, HIGH);
      delay((1000/TX_RATE)/5);
      digitalWrite(TX_CLOCK, LOW);  
    }

    //Calc hamming code
    Hamm_conv(data_byte);
    //clear data txd
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
    
    }
    digitalWrite(TX_CONV, LOW);
    
    
  }
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print(message);
  lcd.setCursor(0, 1);
  lcd.print("TXd Successfully");
  digitalWrite(TX_DATA,LOW);
  blink_green();
    
}

void loop() {
  
}
