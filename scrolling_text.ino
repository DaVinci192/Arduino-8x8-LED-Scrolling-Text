#include "LedControl.h"
#include "string_convert.h"

// initializing the LED matrix object
LedControl lc=LedControl(12,10,11,1);

// different delay times can be used to adjust scroll speed of text
unsigned long delaytime1 = 500;
unsigned long delaytime2 = 50;
unsigned long delaytime3 = 250;

const int LIGHT_INTENSITY = 1;

const int DISPLAY_WIDTH = 8;

const int MAX_CHARS = 50; // This is an arbitrary value, it may be changed.
const int MAX_CHAR_LENGTH = 6;
const int MAX_DISPLAY_LENGTH = MAX_CHARS*MAX_CHAR_LENGTH;

char chars[MAX_CHARS];
byte data[MAX_DISPLAY_LENGTH];
int stringSize = 0;
String message = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // An arbitrary message

void setup() {
  lc.shutdown(0,false); // wakeup call
  lc.setIntensity(0,LIGHT_INTENSITY); // set light intensity
  lc.clearDisplay(0); // clearing the display

  // setting the "data" array to a default value
  for (int displayCol = 0; displayCol < MAX_DISPLAY_LENGTH; displayCol++)
  {
    data[displayCol] = B00000000;
  }

  // populating the "data" array used for displaying "message"
  convert_string_to_byte(message, data, chars, stringSize);
}

void displayWithScroll(const byte displayData[], int arrSize)
{
  // for loop scrolls text by incrementing the display window by 1 (ie. first 0-7, second, 1-8)
  for (int shift = 0; shift < arrSize; shift++)
  {
    int colsDisplayed = 0;
    
    // out of bounds indexing is prevented by the second condition in the for loop
    for (int displayCol = 0; displayCol < DISPLAY_WIDTH && (displayCol+shift < arrSize); displayCol++)
    {
      lc.setRow(0, displayCol, displayData[displayCol + shift]);
      colsDisplayed++;
    }
    
    int wrapCol = 0;

    // if not all 8 columns were displayed, then function returns to the start of the array, creating the "wrap" effect
    for (int displayCol = colsDisplayed; displayCol < DISPLAY_WIDTH; displayCol++)
    {
      lc.setRow(0, displayCol, displayData[wrapCol]);
      wrapCol++;
    }
    delay(100); // custom delay, can be changed to increase/decrease scroll speed of text
  }
}

void loop() 
{
    displayWithScroll(data, stringSize);
}
