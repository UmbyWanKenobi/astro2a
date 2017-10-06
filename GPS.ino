void init_GPS() {
  gpsSerial.begin(9600);
  gpsSerial.println( F("$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28") ); // RMC & GGA only
  gpsSerial.println( F("$PMTK220,1000*1F") ); // 1Hz update rate
  waitForFix();
}

void PRINT_INFO()
{
  byte data_ora, // Seleziona il dato richiesto 0 per la data, 1 per l'ora
       lat_long; // Seleziona il dato richiesto 0 per la latitudine, 1 per la longitudine
 
  u8g.setPrintPos(1, 0);
  data_ora = 1;
  u8g.print(ReadTimeDate(data_ora));
  
  u8g.setPrintPos(1, 8);
  lat_long = 0;
  u8g.print(ReadLatLong(lat_long));
  u8g.setPrintPos(67, 8);
  lat_long = 1;
  u8g.print(ReadLatLong(lat_long));
 
}
String ReadLatLong (byte lat_long){
  String INFO;
   waitForFix();
  if (lat_long == 0) {
    INFO.concat("Lat:");
  } else {
    INFO.concat("Lon:");
  }
 printDD_MMmmmm( fix.latitudeDMS, fix.latitudeDMS.NS() );
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

    /*
      _buffer += ('.');
      if (fix.dateTime_cs < 10)
      _buffer += "0";
      _buffer += fix.dateTime_cs;
    */
  }
  return _buffer;

}

void printDate () {
  _buffer = "";
  // waitForFix();
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
  // waitForFix();
  _buffer  = "";
  _buffer += dms.degrees;
  _buffer += "\xb0";
  if (dms.minutes < 10)
    _buffer += "0";
  float minutes = dms.minutes;
  minutes += (dms.seconds_whole * 1000.0 + dms.seconds_frac) / (60.0 * 1000.0);
  _buffer += minutes;
  // _buffer += " ";
  _buffer += hemisphere;
  return _buffer;
}
void waitForFix()
{
  uint8_t fixes = 0;

  do {
    if (GPS.available( gpsSerial )) {
      fix = GPS.read();
      fixes++;
    }
  } while ((fixes < 2) && !fix.valid.location);

} // waitForFix
