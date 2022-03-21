#include <Wire.h>
int btnPin= 4;
const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int precBtn = HIGH;
void setup(){
  pinMode(btnPin, INPUT_PULLUP);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); 
  Wire.write(0);     
  Wire.endTransmission(true);
  Serial.begin(38400);
}
void loop(){
  int resultBtn = digitalRead(btnPin);
  if (precBtn == HIGH && resultBtn == LOW)
  {
    startBatch();
  }
  if (resultBtn==LOW)
  {
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr,14,true);
    
    // Reads the data from the sensor
    AcX=Wire.read()<<8|Wire.read();     
    AcY=Wire.read()<<8|Wire.read();  
    AcZ=Wire.read()<<8|Wire.read();  
    Tmp=Wire.read()<<8|Wire.read();  
    GyX=Wire.read()<<8|Wire.read();  
    GyY=Wire.read()<<8|Wire.read();  
    GyZ=Wire.read()<<8|Wire.read();  

    Serial.print("START");
    Serial.print(" "); Serial.print(AcX);
    Serial.print(" "); Serial.print(AcY);
    Serial.print(" "); Serial.print(AcZ);
    Serial.print(" "); Serial.print(GyX);
    Serial.print(" "); Serial.print(GyY);
    Serial.print(" "); Serial.print(GyZ);
    Serial.println(" END");
  }

  if (precBtn == LOW && resultBtn == HIGH)
  {
    closeBatch();
  }
  precBtn = resultBtn;
}
void startBatch()
{
  Serial.println("STARTING BATCH");
}
void closeBatch()
{
  Serial.println("CLOSING BATCH");
}
