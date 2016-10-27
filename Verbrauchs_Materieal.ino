/* Schalterabfrage anzeigen in LCD
lcd.setCursor(1, 0); //Start at character 2 on line 0
lcd.print(Schalter1St);
lcd.print(Schalter2St);
lcd.print(Schalter3St);
lcd.print(Schalter4St);
lcd.print(Schalter5St);
lcd.print(Schalter6St);
lcd.print(Schalter7St);
lcd.print(Schalter8St);
lcd.print(Schalter9St);
lcd.print(Schalter10St);
*/
//Schalter1St = digitalRead(Schalter1);
//Schalter2St = digitalRead(Schalter2);
//Schalter3St = digitalRead(Schalter3);
//Schalter4St = digitalRead(Schalter4);
//Schalter5St = digitalRead(Schalter5);
//Schalter6St = digitalRead(Schalter6);
//Schalter7St = digitalRead(Schalter7);
//Schalter8St = digitalRead(Schalter8);
//Schalter9St = digitalRead(Schalter9);
//Schalter10St = digitalRead(Schalter10);

//ATC App
  //Daten An die Senden 
    // Serial1.println("<Alrm00"); Handy gibt Arlarm 
    // Serial1.println("<Imgs02:1"); Bild Nr 2 wird geändert 
    // Serial.println("<TtoS00:Hello world"); Handy gibt Sprachbefehl über Text to Sprache 
    // Serial.println("<Butn05:1")  Knopf bekomt andere Stellung
    // Serial.println (("<Text00:Temp1: " + sSample); ) Text eines Textfeldes wird geändern} 




////Blauzahnausgabe 
//Serial1.println("------------------------------------------------------------");
//phasennameBT();
//Serial1.print("es ist  ");
//Serial1.print(rtc.getTimeStr());
//Serial1.println(" Uhr");
////Zeile 
//Serial1.print("Ziel Brautopf  ");
//Serial1.print(BTemplow)               ;
//Serial1.print(" C - ")                ;
//Serial1.print(BTempHigh);
//Serial1.print(" C Aktuelle  ")     ; 
//Serial1.print(sensors.getTempCByIndex(0))                ;   //Platzhalter für Wert
//Serial1.println(" C")                 ;
//// Zeile
//Serial1.print("Ziel Kocher     ");
//Serial1.print(WTemplow)               ;
//Serial1.print(" C - ")                ;
//Serial1.print(WTempHigh)              ;
//Serial1.print(" C Aktuelle  ")     ; 
//Serial1.print(sensors.getTempCByIndex(1))  ;
//Serial1.println(" C")                 ;
//// Zeile              
//Serial1.print("Zeit seit Einschalten  ");
//Serial1.print(gesamtzeit) ;
//if (zeittimer1 > 0){
//Serial1.print(" Min,Timer 1= ");
//Serial1.print (zeittimer1)              ;
//Serial1.println(" Min")                  ;}
//else {
//Serial1.println(" Min ");}
//// Zeile 
//Serial1.print("Zeit Seit Beginn Phase ");
//Serial1.print(gesamtzeit-starttimer)    ;
//if (zeittimer2 > 0){
//Serial1.print(" Min,Timer 2= ");
//Serial1.print (zeittimer2)              ;
//Serial1.println(" Min")                  ;}
//else {
//Serial1.println(" Min ");}
//// Zeile  
//Serial1.print(" Aktuelle Temp Sensor 3 ")     ; 
//Serial1.print(sensors.getTempCByIndex(2))  ;
//Serial1.println(" C")                 ; 
//if (akLiter > 0){
//  Serial1.print("Füllmenge ")     ; 
//Serial1.print(akLiter)  ;
//Serial1.println(" L") ; }
//if (akStammwuerze > 0){
//  Serial1.print("Stammwuerze ") ; 
//Serial1.print(akLiter)  ;
//Serial1.println(" grad");}
   //ende Blauzahn senden

   //  if (Bittimer == 1) { //  der für die Minuten zählung da ist
//
//    if (second() == Sekundetimer + 1) {
//      Bittimer = 0;
//      digitalWrite(LEDW, LOW);
//    }
//    if (second() == 59) {
//      if (second() == 1) {
//        Bittimer = 0;
//        digitalWrite(LEDW, LOW);
//      }
//    }
//  }
//  //timer ene


  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  //  Serial.print("Requesting temperatures...");
  //  sensors.requestTemperatures(); // Send the command to get temperatures
  //  Serial.println("DONE");
//  if (operationB > 0) {
//
//    if (second() ==  24 || second() ==  54 )Temperaturen();
//    if (second() ==  18 || second() ==  48 )LiterStammwuertze ();
//    if (second() ==  12 || second() ==  42 )Raumuhr();
//    if (second() ==  06 || second() ==  36 )Schaltzeit();
//    if (second() ==  00 || second() ==  30 )PhaseBesttemp();  }


//void phasennameCOM() {
//  switch (operation0 + operation1 + operation2 + operation3 + operation4 + operation5 + operation6 + operation7 + operation8 + operation9 + operation10) {
//    case 1:    Serial.print("Einmaischen          ");    break;
//    case 2:    Serial.print("Eiweisrast           ");    break;
//    case 3:    Serial.print("Maltoserast          ");    break;
//    case 4:    Serial.print("Verzuckerungsrast    ");    break;
//    case 5:    Serial.print("Laeutern/Ausschwänzen");    break;
//    case 6:    Serial.print("Würzekochen          ");    break;
//    case 7:    Serial.print("Würzekühlen          ");    break;
//    case 8:    Serial.print("Vergehrung           ");    break;
//    case 9:    Serial.print("Abfüllen             ");    break;
//    case 10:   Serial.print("Lagern               ");    break;
//    default:   Serial.print("Start                ");    break;

