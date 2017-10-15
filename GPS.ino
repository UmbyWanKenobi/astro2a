

void PRINT_INFO()
{
  byte data_ora, // // Flag del dato richiesto: 0 per la data, 1 per UTC, 2 per l'ora locale, 3 per JDN, 4 per l'ora siderale locale
       lat_long; // Seleziona il dato richiesto 0 per la latitudine, 1 per la longitudine

  u8g.setPrintPos(1, 0);
  data_ora = 3;
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
   if (GPS.available( gpsSerial )) {
      fix = GPS.read();}
  if (lat_long == 0) {
    INFO.concat("Lat:");
    printDD_MMmmmm( fix.latitudeDMS, fix.latitudeDMS.NS() );
  } else {
    INFO.concat("Lon:");
    printDD_MMmmmm( fix.longitudeDMS, fix.longitudeDMS.NS() );
  }

  INFO.concat(DATA);
  return (INFO);


}

void printTime () {
  /*
  DATA = "";
    if (fix.valid.time) {
    if (fix.dateTime.hours < 10)
      DATA += "0";
    DATA += fix.dateTime.hours;
    DATA += ':';
    if (fix.dateTime.minutes < 10)
      DATA += "0" ;
    DATA += (fix.dateTime.minutes);
    DATA += ':';
    if (fix.dateTime.seconds < 10)
      DATA += "0";
    DATA += fix.dateTime.seconds;
  }
  return DATA;
*/
}

void printDate () {
  /*
  DATA = "";
  
  if (fix.valid.date) {
    if (fix.dateTime.date < 10)
      DATA += "0";
    DATA += fix.dateTime.date;
    DATA += '/';
    if (fix.dateTime.month < 10)
      DATA += "0";
    DATA += fix.dateTime.month;
    DATA += '/';
    DATA += fix.dateTime.full_year() ;
  }
  return DATA;
  Serial.println();
*/
}
void printDD_MMmmmm( DMS_t & dms, char hemisphere )
{
  
  DATA  = "";
  DATA += dms.degrees;
  DATA += "\xb0";
  if (dms.minutes < 10)
    DATA += "0";
  float minutes = dms.minutes;
  minutes += (dms.seconds_whole * 1000.0 + dms.seconds_frac) / (60.0 * 1000.0);
  DATA += minutes;
  DATA += hemisphere;
  return DATA;
}

