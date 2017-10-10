void init_GPS() {
  gpsSerial.begin(9600);
  gpsSerial.println( F("$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28") ); // RMC & GGA only
  gpsSerial.println( F("$PMTK220,1000*1F") ); // 1Hz update rate
  waitForFix();
}

void init_MPL3115A2 () {
  MPL.begin();
  MPL.setModeAltimeter(); // Measure quota above sea level in meters
  MPL.setModeBarometer(); // Measure pressione in Pascals from 20 to 110 kPa
  MPL.setOversampleRate(7); // Set Oversample to the recommended 128
  MPL.enableEventFlags(); // Enable all three pressione and temp event flags
}


void init_MPU() {
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  //delay(1000);
}


int init_RTC() {
  SPI.begin();
  RTC.begin();
  RTC.enableOscillator(true, true, 3);
  if (! RTC.isrunning()) {
    Serial.println( F("RTC is NOT running!"));
    Serial.print( F("Setting time to... "));
    Serial.print(__DATE__);
    Serial.print(' ');
    Serial.println(__TIME__);
    // following line sets the RTC to the date & time this sketch was compiled
    //RTC.adjust(DateTime(__DATE__, __TIME__));
  }

}


void init_12864() {
  if (u8g.getMode() == U8G_MODE_R3G3B2)        {
    u8g.setColorIndex(255);
  }
  else if (u8g.getMode() == U8G_MODE_GRAY2BIT) {
    u8g.setColorIndex(3);
  }
  else if (u8g.getMode() == U8G_MODE_BW)       {
    u8g.setColorIndex(1);
  }
  else if (u8g.getMode() == U8G_MODE_HICOLOR)  {
    u8g.setHiColorByRGB(255, 255, 255);
  }
}
