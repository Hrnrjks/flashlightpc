#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int lightSensorPin = A0;
int analogValue = 0;
int inputBit = 0;
int i = 0; // cmd array index
int j = 0; // printWord array index
int k = 0; // alphabetLetter index
bool cmd[3] = { 0, 0, 0 };

bool alphabetLetter[5] = { 0, 0, 0, 0, 0 };
char printWord[] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };

bool inputting = 0;
bool cmdEntered = 0;
bool zeroOrOne = 0;
bool zeroOrOneLetter = 0;
bool inputtingWord = 0;

void closeBtn()
{
  lcd.clear();
  lcd.print("   [X]");
  inputStopCheck();

  if (!inputting)
  {
    i = 0;
    j = 0;
    lcd.clear();
    loop();
  }
  
  lcd.clear();
}

void inputStopCheck()
{
    delay(1000); // wait for input
    analogValue = analogRead(lightSensorPin);
    if (analogValue < 100)
    {
      inputting = 0;
    }
    else
    {
      inputting = 1;
    }
}

void print12or3Bit(bool onePrint)
{
    lcd.clear();
    if (!onePrint)
    {
      switch (i)
      {
      case 0:
        lcd.print("1st bit: 0");
        break;
      case 1:
        lcd.print("2nd bit: 0");
        break;
      case 2:
        lcd.print("3rd bit: 0");
        break;
      }
    }

    else
    {
      switch (i)
      {
      case 0:
        lcd.print("1st bit: 1");
        break;
      case 1:
        lcd.print("2nd bit: 1");
        break;
      case 2:
        lcd.print("3rd bit: 1");
        break;
      }
    }
}

void resetCmdArray()
{
  for (int x = 0; x < 3; ++x)
  {
    cmd[x] = 0;
  }
}

void print1234or5Bit(bool onePrint)
{
    lcd.clear();
    if (!onePrint)
    {
      switch (k)
      {
      case 0:
        lcd.print("1st bit: 0");
        break;
      case 1:
        lcd.print("2nd bit: 0");
        break;
      case 2:
        lcd.print("3rd bit: 0");
        break;
      case 3:
        lcd.print("4th bit: 0");
        break;
      case 4:
        lcd.print("5th bit: 0");
        break;
      }
    }

    else
    {
      switch (k)
      {
      case 0:
        lcd.print("1st bit: 1");
        break;
      case 1:
        lcd.print("2nd bit: 1");
        break;
      case 2:
        lcd.print("3rd bit: 1");
        break;
      case 3:
        lcd.print("4th bit: 1");
        break;
      case 4:
        lcd.print("5th bit: 1");
        break;
      }
    }
}

void printDevice()
{ 
  lcd.clear();
  
  do
  {    
    if (j > 15) // if word fully inputted, then print the word
    {
      j = 0;

      while (1)
      {
        for (int x; x < 16; ++x)
        {
          lcd.print(printWord[x]);
        }
        
        closeBtn();
      }
    }

    if (k > 5)
    {
      k = 0;
      for (int x; x < 6; ++x)
      {
        lcd.print(alphabetLetter[x]);;
      }
      delay(2000);
      lcd.clear();
      
      loop();
    }

    inputStopCheck();
    while (inputting && k < 6) // input single letter
    {
      zeroOrOneLetter = 0;
      print1234or5Bit(zeroOrOneLetter);
      inputStopCheck();
      if (!inputting)
      {
        alphabetLetter[k] = 0;
        ++k;
        printDevice();
      }
      if (!inputting)
      {
        printDevice();
      }

      zeroOrOneLetter = 1;
      print1234or5Bit(zeroOrOneLetter);
      inputStopCheck();
      if (!inputting)
      {
        alphabetLetter[k] = 1;
        ++k;
        printDevice();
      }
    }

  } while (j < 16);
}

void calcDevice()
{
}

void tGum()
{
  lcd.clear();
  lcd.print("Welcome...");
  delay(1000);
  
  lcd.clear();
  lcd.print("To the...");
  delay(1000);

  lcd.clear();
  lcd.print("   Terror Gum");
  lcd.setCursor(0, 1);
  lcd.print("     Project");
  lcd.setCursor(0, 0);
  delay(1500);

  lcd.clear();
  lcd.print("   Enjoy your");
  lcd.setCursor(0, 1);
  lcd.print("     stay...");
  lcd.setCursor(0, 0);
  delay(1500);
  lcd.clear();
}

void cmdInput()
{
  while (inputting && i < 3)
  {
      zeroOrOne = 0;
      print12or3Bit(zeroOrOne);
    
      inputStopCheck();
    
      if (!inputting)
      { 
        inputBit = 0;
        cmd[i] = inputBit;
        lcd.clear();
        ++i;
        break;
      }
      if (!inputting) break;

      zeroOrOne = 1;
      print12or3Bit(zeroOrOne);
    
      inputStopCheck();
    
      if (!inputting)
      { 
        inputBit = 1;
        cmd[i] = inputBit;
        lcd.clear();
        ++i;
        break;
      }
      if (!inputting) break;
    
      lcd.clear();
    } //while loop end

    if (!inputting && i > 2) // if not inputting and cmd array is filled up
    {
      for (int x = 0; x < 3; ++x)
      {
       lcd.print(cmd[x]);
      }
      
      i = 0;
      cmdEntered = 1;
      delay(1000);
    }
}

void programLauncher()
{
  if (cmdEntered)
  {
    if (cmd[0] == 0 && cmd[1] == 0 && cmd[2] == 1)
    {
      lcd.clear();
      lcd.print("Launching Print");

      resetCmdArray();

      delay(1000);
      printDevice();
    }
    
    else if (cmd[0] == 0 && cmd[1] == 1 && cmd[2] == 0)
    {
      lcd.clear();
      lcd.print("Launching Calc");

      resetCmdArray();

      delay(1000);
      calcDevice();
    }

    else if (cmd[0] == 0 && cmd[1] == 1 && cmd[2] == 1)
    {
      lcd.clear();
      lcd.print("Launching Tgum");

      resetCmdArray();

      delay(1000);
      tGum();
    }
    
    else
    {
      lcd.clear();
      lcd.print("ERROR");
      delay(1000);
    }

    cmdEntered = 0;
  }
}

void setup()
{
  lcd.begin(16, 2);
  lcd.print("   Lumeno PC");
  delay(2000);
  lcd.clear();
}


void loop() // main loop
{
  delay(1000);
  analogValue = analogRead(lightSensorPin);
  if (analogValue > 100)
  {
    inputting = 1;
  }
  else
  {
    inputting = 0;
  }
  
  cmdInput(); // program launcher; launches if inputting == 1; if cmd entered then cmdEntered = 1;

  if (cmdEntered) programLauncher();
  
  lcd.clear();
}
