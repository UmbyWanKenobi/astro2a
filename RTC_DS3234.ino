
String ReadTimeDate(byte data_ora) {

  LMT();
  DateTime now = RTC.now();

  DATA = "";
  switch (data_ora) {
    case 0:
      if ( dy < 10 ) DATA.concat ( "0"  );
      DATA.concat(dy); // GIORNO
      DATA.concat("/") ;
      if ( mo < 10 ) DATA.concat ( "0"  );
      DATA.concat(mo);  //MESE
      DATA.concat("/") ;
      DATA.concat(yr); // ANNO
      return (DATA);
      break;
    case 1:
      DATA = "";
      DATA.concat("Locale: ") ;
      if ( hr < 10 ) DATA.concat ( "0"  );
      DATA.concat(hr); // ORA
      DATA.concat(":") ;
      if ( mn < 10 ) DATA.concat ( "0"  );
      DATA.concat(mn); //MINUTI
      DATA.concat(":") ;
      if ( se < 10 ) DATA.concat ( "0"  );
      DATA.concat(se); // SECONDI
      return (DATA);
      break;
    case 2:

      DATA = "";
      DATA.concat("UTC: ") ;
      if ( now.hour() < 10 ) DATA.concat ( "0"  );
      DATA.concat(now.hour()); // ORA
      DATA.concat(":") ;
      if ( now.minute() < 10 ) DATA.concat ( "0"  );
      DATA.concat(now.minute()); //MINUTI
      DATA.concat(":") ;
      if ( now.second() < 10 ) DATA.concat ( "0"  );
      DATA.concat(now.second()); // SECONDI
      return (DATA);
      break;
    case 3:
      DATA = "";
      DATA.concat("JD: ");
      DATA.concat(JD0());
      DATA.concat(".");
      DATA.concat( JD1() );
     spln (JD1());
     return (DATA);
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
String JD1() {
 char ccc [9];
unsigned long JD1 = (unsigned long)( (  UTC() + .5 ) * 100000.0f ) % 100000;
sprintf (ccc,"%05u",JD1);
return (String(ccc));
}

void LMT() {
  DateTime now = RTC.now();
  if ( IsDST() == true ) {
    DST = 1;
  } else {
    DST = 0;
  }
  hr = now.hour() + TZ + DST;              // Sommo il fuso orario e l'ora legale per l'ora locale
  while (hr >= 24.0) { hr -= 24.0; }       // accordo le 24 ore          
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
      fix = GPS.read();}        // calcolo dinamico sulla posizione assoluta GPS
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
  DATA = "";
  DATA.concat("Siderale: ") ;
  if ( dh < 10 ) DATA.concat ( "0"  );
  DATA.concat(dh); // ORA
  DATA.concat(":") ;
  if ( dm < 10 ) DATA.concat ( "0"  );
  DATA.concat(dm); //MINUTI
  DATA.concat(":") ;
  if ( ds < 10 ) DATA.concat ( "0"  );
  DATA.concat(ds); // SECONDI
  return (DATA);
}


