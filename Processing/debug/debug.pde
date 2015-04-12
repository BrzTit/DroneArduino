// TODO : Indentation pourrie avec cet IDE ...
 import processing.serial.*;

 Serial myPort;
 
 int[] vitesse = new int[4];

void setup() {
   size(500,500);
   
   myPort = new Serial(this, Serial.list()[0], 9600);
}

void draw() {
  
  textSize(32);
  background(165, 255, 255);
  
   int i;
   int x = 50;
   int y = 50;
   
   // S'il y a des données
   if ( myPort.available() > 0) 
   {
       for(i=0; i<4; i++)
       {
         int tmp = myPort.read();
         // Parfois bug de lecture, on obtient -1
         // -1 empeche lecture valeur visuellement
         if(tmp >= 0)
           vitesse[i] = tmp;
       }
   }
   
   // Affiche les 4 valeurs
    for(i=0; i < 4; i++)
    {
       text(vitesse[i], x, y);
       x += 100;
       if(x >= 250)
       {
         y += 100;
         x = 50;
       } 
    }
 }

