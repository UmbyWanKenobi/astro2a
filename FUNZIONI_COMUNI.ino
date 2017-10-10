void Split_into_dms( float angle, unsigned int* _deg, unsigned int* _min ) {
  float t;
  unsigned int d, m;
  float s;

  Serial.println(angle);
  if (angle < 0.0) {
    angle = - angle;
  }
  angle = GRADI_DA_RADIANTI(angle);
  //Serial.println(angle);
  d = (unsigned int)angle;
  // Serial.println(d);
  t = (angle - (float )d) * 60.0;
  //  Serial.println(t);
  m = (unsigned int)(t);


  if (m == 60) {
    m = 0;
    d++;
  }

  *_deg = d;
  *_min = m;

  //  Serial.println(_deg);
  Serial.println(angle);
}

float GRADI_DA_RADIANTI(float angolo) {
  float gradi;
  gradi = angolo * 180 / pi;
  return gradi;
}

void MESSAGGIO_MENU (char* _buf) {
  uint8_t h;
  u8g_uint_t w, d, e;
  w = u8g.getWidth();
  e = u8g.getHeight();

  u8g.setFont(u8g_font_6x12);

  h = u8g.getFontAscent() - u8g.getFontDescent();
  //char *_buffer = "Premi ESC per uscire";
  // if (ug8.getStrWidth(_buf)> e) {
  d = (w - u8g.getStrWidth(_buf)) / 2;
  u8g.setDefaultForegroundColor();

  u8g.drawBox(0, e - h + 1 , w, h);
  u8g.setDefaultBackgroundColor();

  u8g.drawStr(d, e - 1, _buf);

}


int GiorniAnno(int y, int m, int d) {
  int GiorniDelMese[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  if (y % 4  == 0) {                //
    if (y % 100 != 0) {             //
      GiorniDelMese[1] = 29;        //Calcolo
    }                               //
    else {                          // del
      if (y % 400 == 0) {           //
        GiorniDelMese[1] = 29;      // bisestile
      }                             //
    }                               //
  }                                 //

  int dy = 0;
  for (int i = 0; i < m - 1; i++) {
    dy += GiorniDelMese[i];
  }

  dy += d;
  return dy;                      // Giorni dall'inizio dell'annno
}



boolean IsDST() {
  if (mo < 3 || mo > 11) {
    return false;                 // Gennaio, Febbraio e Dicembre non hanno ora legale
  }
  if (mo > 3 && mo < 11) {
    return true;                  // da Aprile a Ottobre vige l'ora legale
  }
  int previousSunday = dy - dw;
  if (mo == 3) {
    return previousSunday >= 8;  // Trova l'ultima domenica di Marzo
  }
  return previousSunday <= 0;    // e l'ultima domenica di Ottobre per il salto
}
void waitForFix() {
  //uint8_t fixes = 0;
  uint16_t lastToggle = millis();
  digitalWrite( LED_GPS0, LOW );
  digitalWrite( LED_GPS1, LOW );
  do {
    if (GPS.available( gpsSerial )) {
      fix = GPS.read();
      //fixes++;
      //LED_GPS00 lampeggiante in attesa del fix
      if ((uint16_t) millis() - lastToggle > 500) {
        lastToggle += 500;
        digitalWrite( LED_GPS0, !digitalRead(LED_GPS0) );
      }
    }
  } while (!fix.valid.location);
  digitalWrite( LED_GPS0, LOW );
  digitalWrite( LED_GPS1, HIGH );

  GPS.overrun( false );                                           // we had to wait a while...
  UpdateMenu ();
} // waitForFix

