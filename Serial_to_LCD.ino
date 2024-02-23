#include <Arduino.h>
#include <LiquidCrystal.h>

#define interval 170

// Define the LCD dimensions
const uint8_t numRows = 2;
const uint8_t numCols = 16;

// Define the LCD pins
const uint8_t rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String message = "";

void LCD_Print_Msg( String &str);
void rmSpaceatColumn0(String &str);
void removeThis(String &str, int index);

void setup() 
{
  Serial.begin(115200);
  delay(1000);  // wait some time

  lcd.begin(numCols, numRows);
  lcd.setCursor(0, 0);
  
}

void loop() {
  // Sample text to display
  if( Serial.available() > 0)
  {
    message = Serial.readStringUntil('\n');
    LCD_Print_Msg(message);
    Serial.println(message);
  }
}

void LCD_Print_Msg( String str)
{
  String tempStr = str;
  rmSpaceatColumn0(tempStr);  // prepare the string suitable for 16 column LCD
  lcd.clear();
  uint8_t len = tempStr.length() - 1;  // minus one to leave out the '\0' (we are not printing the null char)
  uint8_t pos = 0;
  uint8_t overhead = 0;
  while( pos < numCols && pos < len)  // the first row
  {
    lcd.setCursor(0, 0);
    for( int i = 0; i <= pos; i++)
      lcd.print( tempStr[i]);
    delay(interval);
    pos++;
  }
  while( len > numCols)  // if more words remained to print
  {
    len -= numCols;
    overhead += numCols;
    pos = 0;
    while( pos < numCols && pos < len)  // do the second row
    {
      lcd.setCursor( 0, 1);
      for( int i = 0; i <= pos; i++)
        lcd.print( tempStr[ i + overhead]);
      delay(interval);
      pos++;
    }
    if( len > numCols)
    {
      lcd.clear();
      pos = 0;
      while( pos < numCols && pos < len)
      {
        lcd.setCursor( 0, 0);  // shift the former second line
        for( int i = 0; i <= pos; i++)
          lcd.print( tempStr[ i + overhead]);
        pos++;
      }
    }
  }
  // delay(5000);
  // lcd.clear();
}

void rmSpaceatColumn0(String &str) 
{
  int length = str.length();
  bool removedSpace = false;

  checkAgain:  // check again if string is changed (inefficient for long string)
  for( int i = 0; i < length; i += numCols)  // for all char where index % 16 == 0
  {
    if( str[i] == ' ')  // check if the char at 0 column is a space
    {  
      removeThis( str, i);  // Remove the space character
      length--;
      goto checkAgain;
    }
  }
  return ;
}

void removeThis(String &str, int index) 
{
  do
  {
    str[index] = str[index + 1];
    index++;
  } while( str[index] != '\0');
  str.remove( str.length() - 1);  // resize the string (reduce by 1 char)
}

