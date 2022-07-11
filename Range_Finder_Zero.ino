#include "SPI.h"
#include "SD.h"
#include "AudioZero.h"

const int chipSelect = SDCARD_SS_PIN;

int BUTTON_PIN = A1;
int BUTTON_VALUE = 0;
int RANDOM_NUM = 0;
int RANDOM_NUM_OLD = 1;
int RANDOM_NUM_OLD2 = 2;
int RANDOM_NUM_OLD3 = 3;
int i = 0;
File SONG;


void setup()
{ 
 Serial.begin(115200);
 if (!SD.begin(chipSelect)) // returns 1 if the card is present
 {
  Serial.println("SD fail");
  return;
 }

  Serial.println("SD Initialized");

  // 44100kHz stereo => 88200 sample rate
  AudioZero.begin(2*44100);
  File SONG = SD.open("Mess_Up.wav");
  AudioZero.end();

}



void loop()
{  
 if (!SD.begin(chipSelect)) // returns 1 if the card is present
 {
  Serial.println("SD fail");
  return;
 }
 RANDOM_NUM = int(random(0,4));
 BUTTON_VALUE = analogRead(BUTTON_PIN);
 delay(200);
 //Serial.println(BUTTON_VALUE);
 if(BUTTON_VALUE > 400)
 {
  i = 1;
  //Serial.println("BUTTON PRESSED");
  while(i == 1)
  {
    BUTTON_VALUE = analogRead(BUTTON_PIN);
    if(BUTTON_VALUE < 400)
    {
      i = 0;
      delay(5);
      //Serial.println("BUTTON RELEASED");
    }
  }
  Serial.println("PLAY AUDIO");
  while(RANDOM_NUM == RANDOM_NUM_OLD || RANDOM_NUM == RANDOM_NUM_OLD2 || RANDOM_NUM == RANDOM_NUM_OLD3)
  {
    RANDOM_NUM = random(0,5);
  }
  Serial.println(RANDOM_NUM);
  //Serial.println(RANDOM_NUM_OLD);
  //Serial.println(RANDOM_NUM_OLD2);
  delay(200);
  switch (RANDOM_NUM)
  {
    case 0:
      SONG = SD.open("ESP_Nuke.wav");
      AudioZero.begin(2*44100);
      AudioZero.play(SONG);
      AudioZero.end();
      break;
    case 1:
      SONG = SD.open("Hurry_Up.wav");
      AudioZero.begin(2*44100);
      AudioZero.play(SONG);
      AudioZero.end();
      break;
    case 2:
      SONG = SD.open("Mess_Up.wav");
      AudioZero.begin(2*44100);
      AudioZero.play(SONG);
      AudioZero.end();
      break;
    case 3:
      SONG = SD.open("ThrowFar.wav");
      AudioZero.begin(2*44100);
      AudioZero.play(SONG);
      AudioZero.end();
      break;
    case 4:
      SONG = SD.open("Tailwind.wav");
      AudioZero.begin(2*44100);
      AudioZero.play(SONG);
      AudioZero.end();
       break;
  }
  RANDOM_NUM_OLD3 = RANDOM_NUM_OLD2;
  RANDOM_NUM_OLD2 = RANDOM_NUM_OLD;
  RANDOM_NUM_OLD = RANDOM_NUM;
 }

}
