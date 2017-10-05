
int init_RTC(){ 
    pinMode(cs,OUTPUT); // chip select
    // start the SPI library:
    SPI.begin();
    SPI.setBitOrder(MSBFIRST); 
    SPI.setDataMode(SPI_MODE1); // both mode 1 & 3 should work 
    //set control register 
    digitalWrite(cs, LOW);  
    SPI.transfer(0x8E);
   // SPI.transfer(0x60); //60= disable Osciallator and Battery SQ wave @1hz, temp compensation, Alarms disabled
    digitalWrite(cs, HIGH);
    delay(10);
}

int SetTimeDate(int d, int mo, int y, int h, int mi, int s){ 
  int TimeDate [7]={s,mi,h,0,d,mo,y};
  for(int i=0; i<=6;i++){
    if(i==3)
      i++;
    int b= TimeDate[i]/10;
    int a= TimeDate[i]-b*10;
    if(i==2){
      if (b==2)
        b=B00000010;
      else if (b==1)
        b=B00000001;
    } 
    TimeDate[i]= a+(b<<4);
      
    digitalWrite(cs, LOW);
    SPI.transfer(i+0x80); 
    SPI.transfer(TimeDate[i]);        
    digitalWrite(cs, HIGH);
  }
}


String ReadTimeDate(byte* data_ora){
  String DATA, ORA;
  int TimeDate [7]; //second,minute,hour,null,day,month,year    
  for(int i=0; i<=6;i++){
    if(i==3)
      i++;
    digitalWrite(cs, LOW);
    SPI.transfer(i+0x00); 
    unsigned int n = SPI.transfer(0x00);        
    digitalWrite(cs, HIGH);
    int a=n & B00001111;    
    if(i==2){ 
      int b=(n & B00110000)>>4; //24 hour mode
      if(b==B00000010)
        b=20;        
      else if(b==B00000001)
        b=10;
      TimeDate[i]=a+b;
    }
    else if(i==4){
      int b=(n & B00110000)>>4;
      TimeDate[i]=a+b*10;
    }
    else if(i==5){
      int b=(n & B00010000)>>4;
      TimeDate[i]=a+b*10;
    }
    else if(i==6){
      int b=(n & B11110000)>>4;
      TimeDate[i]=a+b*10;
    }
    else{ 
      int b=(n & B01110000)>>4;
      TimeDate[i]=a+b*10; 
      }
  }
  if ( TimeDate[4] < 10 ) DATA.concat ( "0"  );
  DATA.concat(TimeDate[4]);
  DATA.concat("/") ;
  if ( TimeDate[5] < 10 ) DATA.concat ( "0"  );
  DATA.concat(TimeDate[5]);
  DATA.concat("/") ;
  if ( TimeDate[6] < 10 ) DATA.concat ( "0"  );
  DATA.concat(TimeDate[6]);
  ORA.concat("UTC: ") ;
  if ( TimeDate[2] < 10 ) ORA.concat ( "0"  );
  ORA.concat(TimeDate[2]);
  ORA.concat(":") ;
  if ( TimeDate[1] < 10 ) ORA.concat ( "0"  );
  ORA.concat(TimeDate[1]);
  ORA.concat(":") ;
  if ( TimeDate[0] < 10 ) ORA.concat ( "0"  );
  ORA.concat(TimeDate[0]);
  Serial.print (*data_ora);
  if (data_ora == 0 ) {
    return(DATA);
  } else {
  return (ORA);
}
}
