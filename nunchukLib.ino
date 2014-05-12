
#include <Wire.h>
#include "nunchuklib.h"

void setup()
{
 
Serial.begin(19200);
nunchuk_init();
Serial.println("init");

}

void loop()
{
   nunchuk_receive_data();
  
    // on extrait les données
    // dans mon exemple j'utilise uniquement les données d'accélération sur l'axe Y
    double accelX = nunchuk_accelx();
    double accelY = nunchuk_accely();
    double accelZ = nunchuk_accelz();
    
    Serial.print("X:");
    Serial.print(accelX);
    Serial.print("\t");
    
    Serial.print("Y:");
    Serial.println(accelY);
     
    delay(50);

}
