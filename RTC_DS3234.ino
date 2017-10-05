
int init_RTC() {
  SPI.begin();
  RTC.begin();
  RTC.enableOscillator(true, true, 3);
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    Serial.print("Setting time to... ");
    Serial.print(__DATE__);
    Serial.print(' ');
    Serial.println(__TIME__);
    // following line sets the RTC to the date & time this sketch was compiled
    //RTC.adjust(DateTime(__DATE__, __TIME__));
  }

}

String ReadTimeDate(byte data_ora) {
  const int len = 32;
  static char buf[len];

  DateTime now = RTC.now();

  Serial.println(now.toString(buf, len));

  Serial.print(" since midnight 1/1/1970 = ");
  Serial.print(now.unixtime());
  Serial.print("s = ");
  Serial.print(now.unixtime() / 86400L);
  Serial.println("d");

  // calculate a date which is 7 days and 30 seconds into the future
  //DateTime future (now.unixtime() + 7 * 86400L + 30 );

  //  Serial.print(" now + 7d + 30s: ");
  //Serial.println(future.toString(buf,len));


  Serial.print(" ");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();



  Serial.println();

  String DATA, ORA, JD;
  if ( now.day() < 10 ) DATA.concat ( "0"  );
  DATA.concat(now.day()); // GIORNO
  DATA.concat("/") ;
  if ( now.month() < 10 ) DATA.concat ( "0"  );
  DATA.concat(now.month());  //MESE
  DATA.concat("/") ;
  if ( now.year() < 10 ) DATA.concat ( "0"  );
  DATA.concat(now.year()); // ANNO


  ORA.concat("UTC: ") ;
  if ( now.hour() < 10 ) ORA.concat ( "0"  );
  ORA.concat(now.hour()); // ORA
  ORA.concat(":") ;
  if ( now.minute() < 10 ) ORA.concat ( "0"  );
  ORA.concat(now.minute()); //MINUTI
  ORA.concat(":") ;
  if ( now.second() < 10 ) ORA.concat ( "0"  );
  ORA.concat(now.second()); // SECONDI

    switch (data_ora) {
    case 0:
    return (DATA);
    break;
    case 1:
    return (ORA);
    break;
    case 2:
    return (JD);
    break;
    }

  /*
    const int len = 32;
    static char buf[len];
    /*
    char Y = now.year();
    char M = now.month();
    char D = now.day();
    char H = now.hour();
    char Mn= now.minute();
    char S = now.second();

    DateTime now = RTC.now();

    Serial.println(now.toString(buf, len));

    Serial.print(" since midnight 1/1/1970 = ");
    Serial.print(now.unixtime());
    Serial.print("s = ");
    Serial.print(now.unixtime() / 86400L);
    Serial.println("d");

    // calculate a date which is 7 days and 30 seconds into the future
    //DateTime future (now.unixtime() + 7 * 86400L + 30 );

    Serial.print(" now + 7d + 30s: ");
    //  Serial.println(future.toString(buf, len));


    Serial.print(" ");
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    /*


    ORA.concat("UTC: ") ;
    if ( H < 10 ) ORA.concat ( "0"  );
    ORA.concat(H); // ORA
    ORA.concat(":") ;
    if ( Mn < 10 ) ORA.concat ( "0"  );
    ORA.concat(Mn); //MINUTI
    ORA.concat(":") ;
    if ( S < 10 ) ORA.concat ( "0"  );
    ORA.concat(S); // SECONDI
    /*
    if (M<3) {M+=12; Y-=1;}
    float JDN= ((2 - Y/100) + Y/400) + D + (365.25 * (Y + 4716)) + (30.6001 * (M + 1)) - 1524.5;

    float d = JDN - 2451545.0;
    float T = d /36525;

    H = H + ((float)(Mn/60)) + ((float)(S/3600));
    //float T3 = H * 0.00273790935;
    ///float T+=H;
    float GMST =  24110.54841 + 864184.812866 * T + 0.093104 * (T*T) - 0.0000062 * (T*T*T);
    Serial.println(JDN);
    Serial.println (GMST);


    if (data_ora == 0 ) {
    return(DATA);
    } else {
    return (ORA);
  */

}
