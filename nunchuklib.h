// Doit être ajusté en fonction de chaque nunchuck
#define ZEROX 300
#define ZEROY 300
#define ZEROZ 0

// adresse I2C du nunchuck
#define WII_NUNCHUK_I2C_ADDRESS 0x52

static void nunchuk_init(){
  Wire.begin();
  
  Wire.beginTransmission(WII_NUNCHUK_I2C_ADDRESS);
  Wire.write(0xF0);
  Wire.write(0x55);
   Wire.endTransmission();
  
  Wire.beginTransmission(WII_NUNCHUK_I2C_ADDRESS);
  Wire.write(0xFB);
  Wire.write(0x00);
  Wire.endTransmission();
}

static int nunchuk_count;
static double nunchuk_x = -9999;
static double nunchuk_y = -9999;
static double nunchuk_z = -9999;
static uint8_t nunchuk_data[6];

static void nunchuk_receive_data(){
  nunchuk_count = 0;
   // on demande 6 octets au nunchuck
  Wire.requestFrom(WII_NUNCHUK_I2C_ADDRESS, 6);
  
  // tant qu'il y a des données
  while(Wire.available())
  {
    // on récupère les données
    nunchuk_data[nunchuk_count++] = Wire.read();
  }
  
  // on réinitialise le nunchuck pour la prochaine demande
  Wire.beginTransmission(WII_NUNCHUK_I2C_ADDRESS);
  Wire.write(0x00);
  Wire.endTransmission();
  nunchuk_x = ((nunchuk_data[2] << 2) + ((nunchuk_data[5] >> 2) & 0x03) - ZEROX);
  nunchuk_y = ((nunchuk_data[3] << 2) + ((nunchuk_data[5] >> 4) & 0x03) - ZEROY);
  nunchuk_z = ((nunchuk_data[4] << 2) + ((nunchuk_data[5] >> 6) & 0x03) - ZEROZ);
  nunchuk_x = (nunchuk_x  * 180) / 425;
  nunchuk_y = (nunchuk_y  * 180) / 425;
}

static double nunchuk_accelx(){
  return nunchuk_x;
}

static double nunchuk_accely(){
  return nunchuk_y;
}

static double nunchuk_accelz(){
  return nunchuk_z;
}
 
