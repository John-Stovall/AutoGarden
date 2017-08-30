#define PIN_RESET 9  // Connect RST to pin 9 (req. for SPI and I2C)
#define PIN_DC    8  // Connect DC to pin 8 (required for SPI)
#define PIN_CS    10 // Connect CS to pin 10 (required for SPI)

//############################ Pin SetUP ############################
int Btry_Pin = A0;  //Simple Voltage Divider for battery measurment 
int tempPin1 = A1;   
int tempPin2 = A2;
int H2O_Pin1 = A3;
int H2O_Pin2 = A4;
int H2O_Pin3 = A5;
int H2O_Pin4 = A6;
int PhotoPin = A7;  //To insure no watering during the day

int SoleniodPin1 = 4;
int SoleniodPin2 = 5;
int SoleniodPin3 = 6;
int SoleniodPin4 = 7;

int BtnPin1 = 8;
int BtnPin2 = 9;


//############################ Variables ############################    
int tempVal; 
int rollingIndex = 0;
int minIndex, maxIndex;
int tempArray[5];
int temperatureArrayWk1[70];
int temperatureArrayWk2[70];
int saturationArrayWk1[70];
int saturationArrayWk2[70];
int saturationArrayWk3[70];
int saturationArrayWk4[70];

float keptVal;
float temperature1 = 0;
float temperature2 = 0;
float saturation1 = 0;
float saturation2 = 0;
float saturation3 = 0;
float saturation4 = 0;

//############################ Constants ############################
//Value of Photo Resistor at midmorning
const int DAY_LIGHT = 400;

const bool DEBUG = true;

const int minSaturation1 = 10;
const int minSaturation2 = 10;
const int minSaturation3 = 10;
const int minSaturation4 = 10;

//Battery Constants
const int LP1 = 48;   //Low Battery 4.8v
const int HP2 = 68;   //High Battery 5.6v

//Temperature Constants
const int FP1 = 148;  //Freezing Point Reference thermisitor 1
const int FP2 = 148;  //Freezing Point Reference thermisitor 2
const int BP1 = 880;  //Boiling Point Reference thermisitor 1
const int BP2 = 875;  //Boiling Point Reference thermisitor 2
const int TempOffset1 = 2;  //Offset for calibration
const int TempOffset2 = -1; //Offset for calibration

//Hydration Constants
const int DP1 = 0;    //Dry Point Reference H2O sensor 1
const int DP2 = 0;    //Dry Point Reference H2O sensor 2
const int DP3 = 0;    //Dry Point Reference H2O sensor 3
const int DP4 = 0;    //Dry Point Reference H2O sensor 4
const int SP1 = 880;  //Saturation Point Reference H2O sensor 1
const int SP2 = 875;  //Saturation Point Reference H2O sensor 2
const int SP3 = 875;  //Saturation Point Reference H2O sensor 3
const int SP4 = 875;  //Saturation Point Reference H2O sensor 4