#include <Wire.h>
#include "MMA7660.h"
MMA7660 accelemeter;

//int index = 0;
int buttonPin = 2;
int buttonState = false; //off at first
int delta = 250;
int nextTime = 0;
float password[51][3] = {{-0.90,-0.10,0.05},{-0.90,-0.05,0.00},{-0.90,-0.10,0.05},{-0.95,-0.05,0.05},{-0.95,-0.05,0.05},{-0.95,-0.05,0.05},{-0.95,-0.05,0.05},{-0.95,-0.05,-0.05},{-1.00,-0.10,0.00},{-0.95,-0.10,0.00},{-0.95,-0.05,-0.05},{-1.00,-0.05,0.00},{-0.95,-0.10,0.00},{-0.95,-0.10,0.00},{-0.90,-0.10,0.00},{-0.95,-0.05,-0.05},{-0.95,-0.05,-0.10},{-0.95,-0.10,-0.05},{-1.00,-0.10,0.00},{-0.95,-0.05,0.00},{-0.90,-0.05,-0.10},{-0.95,-0.05,-0.05},{-0.90,-0.05,0.00},{-0.95,-0.05,-0.05},{-0.90,-0.05,0.00},{-0.90,-0.10,-0.05},{-0.90,-0.10,0.00},{-0.95,-0.52,0.00},{-1.19,-0.29,0.29},{-1.14,-0.33,0.19},{-1.00,-0.29,0.19},{-0.90,-0.29,0.10},{-0.19,0.05,-0.24},{-0.29,0.43,-0.14},{-0.62,0.76,-0.19},{-1.10,0.24,0.24},{-0.95,-0.19,0.14},{-1.33,-0.19,0.62},{-1.00,0.00,0.43},{-1.10,0.05,0.38},{-1.24,0.05,0.52},{-0.71,0.24,0.05},{-0.38,0.29,-0.29},{-0.52,-0.81,0.14},{-1.24,-0.14,0.76},{-0.95,-0.14,0.29},{-0.90,0.00,0.24},{-0.95,-0.14,0.19},{-1.00,-0.19,0.14},{-0.90,-0.05,0.10},{-0.90,-0.10,0.05}};
float attempt1[52][3] = {{-1.00,0.00,0.05},{-0.95,-0.14,-0.05},{-0.95,-0.19,0.05},{-0.90,-0.05,0.05},{-0.95,-0.05,0.05},{-0.95,-0.05,0.00},{-1.00,-0.10,0.00},{-0.95,-0.05,0.05},{-0.95,0.00,0.00},{-1.00,0.00,0.00},{-0.95,-0.05,0.00},{-1.00,-0.05,0.00},{-1.00,0.00,-0.05},{-1.00,-0.05,0.05},{-0.95,0.00,0.00},{-0.95,-0.05,0.00},{-0.90,0.05,0.05},{-0.95,-0.10,0.00},{-0.95,-0.10,0.00},{-0.95,-0.10,0.05},{-0.90,-0.05,0.00},{-0.95,-0.05,0.00},{-0.95,-0.05,0.00},{-0.90,0.05,-0.05},{-0.90,-0.10,0.00},{-0.90,-0.05,0.05},{-0.95,0.00,0.05},{-0.95,-0.05,0.05},{-0.95,-0.05,0.00},{-1.29,0.10,0.24},{-1.48,-0.43,0.38},{-0.95,-0.38,0.29},{-0.67,-0.43,0.14},{-0.33,-0.14,-0.14},{-0.33,0.29,-0.24},{-0.67,0.57,-0.14},{-1.19,0.29,0.14},{-0.86,0.14,0.14},{-1.38,-0.24,0.62},{-0.95,-0.29,0.86},{-1.00,-0.14,0.38},{-1.29,0.29,0.38},{-1.10,0.57,0.14},{-0.14,0.14,-0.29},{-0.05,-0.38,-0.19},{-0.19,-0.90,0.14},{-1.00,-0.67,0.43},{-1.48,0.10,0.48},{-1.29,0.05,0.43},{-0.76,0.00,0.24},{-0.71,0.05,0.24},{-0.90,0.00,0.29}};
int countX = 0;
int countY = 0;
int countZ = 0;
float realTimeAttemptX[52] = {};
float realTimeAttemptY[52] = {};
float realTimeAttemptZ[52] = {};

