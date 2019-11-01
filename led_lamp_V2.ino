//accel_STOP_v2b
#include          <Adafruit_NeoPixel.h>
#include          <SparkFun_ADXL345.h>  
#define           ALIVELED                13
#define           EMYLED                  7
#define           STOPLED                4
#define           PIXELSPIN               3
#define           STOPPIN                A1
#define           NUMOFPIXELS            88
int               stopValue      =        0;
int               emergency      =        0;
int               updatecompleted =       0;
int               accelx         =        0;
int               accely         =        0;
int               accelz         =        0; 
unsigned int      aliveledDelay1 =        10;
unsigned int      aliveledDelay2 =      490;
unsigned int      emystartDelay  =     1000;
unsigned int      emystopDelay   =     3000;
unsigned long     aliveledTimer  = millis();
unsigned long     stopTimer      = millis();
unsigned long     emyTimer       = millis();
Adafruit_NeoPixel pixels         = Adafruit_NeoPixel(NUMOFPIXELS, PIXELSPIN, NEO_GRB + NEO_KHZ800);
ADXL345           adxl           = ADXL345();
int               bx              =1500; //boot time

enum pixelsStates                  {PIXELS_STD, PIXELS_STP, PIXELS_EMY}  pixelsState;
enum aliveledStates                {alive_LED_ON, alive_LED_OFF}         aliveledState;

void setup() 
{ 
  pinMode(ALIVELED, OUTPUT);
  pinMode(STOPLED,  OUTPUT);
  pinMode(EMYLED,   OUTPUT);
  pixels.begin();
  pixelsState   = PIXELS_STD;
  aliveledState = alive_LED_OFF;
  aliveledTimer = millis();
  adxl.powerOn();               
  adxl.setRangeSetting(2);
 stopValue = analogRead(STOPPIN);

 {
  if (stopValue < 256) startup (205,0,0);//startup image 
  else
    loop() ;
  }
}
void loop() 
{
stoppixelsmachine();  
//aliveledmachine();   
}

void stoppixelsmachine()
{
    stopValue = analogRead(STOPPIN);
  if (stopValue < 256) 
     {
      digitalWrite(STOPLED, LOW);
      digitalWrite(EMYLED,  LOW);      
      pixelsState = PIXELS_STD;
      updatecompleted = 0;  
     }
   else 
     {
      digitalWrite(STOPLED, HIGH);
      if (emergency==0) pixelsState = PIXELS_STP; else pixelsState = PIXELS_EMY;
     }
 switch(pixelsState) 
 {
    case PIXELS_STD:
       {
       if (updatecompleted == 0) laurynopixels(15, 0, 0); 
       }      
    break;

    case PIXELS_STP:
       {
       if (updatecompleted == 0) laurynopixels(255,0,0);

//              adxl.readAccel(&accelx, &accely, &accelz);
//              if (accelz > 120)
//                      {
//                       digitalWrite(EMYLED, HIGH);
//                       emergency = 1;
//                       stopTimer = millis();
//                       emyTimer  = millis();
//                      }
       }      
    break;
//    case PIXELS_EMY:
//       {        
//        adxl.readAccel(&accelx, &accely, &accelz);
//        if (accelz > 120) emyTimer = millis();
//        if ((millis() - emyTimer)  <  emystopDelay)
//      {
//       if ((millis() - stopTimer) > emystartDelay)       
//        {
//           if ( (millis() - stopTimer) % 600 > 300) //mirskejimo tankis 
//              {
//               if (updatecompleted == 0) laurynopixels(115,0,0); //ryskumas mirksint
//
//                    digitalWrite(EMYLED, HIGH);
//                      
//              }
//            else
//              {
//          if (updatecompleted == 0) laurynopixels(255,0,0);
//              }         
//          }
//        else
//           {
//            if (updatecompleted == 0) laurynopixels(255,0,0);
//
//           }          
//      }
//            else
//             {
//              if (updatecompleted == 0) laurynopixels(255,0,0);
//
//                  digitalWrite(EMYLED, LOW);
//                  emergency = 0;
//              }
//       }      
//    break; 
 }
}



