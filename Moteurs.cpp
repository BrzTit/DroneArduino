#include "Moteurs.h"

void Moteurs::init()
{
  int i;

  moteur[0].attach(6);
  moteur[1].attach(9);
  moteur[2].attach(10);
  moteur[3].attach(11);
  
  test.attach(3);
  
  for(i=0; i < 4; i++)
  {
    vitesse[i] = 0;
    moteur[i].write(vitesse[i]);
    test.write(vitesse[i]);
  }
}

void Moteurs::updateAngle(int16_t valAngle[])
{
   int8_t i;
   
   for(i=0; i < 3; i++)
   {
       anglePrec[i] = angle[i];
       angle[i] = map(valAngle[i], -17000, 17000, 0, 179);         
   }
}

void Moteurs::erreurAngle(MPU6050 mpu)
{
  int i;
  int16_t angle[3];
  int16_t gyro[3];
  
  for(i=0; i < 100; i++)
  {
     mpu.getMotion6(&angle[0], &angle[1], &angle[2], &gyro[0], &gyro[1], &gyro[2]);
     
     valErreurAngleX += map(angle[0], -17000, 17000, 0, 179);
     valErreurAngleY += map(angle[1], -17000, 17000, 0, 179);
  }
  
  valErreurAngleX /= 100;
  valErreurAngleY /= 100;
  
  valErreurAngleX -= 90;
  valErreurAngleY -= 90;
}

void Moteurs::afficheValErreurs()
{
  Serial.print(valErreurAngleX);
  Serial.print(" - ");
  Serial.println(valErreurAngleY); 
}

int Moteurs::getRotationX()
{
  return angle[0] - valErreurAngleX - 90;
}

int Moteurs::getRotationY()
{
    return angle[1] - valErreurAngleY - 90;
}

void Moteurs::equilibre()
{
  vitesse[0] -= getRotationX();
  vitesse[2] -= getRotationX();
  
  vitesse[1] += getRotationX();
  vitesse[3] += getRotationX();
  
  for(int i = 0; i < 4; i++)
  {
    if(vitesse[i] < 0)
       vitesse[i] = 0; 
  }
  
  Serial.print(vitesse[0]);
  Serial.print("\t");
  Serial.print(vitesse[1]);
  Serial.print("\t");
  Serial.print(vitesse[2]);
  Serial.print("\t");
  Serial.print(vitesse[3]);
  
  Serial.println("");
  
}

void Moteurs::setVitesse(char lecture)
{
  if(lecture == 'e')
    vitesseGlobale += 1;
  else if(lecture == 'a')
    vitesseGlobale -= 1;
  else if(lecture == 's')
    vitesseGlobale = 0;
  else if(lecture == 'd')
    depart();
    
  for(int i = 0; i < 4; i++)
    vitesse[i] = vitesseGlobale;
  
}

void Moteurs::depart()
{
  int i;
 
  for(i=0; i < 25; i++)
  {
     for(int e=0; e<4; e++)
       moteur[e].write(i);
     test.write(i);
     delay(300);
  } 
  vitesseGlobale = 25;
  
}

void Moteurs::deplacer()
{
  int i;
  
  for(i=0; i < 4; i++)
    moteur[i].write(vitesse[i] + 10); // DEbug servoMoteur
    
  test.write(vitesseGlobale + 5);
  
}
