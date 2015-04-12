#include <Arduino.h>
#include "Wire.h"
#include "Servo.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Moteurs.h"

MPU6050 mpu;
Moteurs moteur;

int16_t angle[3];
int16_t gyro[3];

int val = 0;
char lecture;



void setup()
{
    Serial.begin(9600);
    
    mpu.initialize();    
    
    moteur.init();
    moteur.erreurAngle(mpu);
}

void loop()
{
    lecture = Serial.read();
    
    
    mpu.getMotion6(&angle[0], &angle[1], &angle[2], &gyro[0], &gyro[1], &gyro[2]);
    
    moteur.updateAngle(angle);
    
    moteur.setVitesse(lecture);
    moteur.equilibre();
    
    moteur.deplacer();

}
