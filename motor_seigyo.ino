#define PIN_IN1L  13
#define PIN_IN2L  12
#define PIN_VREFL 11 // PWM

#define PIN_IN1R  5
#define PIN_IN2R  4
#define PIN_VREFR 3 // PWM
 
void setup(){
  pinMode(PIN_IN1L,OUTPUT); 
  pinMode(PIN_IN2L,OUTPUT); 
  pinMode(PIN_IN1R,OUTPUT); 
  pinMode(PIN_IN2R,OUTPUT); 
}
 
void loop(){
      
    // モーターの回転速度を中間にする
    analogWrite(PIN_VREFL,127); 
    analogWrite(PIN_VREFR,127); 
 
    // 回転
    digitalWrite(PIN_IN1L,HIGH);
    digitalWrite(PIN_IN2L,LOW);
    digitalWrite(PIN_IN1R,HIGH);
    digitalWrite(PIN_IN2R,LOW);
    delay(5000);
 
    // ブレーキ
    digitalWrite(PIN_IN1L,HIGH);
    digitalWrite(PIN_IN2L,HIGH);
    digitalWrite(PIN_IN1R,HIGH);
    digitalWrite(PIN_IN2R,HIGH);
    
    // 逆回転
    digitalWrite(PIN_IN1L,LOW);
    digitalWrite(PIN_IN2L,HIGH);    
    digitalWrite(PIN_IN1R,LOW);
    digitalWrite(PIN_IN2R,HIGH);    
    delay(5000);
 
    // ブレーキ
    digitalWrite(PIN_IN1L,HIGH);
    digitalWrite(PIN_IN2L,HIGH);
    digitalWrite(PIN_IN1R,HIGH);
    digitalWrite(PIN_IN2R,HIGH);
    delay(2000);
    
    // モーターの回転速度を最大にする
    analogWrite(PIN_VREFR,255); 
    analogWrite(PIN_VREFL,255); 
    
    // 逆回転　
    digitalWrite(PIN_IN1R,LOW);
    digitalWrite(PIN_IN2R,HIGH);    
    digitalWrite(PIN_IN1L,LOW);
    digitalWrite(PIN_IN2L,HIGH);    
    delay(5000);
                
    // ストップ
    digitalWrite(PIN_IN1L,LOW);
    digitalWrite(PIN_IN2L,LOW);
    digitalWrite(PIN_IN1R,LOW);
    digitalWrite(PIN_IN2R,LOW);
    delay(2000);
}
