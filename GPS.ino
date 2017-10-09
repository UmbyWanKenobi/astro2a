

void PRINT_INFO()
{
  byte data_ora, // Seleziona il dato richiesto 0 per la data, 1 per l'ora, 2 per JDN
       lat_long; // Seleziona il dato richiesto 0 per la latitudine, 1 per la longitudine

  u8g.setPrintPos(1, 0);
  data_ora = 1;
  u8g.print(ReadTimeDate(data_ora));
 /* 
  u8g.setPrintPos(1, 8);
data_ora = 4;
  u8g.print(ReadTimeDate(data_ora));
 */
  u8g.setPrintPos(1, 8);
  lat_long = 0;
  u8g.print(ReadLatLong(lat_long));
  u8g.setPrintPos(67, 8);
  lat_long = 1;
  u8g.print(ReadLatLong(lat_long));

}
String ReadLatLong (byte lat_long) {
  String INFO;
  waitForFix();
  if (lat_long == 0) {
    INFO.concat("Lat:");
    printDD_MMmmmm( fix.latitudeDMS, fix.latitudeDMS.NS() );
  } else {
    INFO.concat("Lon:");
    printDD_MMmmmm( fix.longitudeDMS, fix.longitudeDMS.NS() );
  }

  INFO.concat(_buffer);
  return (INFO);


}

void printTime () {
  _buffer = "";
  // waitForFix();
  if (fix.valid.time) {
    if (fix.dateTime.hours < 10)
      _buffer += "0";
    _buffer += fix.dateTime.hours;
    _buffer += ':';
    if (fix.dateTime.minutes < 10)
      _buffer += "0" ;
    _buffer += (fix.dateTime.minutes);
    _buffer += ':';
    if (fix.dateTime.seconds < 10)
      _buffer += "0";
    _buffer += fix.dateTime.seconds;
  }
  return _buffer;

}

void printDate () {
  _buffer = "";
  
  if (fix.valid.date) {
    if (fix.dateTime.date < 10)
      _buffer += "0";
    _buffer += fix.dateTime.date;
    _buffer += '/';
    if (fix.dateTime.month < 10)
      _buffer += "0";
    _buffer += fix.dateTime.month;
    _buffer += '/';
    _buffer += fix.dateTime.full_year() ;
  }
  return _buffer;
  Serial.println();

}
void printDD_MMmmmm( DMS_t & dms, char hemisphere )
{
  
  _buffer  = "";
  _buffer += dms.degrees;
  _buffer += "\xb0";
  if (dms.minutes < 10)
    _buffer += "0";
  float minutes = dms.minutes;
  minutes += (dms.seconds_whole * 1000.0 + dms.seconds_frac) / (60.0 * 1000.0);
  _buffer += minutes;
  _buffer += hemisphere;
  return _buffer;
}
void waitForFix() {
 uint8_t fixes = 0;
  uint16_t lastToggle = millis();
    digitalWrite( LED_GPS, LOW );
  do {
    if (GPS.available( gpsSerial )) {
      fix = GPS.read();
      fixes++;
       // Slowly flash the LED until we get a fix
    if ((uint16_t) millis() - lastToggle > 500) {
      lastToggle += 500;
      digitalWrite( LED_GPS, !digitalRead(LED_GPS) );
    }
    }
  } while ((fixes < 2) && !fix.valid.location);
  digitalWrite( LED_GPS, LOW );

  GPS.overrun( false );                                           // we had to wait a while...



} // waitForFix