// tikrina ar nepakibo
//void aliveledmachine()
//{
// switch(aliveledState) 
//   {
//    case alive_LED_ON:
//      if((millis() - aliveledTimer) >= aliveledDelay1)
//       {
//        digitalWrite(ALIVELED, LOW);
//        aliveledState = alive_LED_OFF;
//        aliveledTimer = millis();
//        break;
//       }
//    case alive_LED_OFF:    
//      if((millis() - aliveledTimer) >= aliveledDelay2)
//       {
//        digitalWrite(ALIVELED, HIGH);
//        aliveledState = alive_LED_ON;
//        aliveledTimer = millis();
//        break;
//      }
//    }
//
//}
//padaryti per funkcija
void laurynopixels (int r, int g, int b)
{
 for(int i=0;i<NUMOFPIXELS;i++)
             {
            pixels.setPixelColor(i, pixels.Color(r,g,b)); 
           }   
              pixels.show();
}

void startup  (int r, int g, int b)
{
  {
    pixels.setPixelColor(12, pixels.Color(r, g, b));
    pixels.setPixelColor(13, pixels.Color(r, g, b));
    pixels.setPixelColor(14, pixels.Color(r, g, b));
    pixels.setPixelColor(15, pixels.Color(r, g, b));
    pixels.setPixelColor(28, pixels.Color(r, g, b));
    pixels.setPixelColor(29, pixels.Color(r, g, b));
    pixels.setPixelColor(30, pixels.Color(r, g, b));
    pixels.setPixelColor(31, pixels.Color(r, g, b));
    pixels.setPixelColor(44, pixels.Color(r, g, b));
    pixels.setPixelColor(45, pixels.Color(r, g, b));
    pixels.setPixelColor(46, pixels.Color(r, g, b));
    pixels.setPixelColor(47, pixels.Color(r, g, b));
    pixels.setPixelColor(60, pixels.Color(r, g, b));
    pixels.setPixelColor(61, pixels.Color(r, g, b));
    pixels.setPixelColor(62, pixels.Color(r, g, b));
    pixels.setPixelColor(63, pixels.Color(r, g, b));
  }
  pixels.show();
  delay(bx);
}

void regular  (int r, int g, int b)
{
  {
   pixels.setPixelColor(3 , pixels.Color(r, g, b));
   pixels.setPixelColor(16, pixels.Color(r, g, b));
   pixels.setPixelColor(22, pixels.Color(r, g, b));
   pixels.setPixelColor(23, pixels.Color(r, g, b));
   pixels.setPixelColor(25, pixels.Color(r, g, b));
   pixels.setPixelColor(26, pixels.Color(r, g, b));
   pixels.setPixelColor(28, pixels.Color(r, g, b));
   pixels.setPixelColor(29, pixels.Color(r, g, b));
   pixels.setPixelColor(42, pixels.Color(r, g, b));
   pixels.setPixelColor(41, pixels.Color(r, g, b));
   pixels.setPixelColor(35, pixels.Color(r, g, b));
   pixels.setPixelColor(36, pixels.Color(r, g, b));
   pixels.setPixelColor(37, pixels.Color(r, g, b));
   pixels.setPixelColor(46, pixels.Color(r, g, b));
   pixels.setPixelColor(47, pixels.Color(r, g, b));
   pixels.setPixelColor(48, pixels.Color(r, g, b));
   pixels.setPixelColor(73, pixels.Color(r, g, b));
   pixels.setPixelColor(74, pixels.Color(r, g, b));
   pixels.setPixelColor(77, pixels.Color(r, g, b));
   pixels.setPixelColor(78, pixels.Color(r, g, b));
   pixels.setPixelColor(81, pixels.Color(r, g, b));
   pixels.setPixelColor(82, pixels.Color(r, g, b));
   pixels.setPixelColor(85, pixels.Color(r, g, b));
   pixels.setPixelColor(86, pixels.Color(r, g, b));
   
  }
   pixels.show();
}
