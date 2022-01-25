#include "arduinoFFT.h"
#include <avr/wdt.h>
 
#define SAMPLES 128            //Must be a power of 2
#define SAMPLING_FREQUENCY 7500 //Hz, must be less than 10000 due to ADC

 

//PWMで速度調節、前に進みながらみぎまわりするoutputpin1,2とoutputpin3,4の速さを変える

 

arduinoFFT FFT = arduinoFFT();
 
unsigned int sampling_period_us;
unsigned long microseconds;
const int outputPin1 = 13;//11
const int outputPin2 = 12;//10
const int outputPin3 = 8;//9
const int outputPin4 = 7;//6
const int vrefL = 10;
const int vrefR = 11;

 

void software_reset(){
  wdt_disable();
  wdt_enable(WDTO_15MS);
  while(1){}
}

 

void setup() {
    Serial.begin(115200);//シリアル転送レート
 
    sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));

 

    pinMode(outputPin1,OUTPUT);//11,10,9,6をアウトプット
    pinMode(outputPin2,OUTPUT);
    pinMode(outputPin3,OUTPUT);
    pinMode(outputPin4,OUTPUT);
    pinMode(vrefR, OUTPUT);
    pinMode(vrefL, OUTPUT);
}
 
void loop() {
    double vReal[SAMPLES];
    double vImag[SAMPLES];
   
    /*SAMPLING*/
    for(int i=0; i<SAMPLES; i++)
    {
        microseconds = micros();    //Overflows after around 70 minutes!
     
        vReal[i] = analogRead(A0);  //ESP8266の場合は「A0」。普通のArduinoは「0」。//0~5Vの電圧を一定時間感知して配列に格納
        vImag[i] = 0;
     
        while(micros() < (microseconds + sampling_period_us)){
        }
    }
 
    /*FFT*/
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
 
    /*PRINT RESULTS*/
    Serial.println(peak);     //Print out what frequency is the most dominant.


 

      if(peak > 3650 && peak < 3850){
      analogWrite(vrefL, 80);
      analogWrite(vrefR, 255);
      digitalWrite(outputPin1,HIGH);  //左  
      digitalWrite(outputPin2,LOW);
      
      digitalWrite(outputPin3,HIGH); //右
      digitalWrite(outputPin4,LOW);
      
      delay(800);

      Serial.print("直進");
    }
    
    else if(peak >2200 && peak < 2400){
      analogWrite(vrefL, 70);
      analogWrite(vrefR, 100);
      digitalWrite(outputPin1,HIGH);  //左  
      digitalWrite(outputPin2,LOW);
      
      digitalWrite(outputPin3,HIGH); //右
      digitalWrite(outputPin4,LOW);

      Serial.print("右折");
    }
    
    else if(peak > 2700 && peak < 2800){ 
      analogWrite(vrefL, 28);
      analogWrite(vrefR, 255);
      digitalWrite(outputPin1,HIGH);  //左  
      digitalWrite(outputPin2,LOW);
      
      digitalWrite(outputPin3,HIGH); //右
      digitalWrite(outputPin4,LOW);

      Serial.print("左折");
    }
    
    else if(peak > 2700 && peak < 3000){
      analogWrite(vrefL, 255);
      analogWrite(vrefR, 255);
      digitalWrite(outputPin1,LOW);  //左  
      digitalWrite(outputPin2,HIGH);
      
      digitalWrite(outputPin3,LOW); //右
      digitalWrite(outputPin4,HIGH);
      
      delay(500);

      Serial.print("後退");
    }
    
    else{
      analogWrite(vrefL, 255);
      analogWrite(vrefR, 255);
      digitalWrite(outputPin1,LOW);  //左
      digitalWrite(outputPin2,LOW);



      digitalWrite(outputPin3,LOW); //右
      digitalWrite(outputPin4,LOW);
      //delay(100);
      Serial.print("x");
    } 
    delay(1);  //Repeat the process every second OR:
}
