#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <Mouse.h>
MPU6050 mpu;
int16_t ax,ay,az,gx,gy,gz;
int vx,vy;
const int rbutton=4;
const int lbutton=5;
void setup() {
  Serial.begin(9600);
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
  Mouse.begin();
  Wire.begin();
  mpu.initialize();
  if (!mpu.testConnection())
  {
    while(1);
  }
}

void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  vx = -(ax)/500;
  vy = -(ay)/500;
  Mouse.move(vx, vy);
  delay(20);
  int rstate= digitalRead(rbutton);
  int lstate= digitalRead(lbutton);
  if(rstate==LOW){
    Mouse.press(MOUSE_RIGHT);
  }
   else if(rstate== HIGH){
      Mouse.release(MOUSE_RIGHT);
  }
  if(lstate==LOW){
    Mouse.press(MOUSE_LEFT);
  }
   else if(lstate== HIGH){
      Mouse.release(MOUSE_LEFT);
  }
}
