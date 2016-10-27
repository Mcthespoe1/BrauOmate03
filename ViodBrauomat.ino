//Funktion die  Festlegt das Die LED bei Bestimmten Temperaturen arbeiten
// Blau zu Kalt ,Grün richtg , Rot zu Warm
void LEDTEMP() {
  if ( (Brautopftemp >= BTemplow) && (Brautopftemp <= BTempHigh) ) {
    digitalWrite(LEDGR1, HIGH);
    Serial1.println("<Imgs15:1");
    if (timer == 0){
    starttimer = gesamtzeit ;     //Timer Setzen
    Serial1.println("<Butn01:1"); // Knopf bekomt andere Stellung
    if (zeittimer1 > 0) timer=1;
    if  (zeittimer2 > 0 )  timer=2;
    }}
  else  digitalWrite(LEDGR1, LOW);
  if (  Brautopftemp < BTemplow ) {
    digitalWrite(LEDBL1, HIGH);
    Serial1.println("<Imgs15:1");
  }
  else   digitalWrite(LEDBL1, LOW);
  if (  Brautopftemp > BTempHigh ) {
    digitalWrite(LEDRT1, HIGH);
    Serial1.println("<Imgs15:1");
  }
  else  digitalWrite(LEDRT1, LOW);

  if ( (Wasserkochertemp >= WTemplow) && (Wasserkochertemp <= WTempHigh) ) {
    digitalWrite(LEDGR2, HIGH);
    Serial1.println("<Imgs17:1");
  }
  else  digitalWrite(LEDGR2, LOW);
  if (  Wasserkochertemp < WTemplow ) {
    digitalWrite(LEDBL2, HIGH);
    Serial1.println("<Imgs17:0");
  }
  else digitalWrite(LEDBL2, LOW);
  if (  Wasserkochertemp > WTempHigh ) {
    digitalWrite(LEDRT2, HIGH);
    Serial1.println("<Imgs17:2");
  }
  else digitalWrite(LEDRT2, LOW);
}

// Läst einfach alle LED mal durch blinken
void LEDTEST() {
  digitalWrite(LEDBL1, HIGH);
  delay(50);
  digitalWrite(LEDGR1, HIGH);
  delay(50);
  digitalWrite(LEDBL1, LOW);
  delay(50);
  digitalWrite(LEDRT1, HIGH);
  delay(50);
  digitalWrite(LEDGR1, LOW);
  delay(50);
  digitalWrite(LEDBL2, HIGH);
  delay(50);
  digitalWrite(LEDRT1, LOW);
  delay(50);
  digitalWrite(LEDGR2, HIGH);
  delay(50);
  digitalWrite(LEDBL2, LOW);
  delay(50);
  digitalWrite(LEDRT2, HIGH);
  delay(50);
  digitalWrite(LEDGR2, LOW);
  delay(50);
  digitalWrite(LEDGL, HIGH);
  delay(50);
  digitalWrite(LEDRT2, LOW);
  delay(50);
  digitalWrite(LEDW, HIGH);
  delay(50);
  digitalWrite(LEDGL, LOW);
  delay(50);
  digitalWrite(LEDW, LOW);
}



 

//  }
//}

void phasenname () {
  switch (operationB) {
    case 1:    SPhasename =  ("Einmaischen");    break;
    case 2:    SPhasename =  ("Eiweisrast");    break;
    case 3:    SPhasename =  ("Maltoserast");    break;
    case 4:    SPhasename =  ("Verzuckerung");    break;
    case 5:    SPhasename =  ("Laeutern");    break;
    case 6:    SPhasename =  ("Kochen");    break;
    case 7:    SPhasename =  ("Kuehlung");    break;
    case 8:    SPhasename =  ("Vergehrung");    break;
    case 9:    SPhasename =  ("Abfuellen");    break;
    case 10:   SPhasename =  ("Lagerung");    break;
    default:   SPhasename =  ("Start");    break;
  }
}
// }
//LCD Display
void Raumuhr()   {// LCD Uhr und Raumtemperatur
  lcd.setCursor(0, 0);
  lcd.print("Uhrzeit ");
  lcd.print(hour());
  lcd.print(":");
  lcd.print(minute());
  lcd.print("      ");
  lcd.setCursor(0, 1);
  lcd.print("Raum Temp  ");
  lcd.print(RTC.temperature());
}
void Schaltzeit() { // LCD Zeit seit Anfang des Schalten
  lcd.setCursor(0, 0);
  lcd.print("Zeit seit Beginn ");
  lcd.setCursor(0, 1);
  lcd.print(gesamtzeit - starttimer);
  lcd.print(" Minuten         ");
}
void PhaseBesttemp() {
  lcd.setCursor(0, 0);
  lcd.print(SPhasename+"     ");
  lcd.setCursor(0, 1);
  lcd.print("Temp Best");
  lcd.print(BTemplow);
  lcd.print("-");
  lcd.print(BTempHigh);
  lcd.print("c   ");
}
void  Temperaturen() {
  lcd.setCursor(0, 0);
  lcd.print(Brautopftemp);
  lcd.print("C BrauTemp    ");
  lcd.setCursor(0, 1);
  lcd.print(Wasserkochertemp);
  lcd.print(" C KocherTemp  ");
}
void  LiterStammwuertze () {
  lcd.setCursor(0, 0);
  lcd.print(akLiter);
  lcd.print(" Liter         ");

  lcd.setCursor(0, 1);
  lcd.print(akStammwuerze);
  lcd.print(" Stammwuertze  ");
}





//Voids für die Temperatur sensoren
void printTemperature(DeviceAddress deviceAddress) {
  // method 1 - slower
  //Serial.print("Temp C: ");
  //Serial.print(sensors.getTempC(deviceAddress));
  //Serial.print(" Temp F: ");
  //Serial.print(sensors.getTempF(deviceAddress)); // Makes a second call to getTempC and then converts to Fahrenheit

  // method 2 - faster
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.print(tempC);
  //  Serial.print(" Temp F: ");
  //  Serial.print(DallasTemperature::toFahrenheit(tempC)); // Converts tempC to Fahrenheit
}
void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++)
  { if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

void NextPhase() {
  operationB=operationB+1;
  phasenname ();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(SPhasename);
  lcd.setCursor(0, 1);
  lcd.print("Beginnt        ");
  
  Serial1.println("<TtoS01:"+SPhasename+" hat begonnen ");
  LEDTEST();
  timer =0;
  Timerstat ='B' ;
}
void LastPhase(){
   ZuruckBIT = ZuruckBIT + 1;
      Serial.print (ZuruckBIT);
      if  (ZuruckBIT == 30 ) {
        operationA = operationA-1;
        operationB = operationB-2;
        lcd.setCursor(0, 0);
        phasenname ();
        lcd.print("Eins zurück bitte ");
        Serial.print ("Eins Phase zurück bitte   ");
        Serial1.println("<TtoS01:System wurde zurück gesetzt");
      }  }
void digitalClockDisplay(void)
{
    // digital clock display of the time
    Serial.print(hour());
    printDigits(minute());
    printDigits(second());
    Serial.print(' ');
    Serial.print(day());
    Serial.print(' ');
    Serial.print(month());
    Serial.print(' ');
    Serial.print(year()); 
    Serial.println(); 
}

void printDigits(int digits)
{
    // utility function for digital clock display: prints preceding colon and leading 0
    Serial.print(':');
    if(digits < 10)
        Serial.print('0');
    Serial.print(digits);
}
