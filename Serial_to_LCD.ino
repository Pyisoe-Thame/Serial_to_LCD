/*
  Author : Pyae Sone Hein
  Date   : Feb/23/2024
*/

#include <Arduino.h>
#include <LiquidCrystal.h>

#define interval 200

// Define the LCD dimensions
const uint8_t numRows = 2;
const uint8_t numCols = 16;

// Define the LCD pins
const uint8_t rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String message = "";

void LCD_ShiftTextOnLimit( String &str);
void rmUnwantedSpace(String &str);
void rmIndex(String &str, int index);
void shiftUp(String &str, int shiftTime, bool leaveBotLine);
void printStringOnRow( String &str, int row, int delayTime);

void setup() 
{
  Serial.begin(115200);
  delay(1000);  // wait some time

  lcd.begin(numCols, numRows);
  lcd.setCursor(0, 0);
  
}

void loop() 
{
  // Sample text to display
  if( Serial.available() > 0)
  {
    message = Serial.readStringUntil('\n');
    // Serial.println(message);  // in case want to see the message before further processing
    
    // in printing style
    LCD_ShiftTextOnLimit(message);

    // in scrolling up style
    // rmUnwantedSpace(message);
    // int len = message.length();
    // int shiftTime = ( ( message.length() + numCols -1 ) / numCols) - numRows;  // calculate how many shiftTime need to print all
    // int i = 0;
/*
  shift till to see the last line of text/letter
  to make sure that the printing has ended,
  you can shift one more time to see the blank bottm row
*/
    // do
    // {
    //   shiftUp( message, i, false);
    //   delay(2000);
    //   i++;
    // }while( i < shiftTime);

    // uncomment the following 2 lines if willing to clear the LCD after 10 sec
    // delay(10000);
    // lcd.clear();
  }
}

void LCD_ShiftTextOnLimit( String &str)
{
  String tempStr = str;  // just make a copy to save string integrity
  rmUnwantedSpace(tempStr);  // prepare the string suitable for 16 column LCD
  lcd.clear();
/*
  length() doesn't include counting '\0'
  change the type of len if size of int is not big enough to hold value
  numCols - 1 added to include counting the last substring
  because the last substring could have become modulation and not get printed
*/
  int numSubStr = ( tempStr.length() + ( numCols - 1)) / numCols;
  
  for( int i = 0; i < numRows; i++)  // until it reaches the readable row limit
  {
    String substring = tempStr.substring(i * numCols, (i + 1) * numCols);
    Serial.println(substring);
    printStringOnRow( substring, i, interval);
  }
  if( numSubStr > numRows)
  {
    int shiftTime = 1;  // shifting has to begin
    for( int i = numRows; i < numSubStr; i++) 
    {
      delay(interval);  // put interval also before shifting
      shiftUp( tempStr, shiftTime, true);  // start shifting
      String substring = tempStr.substring(i * numCols, (i + 1) * numCols);
      // Serial.println(substring);  // uncomment this line to see also on Serial Monitor
      printStringOnRow( substring, numRows-1, interval);
      shiftTime++;  // waiting for the next shifting
    }
  }
}

void rmUnwantedSpace(String &str) 
{
  int length = str.length();  

  checkAgain:  // check again if string is changed (inefficient for long string)
  for( int i = 0; i < length; i += numCols)  // for all char where index % 16 == 0
  {
    if( str[i] == ' ')  // check if the char at 0 column is a space
    {  
      rmIndex( str, i);  // Remove the space character
      length--;
      goto checkAgain;
    }
  }
  return ;
}

void rmIndex(String &str, int index) 
{
  do
  {
    str[index] = str[index + 1];
    index++;
  } while( str[index] != '\0');
  str.remove( str.length() - 1);  // resize the string (reduce by 1 char)
}

void shiftUp(String &str, int shiftTime, bool leaveBotLine)
{
  lcd.clear();
  int printingRows = 0;
  if( !leaveBotLine)  // check if request to leave the bottom row for some printing performance
    printingRows = numRows;
  else
    printingRows = numRows-1;

  for( int row = 0; row < printingRows; row++)  // for all rows
  {
    lcd.setCursor( 0, row);  // change line

    // this is another solution
    // String substring = str.substring( ( row + shiftTime) * numCols, ( row + shiftTime + 1) * numCols);
    // printStringOnRow( substring, row, 0);

    for( int i = 0; i < numCols; i++)
    {
      if( str[ i + ( (row + shiftTime) * numCols)] == '\0')
        break;  // added because LCD  was printing the null characters too
      lcd.print( str[ i + ( (row + shiftTime) * numCols)]);  // print depending on row and shift time on each column
    }
  }
}

void printStringOnRow( String &str, int row, int delayTime) 
{
  lcd.setCursor( 0, row); // Set cursor to the beginning of the specified row
  for( int i = 0; i < str.length(); i++) 
  {
    lcd.print(str[i]); // Print the current character
    delay(delayTime);  // Wait for a short time
  }
}
