// Low-Power - Version: Latest 
#include <LowPower.h>

//#include <ArduinoLowPower.h>
#include "Garden.h"
#include <SPI.h>
#include <Wire.h>
#include <SFE_MicroOLED.h>

MicroOLED oled(PIN_RESET, PIN_DC, PIN_CS);

//############################   Setup   ############################
void setup() {
  
  pinMode(SoleniodPin1, OUTPUT);
  pinMode(SoleniodPin2, OUTPUT);
  pinMode(SoleniodPin3, OUTPUT);
  pinMode(SoleniodPin4, OUTPUT);
  pinMode(BtnPin1, INPUT_PULLUP);
  pinMode(BtnPin2, INPUT_PULLUP);
  
  digitalWrite(SoleniodPin1, LOW);
  digitalWrite(SoleniodPin2, LOW);
  digitalWrite(SoleniodPin3, LOW);
  digitalWrite(SoleniodPin4, LOW);
  
  Serial.begin(115200);
  // all of the pins and configure the OLED.
  oled.begin();
  
  oled.setFontType(0);  // Set the text to small (10 columns, 6 rows worth of characters).
  /*
  Btn1         Btn2
  1234567890   1234567890  
  T1:_XXX.XF   T1 /\/\/\/
  T2:_XXX.XF   T2 /\---/\
  H1:_XX.XX%   H1 /\/\/\/
  H2:_XX.XX%   H2 /\/\/\/
  H3:_XX.XX%   H3 /\/\/\/
  H4:_XX.XX%   H4 /\/\/\/
  */
}

//############################   Loop    ############################
void loop() {
  //Wake up
  //Measure Temperatures
  int timeSlept = 10000;
  if(timeSlept > 10000){
    getReadings();
    saveReadings();
    rollingIndex = (rollingIndex + 1) % 70;
    
    //Check and see how dark it is. This is a very basic check system and can
    //be expanded as needed.
    float light = filterAnalog(PhotoPin);
    if(light < DAY_LIGHT){
      if((temperature1 < 75) && (temperature2 < 75)){ 
        if(saturation1 < minSaturation1) waterGarden(1);
        else if(saturation2 < minSaturation2) waterGarden(2);
        else if(saturation3 < minSaturation3) waterGarden(3);
        else if(saturation4 < minSaturation4) waterGarden(4);
        else waterGarden(0);
      }
    }
  }
  
  //If button 1 is pressed
  while(BtnPin1 == LOW){
    getReadings();
    mapReadings();
    printReadings();
    if(DEBUG){
      Serial.print("T1: ");Serial.print(temperature1);
      Serial.print(", T2: ");Serial.print(temperature2);  
      Serial.print(", H1: ");Serial.print(saturation1); 
      Serial.print(", H2: ");Serial.print(saturation2); 
      Serial.print(", H3: ");Serial.print(saturation3); 
      Serial.print(", H4: ");Serial.println(saturation4); 
      
    }
    
  }
  // ATmega328P, ATmega168 Sleeps for one second
  LowPower.idle(SLEEP_1S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, 
                SPI_OFF, USART0_OFF, TWI_OFF);
}

void printReadings(){
  oled.setCursor(0, 0);  // Set the text cursor to the upper-left of the screen.
  oled.print("T1: "); oled.print(temperature1, 1); oled.print("F");
  oled.setCursor(0, 1);
  oled.print("T2: "); oled.print(temperature2, 1); oled.print("F");
  oled.setCursor(0, 2);
  oled.print("H1: "); oled.print(saturation1, 1); oled.print("%");
  oled.setCursor(0, 3);
  oled.print("H2: "); oled.print(saturation2, 1); oled.print("%");
  oled.setCursor(0, 4);
  oled.print("H3: "); oled.print(saturation3, 1); oled.print("%");
  oled.setCursor(0, 5);
  oled.print("H4: "); oled.print(saturation4, 1); oled.print("%");
  oled.display(); // Draw whatever is in the display buffer.
}

void waterGarden(int garden){
  digitalWrite(SoleniodPin1, LOW);
  digitalWrite(SoleniodPin1, LOW);
  digitalWrite(SoleniodPin1, LOW);
  digitalWrite(SoleniodPin1, LOW);
  if(garden != 0) digitalWrite(garden + 2, HIGH);
}

void mapReadings(){
  temperature1 = map(temperature1, FP1, BP1, 32, 212) + TempOffset1;
  temperature2 = map(temperature2, FP2, BP2, 32, 212) + TempOffset2;
  saturation1 = map(saturation1, DP1, SP1, 0, 100);
  saturation2 = map(saturation1, DP2, SP2, 0, 100);
  saturation3 = map(saturation1, DP3, SP3, 0, 100);
  saturation4 = map(saturation1, DP4, SP4, 0, 100);
}

void saveReadings(){
  temperatureArrayWk1[rollingIndex%70] = int(temperature1);
  temperatureArrayWk2[rollingIndex%70] = int(temperature2);
  saturationArrayWk1[rollingIndex%70] = int(saturation1);
  saturationArrayWk2[rollingIndex%70] = int(saturation2);
  saturationArrayWk3[rollingIndex%70] = int(saturation3);
  saturationArrayWk4[rollingIndex%70] = int(saturation4);
}

void getReadings(){
  temperature1 = filterAnalog(tempPin1);
  temperature2 = filterAnalog(tempPin2);
  saturation1 = filterAnalog(H2O_Pin1);
  saturation2 = filterAnalog(H2O_Pin2);
  saturation3 = filterAnalog(H2O_Pin3);
  saturation4 = filterAnalog(H2O_Pin4);
}

float filterAnalog(int Pin){
  minIndex = 0;
  maxIndex = 0;
  keptVal = 0;
  
  // populates the first array and fillters out the outliers 
  for(int i = 0; i < 5; i++){
    tempVal = analogRead(Pin);
    tempArray[i] = tempVal;
    if(tempVal < tempArray[minIndex]) minIndex = i;
    if(tempVal > tempArray[maxIndex]) maxIndex = i;
  }

  // sums the median 3 measurments 
  for(int i = 0; i < 5; i++){
    if(minIndex == i || maxIndex == i);
    else keptVal += tempArray[i];
  }
  
  // averages the mean of the 3 measurments 
  return keptVal/3;
}

