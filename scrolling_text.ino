//www.elegoo.com
//2016.12.9

#include "LedControl.h"
#include "string_convert.h"

LedControl lc=LedControl(12,10,11,1);

unsigned long delaytime1 = 500;
unsigned long delaytime2 = 50;
unsigned long delaytime3 = 250;

const int LIGHT_INTENSITY = 1;
const int DISPLAY_WIDTH = 8;

const int MAX_CHARS = 50;
const int MAX_CHAR_LENGTH = 6;
const int MAX_DISPLAY_LENGTH = MAX_CHARS*MAX_CHAR_LENGTH;

byte b[12] = {B01111110,B10001000,B10001000,B10001000,B01111110,B00000000,B01111110,B10001000,B10001000,B10001000,B01111110,B00000000};

char chars[MAX_CHARS];
byte data[MAX_DISPLAY_LENGTH];
int stringSize = 0;
String message = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void setup() {
  lc.shutdown(0,false); // wakeup call
  lc.setIntensity(0,LIGHT_INTENSITY); // set light intensity
  lc.clearDisplay(0); // clearing the display
  Serial.begin(9600);

  for (int displayCol = 0; displayCol < MAX_DISPLAY_LENGTH; displayCol++)
  {
    data[displayCol] = B00010000;
  }
  
  convert_string_to_byte(message, data, chars, stringSize);
  Serial.print("\n");

  for (int i = 0; i < 8; i++)
  {
    Serial.print(data[i], BIN);
    Serial.print("\n");
  }
}

/* "Slider goes over array"
 * - first iteration: print values from indices 0 to 7
 * - second interation: print values from indices 1 to 8
 * - etc
 * - to wrap values, print from index n to the end of the array, then print the rest from the beginning such that a total of 8 values are printed
 * - one value continuously goes from 0 to 7 for the display. the other values keeps going up to the array max
 */

void displayWithScroll(const byte displayData[], int arrSize)
{

//  int width = min(arrSize, DISPLAY_WIDTH);
//  int whitespace = DISPLAY_WIDTH + (arrSize % DISPLAY_WIDTH);
//  
//  for (int displayCol = 0; displayCol < width; displayCol++)
//  {
//    lc.setRow(0, displayCol, displayData[displayCol]);
////    Serial.print(displayData[displayCol]);
////    Serial.print("\n");
//  }
//  delay(delaytime1);

//  for (int shift = 0; shift < arrSize; shift++)
//  {
//    for (int displayCol = 0; displayCol < DISPLAY_WIDTH; displayCol++)
//    {
//      int letterIndex = displayCol + shift;
//
//      if (letterIndex > (arrSize - 1))
//      {
//        shift = 0;
//        letterIndex = displayCol;
//      }
//      
//      lc.setRow(0, displayCol, displayData[displayCol + shift]);
//    }
//    delay(delaytime1);  
//  }

  for (int shift = 0; shift < arrSize; shift++)
  {
    int colsDisplayed = 0;
    for (int displayCol = 0; displayCol < DISPLAY_WIDTH && (displayCol+shift < arrSize); displayCol++)
    {
      lc.setRow(0, displayCol, displayData[displayCol + shift]);
      colsDisplayed++;
    }
    int wrapCol = 0;
    for (int displayCol = colsDisplayed; displayCol < DISPLAY_WIDTH; displayCol++)
    {
      lc.setRow(0, displayCol, displayData[wrapCol]);
      wrapCol++;
    }
    delay(delaytime3);
  }
}

void loop() {
  byte a[10]={B01111110, B00010001, B00010001, B01111110, B00000000, B01111111, B01001001, B01001001, B00110110, B00000000};
  
//  lc.setRow(0,0,a[0]);
//  lc.setRow(0,1,a[1]);
//  lc.setRow(0,2,a[2]);
//  lc.setRow(0,3,a[3]);
//  lc.setRow(0,4,a[4]);
//  delay(delaytime1);
//    displayWithScroll(a, 10);
//    displayWithScroll(b, 12);
    displayWithScroll(data, stringSize);

}
