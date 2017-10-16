
String ReadTimeDate(byte data_ora) {

  LMT();
  DateTime now = RTC.now();

  switch (data_ora) {
    case 0: //   DATA
      sprintf(ccc, "%02d/%02d/%04d", dy, mo, yr);
      return (ccc);
      break;
    case 1:  // ORA LOCALE
      sprintf(ccc, "LMT: %02d:%02d:%02d", hr, mn, se);
      return (ccc);
      break;
    case 2: //  ORA UTC
      sprintf(ccc, "UTC: %02d:%02d:%02d", (int)(now.hour()), (int)(now.minute()), (int)(now.second()) );
      return (ccc);
      break;
    case 3:  // JULIAN DAY
      //    sp ("JD: "); spln(JD1());
      sprintf (ccc, "JDf %7lu.%05lu", JD0(), JD1());
      spln (ccc);
      return (ccc);
      break;
    case 4:
      return (OraSiderale());
      break;

  }
}
unsigned long JD0 () {
  DateTime now = RTC.now();
  return (now.unixtime() / 86400 ) + JDunix + UTC() ;
}

float UTC() {
  DateTime now = RTC.now();
  return ((float)( now.hour() / 24.0f ) + (float)( now.minute() / 1440.0f ) + (float)( now.second() / 86400.0f ) );

}
unsigned long JD1() {
  return (unsigned long)( ( UTC() + .5 ) * 100000.0f ) % 100000;
}

void LMT() {
  DateTime now = RTC.now();
  if ( IsDST() == true ) {
    DST = 1;
  } else {
    DST = 0;
  }
  hr = now.hour() + TZ + DST;              // Sommo il fuso orario e l'ora legale per l'ora locale
  while (hr >= 24.0) {
    hr -= 24.0;  // accordo le 24 ore
  }
  mn = now.minute();
  se = now.second();
  yr = now.year();
  mo = now.month();
  dy = now.day();
  dw = now.dayOfWeek();
  uxt = now.unixtime();
}


String OraSiderale() {     // Basato su algoritmo di "The United States Naval Observatory (USNO)"
  // http://aa.usno.navy.mil/faq/docs/GAST.php
  if (GPS.available( gpsSerial )) {
    fix = GPS.read();
  }        // calcolo dinamico sulla posizione assoluta GPS
  DateTime now = RTC.now();                          // current time

  // int ny = GiorniAnno(now.year(), now.month(), now.day());

  // calculate GST and Local Sidereal Time (LST)
  GST = Cost_G + (dc * ((now.unixtime() / 86400L) + .5 )) + (un_sid * 24 * UTC() ); // Tempo siderale di Greenwich in formato decimale
  LST = GST + 24.0 + (float)(fix.longitude() / 360 * giorno_siderale); // Tempo siderale locale stabilito dal GPS in formato decimale
  while (LST >= 24.0 ) {
    LST -= 24.0;  // accordo le 24 ore
  }
  dh = int( LST );                                           // ORA LST
  dm = int( (LST - (float)dh) * 60.0 );                      // MINUTI LST
  ds = int( (LST - (float)dh - (float)dm / 60.0) * 3600.0 ); // SECONDI LST
  sprintf(ccc, "LST: %02d:%02d:%02d", dh, dm, ds);
  return (ccc);
}


