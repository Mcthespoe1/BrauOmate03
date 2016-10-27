#include <Wire.h>               //Für den LCD Verteiler 
#include <LiquidCrystal_I2C.h>  //LCD Bibliothek
#include <SPI.h>                //
#include <SD.h>                 // SD Karte 
#include <DS3232RTC.h>     //Echtzeit Uhr  //http://github.com/JChristensen/DS3232RTC
#include <Time.h>         //http://www.arduino.cc/playground/Code/Time  
#include <Wire.h>         //http://arduino.cc/en/Reference/Wire (included with Arduino IDE

#include <TimeLib.h>
char weekDay[][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

#include <OneWire.h>            // Ein Kabel
#include <DallasTemperature.h>  // Tempsensor
#include <Keypad.h>             // Tastefeld 3*4 12 Tasten 
//Keypad daten
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {8, 7, 6, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {10, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
boolean blink = false;
boolean ledPin_state;


//I2C Module
//  LCD               addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); //16 zeichen 2 Reihen
//Echtzeit Uhr

//SD
const int chipSelect = 4;
File dataFile;
File dataFile2;
// Tempsendor
#define ONE_WIRE_BUS 12
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
// arrays to hold device address
DeviceAddress insideThermometer;

//Schalter und dazugehörige speicher


int Schalter1 = 53;
int Schalter2 = 33;
int Schalter3 = 49;
int Schalter4 = 47;
int Schalter5 = 45;
int Schalter6 = 43;
int Schalter7 = 41;
int Schalter8 = 39;
int Schalter9 = 37;
int Schalter10 = 35;
int operationA = 0;
int operationB = 0;
//LED
int LEDBL1 = 34; //Blau
int LEDGR1 = 48; //Grün
int LEDRT1 = 46; //Rot
int LEDBL2 = 44; //Blau
int LEDGR2 = 42; //Grün
int LEDRT2 = 40; //Rot
int LEDGL = 38;  //Gelb
int LEDW  = 36;  //Weiß
//Pieper
int Pieper = 11;
//Zeit Variablen
int timer = 0;
char Timerstat = 0 ;
int Bittimer = 0;     //   der Gesamtzeitrechner
int Bitdata = 0;       // Wenn der Bit 1 ist soll eine Fehlermeldung Laufen 
int starttimer = 0;   // gibt an wann ein vorgang gestartet wird
int tempzeit = 0 ;    // Zeit beginnt wenn Tem ereicht
int tempzeitbit = 0;
int Starttemp = 0;
int zeittimer1 = 0;    //gibt an wie lange ein Vorgang dauern soll
int zeittimer2 = 0 ;   //
int endetimer = 0;
long gesamtzeit = 0; //rechnet jede minute weiter immer wenn eine Sekunde der Uhr anzeigt

int ZuruckBIT = 0;    // wenn es rückwärts gehen soll rechnet er einige Vorgänge Hoch um dann ein Phase zurück zu springen 
//für Blink without
unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 500;           // interval at which to blink (milliseconds)
int ledState = LOW;         // lass Blinken 
// Temperatur Variablen
int BTemplow = 0 ;            // Mindest Temperatur Maische
int BTempHigh = 0 ;           // Max Temperatur Maische
float Brautopftemp = 0;       // Aktuelle Temperatur Maische
int WTemplow = 0 ;            // Mindest Temperatur Kocher
int WTempHigh = 0 ;           // Max Temperatur Kocher
float Wasserkochertemp = 0;   // Aktuelle Temperatur Kocher
// Sonstige angaben
int akLiter = 0;              // Wieviele Liter Sind Im Brautopf 
int akStammwuerze = 0;        // wieviel Stamwürtze hat die Maische 
char key;                     // Speicher fürs Nummernfeld 
char btchar;                  // Speicher für Bluetooth 
String SPhasename = "";
//Blauzahnausgabe


void setup() {



  // Schalter                       Für Phasen des Brauens
  pinMode (Schalter1, INPUT);   //  Einmaischen 
  pinMode (Schalter2, INPUT);   //  Eiweisrast 
  pinMode (Schalter3, INPUT);   //  Maltoserast 
  pinMode (Schalter4, INPUT);   //  Verzuckerung 
  pinMode (Schalter5, INPUT);   //  Laeutern 
  pinMode (Schalter6, INPUT);   //  Kochen 
  pinMode (Schalter7, INPUT);   //  Kuehlung 
  pinMode (Schalter8, INPUT);   //  Vergehrung 
  pinMode (Schalter9, INPUT);   //  Abfuellen 
  pinMode (Schalter10, INPUT);  //  Lagerung 
  //LED
  pinMode(LEDRT1, OUTPUT);      // LED  Rot       Brautopf      zu Warm
  pinMode(LEDGR1, OUTPUT);      // LED  Grün      Brautopf      richtig
  pinMode(LEDBL1, OUTPUT);      // LED  Blau      Brautopf      zu Kalt 
  pinMode(LEDRT2, OUTPUT);      // LED  Rot       Wasserkocher  zu Warm
  pinMode(LEDGR2, OUTPUT);      // LED  Grün      Wasserkocher  richtig 
  pinMode(LEDBL2, OUTPUT);      // LED  Blau      Wasserkocher  zu Kalt 
  pinMode(LEDGL, OUTPUT);       // LED  Gelb      Für Fehlermeldungen 
  pinMode(LEDW, OUTPUT);        // LED  Weiss
 
  pinMode(SS, OUTPUT);          //SD  chip select pin
  pinMode(Pieper, OUTPUT);
  Serial.begin(9600);           // PC Monitor
  Serial1.begin(9600);          // Blauzahn monitor
  setSyncProvider(RTC.get);     // the function to get the time from the RTC
  sensors.begin();              // Digital Termometer
  lcd.begin(20, 4);             // LCD display MIt 4 Reihen a 20 felder  
 



  // Geräte am Kabel der Sensoren
  Serial.print("Suche Thermometer ...");

  Serial.print("Ingesamt  ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" gefunden .");

  // report parasite power requirements
  Serial.print("Parasite power is: ");
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");
  if (!sensors.getAddress(insideThermometer, 0)) Serial.println("Unable to find address for Device 0");

  if (!oneWire.search(insideThermometer)) {
    Serial.println("Unable to find address for insideThermometer");
    lcd.setCursor(0, 0);
    lcd.print("Thermometer Fehler" );
  }
  else {
    lcd.setCursor(0, 0);
    lcd.print("Thermometer " );
    lcd.print (sensors.getDeviceCount(), DEC);

  }
  lcd.setCursor(0, 1);
  if (timeStatus() != timeSet) {

    lcd.print ("RTC Hat einen Fehler ");
  }
  else
    lcd.print("RTC Hat die Zeit ");
  // show the addresses we found on the bus
  Serial.print("Device 0 Address: ");
  printAddress(insideThermometer);
  Serial.println();

  // set the resolution to 9 bit (Each Dallas/Maxim device is capable of several different resolutions)
  sensors.setResolution(insideThermometer, 9);

  Serial.print("Device 0 Resolution: ");
  Serial.print(sensors.getResolution(insideThermometer), DEC);
  Serial.println();





  
  Bittimer = minute();


  //SD Karte Starten
  lcd.setCursor(0, 2);
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    lcd.setCursor(0, 2);
    lcd.print("SD Karte Fehler" );

    // don't do anything more:
    //while (1) ;
  }
  else {
    lcd.setCursor(0, 2);
    lcd.print("SD Karte OK " );
    Serial.println("SDcard initialized.");
    Serial1.println("SDcard initialized.");

  }
  lcd.setCursor(0, 3);
  lcd.print("LED Test" );
  LEDTEST();
  delay (2000);
 

  // Open up the file we're going to log to!
  dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (! dataFile) {
    Serial.println("error opening datalog.txt");
    // Wait forever since we cant write data
    //while (1) ;
  }
  dataFile2 = SD.open("datalog2.txt", FILE_WRITE);
  if (! dataFile2) {
    Serial.println("error opening datalog2.txt");
    // Wait forever since we cant write data
    //while (1) ;
  }
  //STarte Protokoll
  dataFile2.print(" Startzeit des BrauOmat ");
  //Startwerte der Temperatur anzeige
  BTemplow = 10;    // Mindest Temperatur Topf
  BTempHigh = 25;   // Max Temperatur Topf
  WTemplow = 55 ;   // Mindest Temperatur Kocher
  WTempHigh = 70 ;  // Max Temperatur Kocher
  // initialize the lcd for 16 chars 2 lines and turn on backlight
  lcd.clear();
  lcd.setCursor(2, 1); //Start at character 2 on line 0
  lcd.print("Willkommen beim");
  lcd.setCursor(3, 2);
  lcd.print(" BrauOmat2016   ");
  lcd.setCursor(3, 3);
  lcd.print("   v 0.2         ");
  Serial1.println("<TtoS01:einen freundlichen guten Tag wünscht ihr BrauOMate 2016 viel Spass beim brauen  ");
  delay(3000);
  lcd.clear();

}// ende Setup

void loop() {
  //Temp sensor auf der Uhr = Serial.print(rtc.getTemp());
 
  // Blink without
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // Speicher die zeit seid letztem Speichern
    previousMillis = currentMillis;

    //Blauzahn

    if ( Bitdata == 1) {
      if (ledState == LOW) {
        ledState = HIGH;
        lcd.setCursor(0, 0);
        lcd.print("SD Fehler" );
      }

      else {
        ledState = LOW;
        lcd.setCursor(0, 0);
        lcd.print("         " );
      }}
    


    // don't do anything more:
    //while (1) ;
  
  else {
    lcd.setCursor(0, 0);
    lcd.print("SD  OK" );
    ledState = LOW;
  }

  digitalWrite(LEDGL, ledState);
  
}// Ende Blink

if (Serial1.available() > 0) {
  // read the incoming byte:
  akLiter = akLiter + Serial1.readString().toInt();

}//Ende Lieter Schreiben
sensors.requestTemperatures();
Brautopftemp = sensors.getTempCByIndex(0); //Blau
Wasserkochertemp = sensors.getTempCByIndex(1); // Grün

LEDTEMP();


//Timer
if (Serial.available())
{
  btchar = Serial.read();
}
if (btchar == 'b') Timerstat = 'b';
if (key == '*') Timerstat = 'b';


if  (Timerstat == 'B') {
  if (timer > 0) {
    if (gesamtzeit - starttimer == zeittimer1) {
      digitalWrite(LEDGL, HIGH);
      analogWrite(Pieper, 120);
      LEDTEST();
      analogWrite(Pieper, 60);
      LEDTEST();
      analogWrite(Pieper, 20);
      LEDTEST();
      digitalWrite(Pieper, LOW);
      Serial1.println("<TtoS01:Die Zeit ist abgelaufen Bitte weiter schalten ");
    }
    else {
      digitalWrite(LEDGL, LOW);
      digitalWrite(Pieper, LOW);
    }
    if (timer > 1) {
      if (gesamtzeit - starttimer == zeittimer2) {
        digitalWrite(LEDGL, HIGH);
        analogWrite(Pieper, 120);
        LEDTEST();
        analogWrite(Pieper, 60);
        LEDTEST();
        analogWrite(Pieper, 20);
        LEDTEST();
        digitalWrite(Pieper, LOW);
        Serial1.println("<TtoS01:Die Zeit ist abgelaufen Bitte weiter schalten ");
      }
      else {
        digitalWrite(LEDGL, LOW);
        digitalWrite(Pieper, LOW);
      }
    }
  }
}

//Sachen senden an Bluetooth

Serial1.println("<Text04: " + SPhasename + " ");
String SBrautopftemp;
SBrautopftemp = String(Brautopftemp);
Serial1.println("<Text00:Brautopf " + SBrautopftemp + " C");
String SWasserkochertemp;
SWasserkochertemp = String(Wasserkochertemp);
Serial1.println("<Text01:Kocher " + SWasserkochertemp + " C");
String SakLiter;
SakLiter = String(akLiter);
Serial1.println("<Text02:Liter " + SakLiter + " L");
String SakStammwuerze;
SakStammwuerze = String(akStammwuerze);
Serial1.println("<Text03:Stammwürtze " + SakStammwuerze + " ");
String Stringeins ;
String Stringzwei ;
String Stringdrei ;
Stringeins = String (BTemplow);
Stringzwei = String (BTempHigh);
Serial1.println("<Text05:BestTemp " + Stringeins + "-" + Stringzwei);
Stringeins = String (WTemplow );
Stringzwei = String (WTempHigh );
Serial1.println("<Text06:BestTemp " + Stringeins + "-" + Stringzwei);
Stringeins = String (gesamtzeit - starttimer);
Stringzwei = String (zeittimer1);
Serial1.println("<Text07:Timer " + Stringeins + " von " + Stringzwei);
if (timer == 0)   Serial1.println("<Text08:Timer aus  " );
if (timer == 1)   Serial1.println("<Text08:Timer1 Läuft  " );
if (timer == 2)   Serial1.println("<Text08:Beide Timer laufen  " );






digitalWrite(LEDW, LOW);

//Vorgang einmal in der Minute ,Timmer grundzeit stellen
if (Bittimer != minute()) {
  Bittimer = minute();
  gesamtzeit = gesamtzeit + 1;
  //Monitorausgabe  Aktualsierung Minütlich

  Serial.print(SPhasename);
  Serial.print(" Uhrzeit ");
  Serial.print(now());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year());
  Serial.println();
  Serial.print(" Seit start Sind ");
  Serial.print (gesamtzeit);
  Serial.println(" Minuten vergangen");
  Serial.print("Sensor 0 hat ");
  Serial.println(Brautopftemp); //blau
  Serial.print("Sensor 1 hat ");
  Serial.println(Wasserkochertemp);// grün
  Serial.print("Sensor 2 hat ");
  Serial.println(sensors.getTempCByIndex(2));
  Serial.println("SD Schreiben");
  //SD Karte jede Minute einmal Schreiben Aktualsierung Minütlich
 SD.begin(chipSelect);
  
  dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
  dataFile.print(day());
  dataFile.print(".");
  dataFile.print(month());
  dataFile.print(".");
  dataFile.print(year());
  dataFile.print (" ");
  dataFile.print(hour());
  dataFile.print(":");
  dataFile.print (minute());
  dataFile.print(" Minute ");
  dataFile.print(gesamtzeit);
  dataFile.print (" Brautopf ");
  dataFile.print(Brautopftemp);
  dataFile.print (" Kocher ");
  dataFile.print(Wasserkochertemp);
  dataFile.print(" Liter ");
  dataFile.print(akLiter);
  dataFile.print(" Stammwuerze ");
  dataFile.print(akStammwuerze);
  dataFile.print(" ");
  dataFile.println (SPhasename);

  dataFile.flush();  // und Speichern
  dataFile.close();
  digitalWrite(LEDW, HIGH);
  Serial.println("SD Geschrieben");
  
 } 

}
dataFile = SD.open("datalog.txt");
  if (dataFile) {
     Bitdata = 0 ;
    

    // read from the file until there's nothing else in it:
    if (dataFile.available()) {
      Bitdata = 0 ;
      digitalWrite(LEDGL, LOW);
    }else {
    Bitdata = 1;
    // if the file didn't open, print an error:
    Serial.println("error opening datalog.txt");
    digitalWrite(LEDGL, HIGH);
  }
    // close the file:
    dataFile.close();
  }



//Schalter 1 Einmaischen        __________________________________________________________________________________________________

if (operationA  == 0) {
  if (digitalRead(Schalter1) == HIGH) {          // Operation wird einmal mit schalten ausgeführt
    if (operationB == 0 ) {
      NextPhase();
      //Temperatur Brautopf
      BTemplow = 35 ;   // Mindest Temperatur Maische
      BTempHigh = 40 ;  // Max Temperatur Maische
      //Temperatur Wasserkocher
      WTemplow = 50 ;   // Mindest Temperatur Kocher
      WTempHigh = 55 ;  // Max Temperatur Kocher
      zeittimer1 = 0;   //gibt an wie lange ein Vorgang dauern soll
      zeittimer2 = 0 ;   //

    }  //Timer setzen

    if (digitalRead(Schalter2) == HIGH) operationA = operationA + 1;
    ZuruckBIT = 0 ;
  }//Ende Schalter High

}// LOOP Maischen
//Schalter 2 Eiweisrast         __________________________________________________________________________________________________
if (operationA == 1) {
  if (digitalRead(Schalter2) == HIGH) {
    if (operationB == 1) {
      //Temperatur Brautopf
      BTemplow = 35 ;   // Mindest Temperatur Maische
      BTempHigh = 40 ;  // Max Temperatur Maische
      //Temperatur Wasserkocher
      WTemplow = 70 ;   // Mindest Temperatur Kocher
      WTempHigh = 80 ;  // Max Temperatur Kocher}
      zeittimer1 = 1;   //20  gibt an wie lange ein Vorgang dauern soll
      zeittimer2 = 5 ;   //
      NextPhase();
    }//Ende Einmalvorgang

    if (digitalRead(Schalter3) == HIGH) operationA = operationA + 1;
    ZuruckBIT = 0 ;
  }//Ende Schalter High

  if (digitalRead(Schalter2) == LOW ) LastPhase();



}// LOOP Eiweisrast
//Schalter 3 Maltoserast        __________________________________________________________________________________________________
if (operationA == 2) {
  if (digitalRead(Schalter3) == HIGH) {
    if (operationB == 2) {
      NextPhase();
      BTemplow = 60 ;   // Mindest Temperatur Maische
      BTempHigh = 65 ;  // Max Temperatur Maische
      //Temperatur Wasserkocher
      WTemplow = 70 ;   // Mindest Temperatur Kocher
      WTempHigh = 80 ;  // Max Temperatur Kocher}

      zeittimer1 = 10; //35  //gibt an wie lange ein Vorgang dauern soll
      zeittimer2 = 0 ;


    }//Ende Einmalvorgang

    if (digitalRead(Schalter4) == HIGH) operationA = operationA + 1;
    ZuruckBIT = 0 ;
  }//Ende Schalter High
  if (digitalRead(Schalter3) == LOW  ) LastPhase();

}// LOOP Maltoserast
//Schalter 4 Verzuckerungsrast  __________________________________________________________________________________________________
if (operationA == 3) {
  if (digitalRead(Schalter4) == HIGH) {
    if (operationB == 3) {


      BTemplow = 70 ;   // Mindest Temperatur Maische
      BTempHigh = 75 ;  // Max Temperatur Maische
      //Temperatur Wasserkocher
      WTemplow = 70 ;   // Mindest Temperatur Kocher
      WTempHigh = 80 ;  // Max Temperatur Kocher}

      zeittimer1 = 40;   //gibt an wie lange ein Vorgang dauern soll
      zeittimer2 = 0 ;
      NextPhase();
    }//Ende Einmalvorgang
    if (digitalRead(Schalter5) == HIGH) operationA = operationA + 1;
    ZuruckBIT = 0 ;
  }//Ende Schalter High
  if (digitalRead(Schalter4) == LOW ) LastPhase();


}// LOOP Verzuckerungsrast
//Schalter 5 Laeutern und Ausschwänzen    __________________________________________________________________________________________________
if (operationA == 4) {
  if (digitalRead(Schalter5) == HIGH) {
    if (operationB == 4) {

      BTemplow = 80 ;   // Mindest Temperatur Maische
      BTempHigh = 90 ;  // Max Temperatur Maische
      //Temperatur Wasserkocher
      WTemplow = 80 ;   // Mindest Temperatur Kocher
      WTempHigh = 90 ;  // Max Temperatur Kocher}

      zeittimer1 = 0;   //gibt an wie lange ein Vorgang dauern soll
      zeittimer2 = 0 ; NextPhase();  //
    }//Ende Einmalvorgang

    if (digitalRead(Schalter6) == HIGH) operationA = operationA + 1;
    ZuruckBIT = 0 ;
  }//Ende Schalter High
  if (digitalRead(Schalter5) == LOW  ) LastPhase();

}// LOOP ende Laeutern&Ausschwänzen
//Schalter 6 Würzekochen       __________________________________________________________________________________________________
if (operationA == 5) {
  if (digitalRead(Schalter6) == HIGH) {
    if (operationB == 5) {


      BTemplow = 98 ;   // Mindest Temperatur Maische
      BTempHigh = 100 ;  // Max Temperatur Maische
      //Temperatur Wasserkocher
      WTemplow = 30 ;   // Mindest Temperatur Kocher
      WTempHigh = 60 ;  // Max Temperatur Kocher}

      zeittimer1 = 70;   //gibt an wie lange ein Vorgang dauern soll
      zeittimer2 = 90 ;   //
      NextPhase();
    }//Ende Einmalvorgang

    if ( digitalRead(Schalter7) == HIGH) operationA = operationA + 1;
    ZuruckBIT = 0 ;
  }//Ende Schalter High
  if (digitalRead(Schalter6) == LOW  ) LastPhase();


}// LOOP ende Würzekochen
//Schalter 7 Würzekühlen       __________________________________________________________________________________________________
if (operationA == 6) {
  if (digitalRead(Schalter7) == HIGH) {
    if (operationB == 6) {


      BTemplow = 20 ;   // Mindest Temperatur Maische
      BTempHigh = 25 ;  // Max Temperatur Maische
      //Temperatur Wasserkocher
      WTemplow = 30 ;   // Mindest Temperatur Kocher
      WTempHigh = 60 ;  // Max Temperatur Kocher}

      zeittimer1 = 0;   //gibt an wie lange ein Vorgang dauern soll
      zeittimer2 = 0 ;   //
      NextPhase();
    }//Ende Einmalvorgang
    if (digitalRead(Schalter8) == HIGH) operationA = operationA + 1;
    ZuruckBIT = 0 ;
  }//Ende Schalter High
  if (digitalRead(Schalter7) == LOW  ) LastPhase();


}// LOOP ende  Würzekühlen
//Schalter 8 Vergehrung        __________________________________________________________________________________________________
if (operationA == 7) {
  if (digitalRead(Schalter8) == HIGH) {
    if (operationB == 7) {

      BTemplow = 10 ;   // Mindest Temperatur Maische
      BTempHigh = 15 ;  // Max Temperatur Maische
      //Temperatur Wasserkocher
      WTemplow = 0 ;   // Mindest Temperatur Kocher
      WTempHigh = 15 ;  // Max Temperatur Kocher}

      zeittimer1 = 0 ;   //gibt an wie lange ein Vorgang dauern soll
      zeittimer2 = 0 ;   //
      NextPhase();
    }//Ende Einmalvorgang
    if (digitalRead(Schalter9) == HIGH) operationA = operationA + 1;
    ZuruckBIT = 0 ;
  }//Ende Schalter High
  if (digitalRead(Schalter8) == LOW ) LastPhase();


}// LOOP ende Vergehrung
//Schalter 9 Abfüllen      __________________________________________________________________________________________________
if (operationA == 8) {
  if (digitalRead(Schalter9) == HIGH) {
    if (operationB == 8) {


      BTemplow = 10 ;   // Mindest Temperatur Maische
      BTempHigh = 15 ;  // Max Temperatur Maische
      //Temperatur Wasserkocher
      WTemplow = 0 ;   // Mindest Temperatur Kocher
      WTempHigh = 15 ;  // Max Temperatur Kocher}

      zeittimer1 = 0 ;   //gibt an wie lange ein Vorgang dauern soll
      zeittimer2 = 0 ;
      NextPhase();
    }//Ende Einmalvorgang

    if (digitalRead(Schalter10) == HIGH) operationA = operationA + 1;
    ZuruckBIT = 0 ;
  }//Ende Schalter High
  if (digitalRead(Schalter9) == LOW  ) LastPhase();

}// LOOP ende  Vergehrung
//Schalter 10 Lagern      __________________________________________________________________________________________________
if (operationA == 9) {
  if (digitalRead(Schalter10) == HIGH) {
    if (operationB == 9) {

      BTemplow = 10 ;   // Mindest Temperatur Maische
      BTempHigh = 15 ;  // Max Temperatur Maische
      //Temperatur Wasserkocher
      WTemplow = 0 ;   // Mindest Temperatur Kocher
      WTempHigh = 15 ;  // Max Temperatur Kocher}

      zeittimer1 = 0 ;   //gibt an wie lange ein Vorgang dauern soll
      zeittimer2 = 0 ;
      NextPhase();
    }//Ende Einmalvorgang
    ZuruckBIT = 0 ;

  }//Ende Schalter High


  if (digitalRead(Schalter10) == LOW )  LastPhase();



}// LOOP ende Flaschenvergaehrung
char key = keypad.getKey();
if (key) {
  Serial.println(key);
}

//  LCD Ausgabe
//   Zeile 1

lcd.setCursor(11, 0);
lcd.print("Uhr ");
lcd.print(hour());
lcd.print(":");
lcd.print(minute());



//   Zeile 2
lcd.setCursor(0, 1); lcd.print("Timer ");
lcd.print(gesamtzeit - starttimer);
lcd.print(" M von ");
if (zeittimer1 < (gesamtzeit - starttimer)) {
  lcd.print(zeittimer1);
  lcd.print(" M  ");
}
else
{
  lcd.print(zeittimer2);
  lcd.print(" M  ");
}


//   Zeile 3
lcd.setCursor(0, 2);
lcd.print("Brauer ");
lcd.println(Brautopftemp); //blau
lcd.setCursor(9, 2);
lcd.print(" zu ");
lcd.print( BTemplow);
lcd.print("-");
lcd.print(BTempHigh);


//   Zeile 4
lcd.setCursor(0, 3);
lcd.print("Kocher ");
lcd.println(Wasserkochertemp);// grün
lcd.setCursor(9, 3);
lcd.print(" zu ");
lcd.print(WTemplow);
lcd.print("-");
lcd.print(WTempHigh);



}// Ende Loop