void setup()
{
	accelemeter.init();  
	Serial.begin(9600);
  //Serial.println("Press Button to begin Motion's login authentification process");
  pinMode(buttonPin, INPUT);
}
void loop()
{
  
	int8_t x;
	int8_t y;
	int8_t z;
	float ax,ay,az;

  int time = millis();

  if(digitalRead(buttonPin) == HIGH) {
    delay(200); // Melany Added this, button now works consistently
    buttonState = !buttonState;
    Serial.println("BUTTON PRESSED!");   
  }

  if(time>nextTime) {
      if(buttonState) {
        buttonState = !buttonState;
        //countdown to begin recording
        Serial.println("Countdown to Start Gesture: ");
        delay(1000);
        Serial.print("In 3...");
        delay(1000);
        Serial.print("2...");
        delay(1000);
        Serial.print("1...");
        delay(1000);
        Serial.print("START GESTURE!!");  // will only record 50 points until here
        delay(1000);
        for (int j=0; j<=51; j++){
      	accelemeter.getXYZ(&x,&y,&z);
//        Serial.println(x);
//        Serial.println(y);
//        Serial.println(z);
        accelemeter.getAcceleration(&ax,&ay,&az);
        
        realTimeAttemptX[j] = ax;
        realTimeAttemptY[j] = ay;
        realTimeAttemptY[j] = az;
        Serial.print("{"+String(ax)+","+String(ay)+","+String(az)+"}"+",");
        Serial.print("{realTIME: "+String(realTimeAttemptX[j])+","+String(realTimeAttemptY[j])+","+String(realTimeAttemptZ[j])+"}"+",");
        delay(100);
        nextTime += delta;}

        if (checkRealPassword() == true){
          Serial.println("Password Validated! Login Authorized");
          //exit(1);
         }
         else
          Serial.println("Password attempt denied.Press Button to try again. ");
          
    }
    
    
 }
 
 
}

boolean checkPassword(){
  countX = 0;
  countY = 0;
  countZ = 0;
  for (int i = 0; i <= 51; i++){
    // 0.20 is our threshold because it has a 0.05 to 0.10 error usually so 0.20 is a safe bet. Our scale is +/- 1.5g.
    if (((password[i][0] - 0.20) <= attempt1[i][0]) && (attempt1[i][0]<= (password[i][0]+0.20))){
      countX++;
    }
    if (((password[i][1] - 0.20) <= attempt1[i][1]) && ((password[i][1]+0.20) >= attempt1[i][1])){
      countY++;
    }
    if (((password[i][2] - 0.20) <= attempt1[i][2]) && ((password[i][2]+0.20) >= attempt1[i][2])){
      countZ++;
    }
  }
  //calculate percent accuracy
  float avg = countX + countY + countZ;
  float temp = avg/3;
  temp = temp/51;
  temp = temp*100;

  if (temp >= 50){
    //For hardcoded sets: data is good! 52%!
    Serial.println(countX);
    Serial.println(countY);
    Serial.println(countY);
    return true;
  }
  Serial.println(temp);
  return false;
  

  delay(1000);
}

bool checkRealPassword(){
  countX = 0;
  countY = 0;
  countZ = 0;
  for (int i = 0; i <= 51; i++){
    // 0.20 is our threshold because it has a 0.05 to 0.10 error usually so 0.20 is a safe bet. Our scale is +/- 1.5g.
    if (((password[i][0] - 0.15) <= realTimeAttemptX[i]) && (realTimeAttemptX[i]<= (password[i][0]+0.15))){
      countX++;
    }
    if (((password[i][1] - 0.15) <= realTimeAttemptY[i]) && ((password[i][1]+0.15) >= realTimeAttemptY[i])){
      countY++;
    }
    if (((password[i][2] - 0.15) <= realTimeAttemptZ[i]) && ((password[i][2]+0.15) >= realTimeAttemptZ[i])){
      countZ++;
    }
  }
  //calculate percent accuracy
  float avg = countX + countY + countZ;
  float temp = avg/3;
  temp = temp/51;
  temp = temp*100;

  if (temp >= 50){
  /// data must match at least 50% to validate
    
    Serial.println(temp);
    return true;
  }
  Serial.println(temp);
  return false;
  

  delay(1000);
}
