#ifndef TEXT_H
#define TEXT_H

#include <Arduino.h>

extern LedControl lc;

extern int displayLength = 8;
extern int displayHeight = 8;

class Text
{
  private:
    int displayStringLength, rawStringLength, spacing;
    String content;
    byte displayData[50*5];
    Character letters[50];

    void populateData(String content0, int & displayLength, byte data[50*8])
    {
      int stringLength = content0.length();
      displayLength = 0;

      int lastIndex = 0;
      
      for (int letter = 0; letter < stringLength; letter++)
      {
        int charLength = 0;
        byte temp[5]; // stores info about the character - {row1, row2, row3, row4, row5}
        
        convert_letter_to_byte(content0.charAt(letter), temp, charLength);
        
        int tempIndex = 0;
        
        for (int row = 0; row < charLength; row++)
        {
          if (lastIndex + row < 50)
          {
            data[lastIndex + row] = temp[row];
            tempIndex = lastIndex + row;
            
            displayLength++;
          }
        }
        lastIndex += tempIndex;
      }
    }

    void read_string(String string0, Character letters[], byte data[], int & displaylength)
    {
      int stringLength = string0.length();
      //int stringLength = rawStringLength;
      int arrLength = stringLength+1;
      char charArray[arrLength];

      string0.toCharArray(charArray, arrLength);
      
      displayLength = 0;
      
      for (int letter = 0; letter < stringLength; letter++)
      {
        letters[letter] = Character(charArray[letter]); // populating the letters array with Character class instances
        //letters[letter] = Character(string0);
        //string0++;
        //Serial.print(string0.charAt(1));
        //letters[letter].print_char();
        
//        Serial.print(charArray[letter]);
//        Serial.print(": ");
//        Serial.print(letters[letter].get_char());
//        Serial.print(", Length: ");
//        Serial.print(letters[letter].get_length());
//        Serial.print("\n");
        
        displayLength += letters[letter].get_length();
      }

      int rowInDisplay = 0;

      for (int letter = 0; letter < stringLength; letter++) // for each letter
      {
        Character currentLetter = letters[letter];
        
//        Serial.print(currentLetter.get_char());
//        Serial.print("\n");
        
        for (int row = 0; row < currentLetter.get_length(); row++) // for each row in the letter display
        {
          data[rowInDisplay] = currentLetter.get_row(row);
          //Serial.print(data[rowInDisplay], BIN); // 100101
          //Serial.print(currentLetter.get_char());
          //Serial.print(currentLetter.get_length());
          //break;
          //Serial.print("\n");
          rowInDisplay++;
        }
        //break;
      }
      
    }

   
  public:
    Text()
    {
      displayStringLength = 0;
      content = "";
      spacing = 0;
    }

    Text(String text0)
    {
      content = text0;
      spacing = 1;
      rawStringLength = content.length();
      
      //populateData(content, displayStringLength, displayData);
      read_string(content, letters, displayData, displayLength);
      //char* string = content;
      //read_string(string, letters, displayData, displayLength);
    }

    String get_text() const
    {
      return content; 
    }

    int get_spacing() const
    {
      return spacing;
    }

    void change_text(String newText)
    {
      content = newText;
      //populateData(content, displayStringLength, displayData);
      read_string(content, letters, displayData, displayLength);
    }

    void print_row(int row) 
    {
      Serial.print(displayData[row], BIN);
    }

    void change_spacing(int spacing0)
    {
      if (spacing0 >= 0)
      {
        spacing = spacing0;
      }
    }

    void displayScrollNoWrap()
    {
      /*
      for (int scroll = 0; scroll < displayStringLength - displayLength; scroll++)
      {
        for (int row = 0; row < displayLength; row++)
        {
          int currentIndex = scroll + row;
          lc.setRow(0, currentIndex, displayData[currentIndex]);
        }
        
        delay(delaytime2);
      }*/
       lc.setRow(0,0,displayData[0]);
       lc.setRow(0,1,displayData[1]);
       lc.setRow(0,2,displayData[2]);
       lc.setRow(0,3,displayData[3]);
       //lc.setRow(0,4,displayData[4]);
    }

    void displayCharacter(int index)
    {
      //Serial.print(letters[index].get_length());
      //Serial.print("\n");
      for (int row = 0; row < letters[index].get_length(); row++)
      {
        lc.setRow(0, row, displayData[row]);
        delay(500);
      }
    }

    void testDisplay()
    {
      //Serial.print(displayData[0], BIN);
      //Serial.print("\n");
      lc.setRow(0, 0, displayData[0]);
      lc.setRow(0, 1, displayData[1]);
      lc.setRow(0, 2, displayData[2]);
      lc.setRow(0, 3, displayData[3]);
    }
};

#endif
