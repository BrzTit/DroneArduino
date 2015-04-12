#include "Servo.h"
#include "MPU6050.h"

class Moteurs
{
  private:
    int16_t angle[3];
    int16_t anglePrec[3];
  
    Servo moteur[4];
    int8_t vitesse[4];
    
    Servo test;
    
    int vitesseGlobale;
    
    int valErreurAngleX;
    int valErreurAngleY;
    
    boolean enVol;
    
    const int vitesseDepart = 50;

  public:
    void init();
    void updateAngle(int16_t valAngle[]);
    void erreurAngle(MPU6050 mpu);
    void equilibre();
    int getRotationX();
    int getRotationY();
    void afficheValErreurs();
    void setVitesse(char lecture);
    void deplacer();
    void depart();
};
