#include <virtuabotixRTC.h>

int CLK = 10;            //RTC CLOCK PINI
int DAT = 7;             //RTC DATA PINI
int RST = 8;             //RTC RESET PINI
virtuabotixRTC myRTC(CLK, DAT, RST);             //RTC TANIMLAMA

#define VBAT A0             //POT ile gerilim bolucu
#define role1 2             //AYDINLATMA ROLESI
#define role2 3             //SARJ ROLESI
#define role3 4             //FAN ROLESI
#define role4 11

#define RED_LED 6             //KIRMIZI LED
#define BLUE_LED 5            //MAVI LED
#define GREEN_LED 9           //YESIL LED

int brightness = 255;         //PARLAKLIK MAKSIMUM 255
int gBright = 0;              //YESIL BASLANGIC PARLAKLIGI
int rBright = 0;              //KIRMIZI BASLANGIC PARLAKLIGI
int bBright = 0;              //MAVI BASLANGIC PARLAKLIGI
int fadeSpeed = 1;            //GOLGELENME SURESI

const int sensor_pin = A1;             //SICAKLIK SENSORU DATA PINI
int sensor_deger = 0;                  //SENSOR DEGISKENI
float voltaj_deger = 0;                //SENSOR DEGISKENI
float sicaklik_deger =0;               //SENSOR DEGISKENI

int bat_deger = 0;                     //BATARYA DEGISKENI
void setup() {
  Serial.begin(9600);
  //myRTC.setDS1302Time(0, 31, 14, 6, 21, 5, 2022);  // RTC zamani ayarlandi
  
  pinMode(VBAT,INPUT);                            //BATARYA
  
  pinMode(role1, OUTPUT);                         //ROLE
  pinMode(role2, OUTPUT);                         //ROLE
  pinMode(role3, OUTPUT);                         //ROLE
  pinMode(role4, OUTPUT);

  pinMode(GREEN_LED, OUTPUT);                     //LED
  pinMode(RED_LED, OUTPUT);                       //LED
  pinMode(BLUE_LED, OUTPUT);                      //LED

  randomSeed(analogRead(5));                      //LED RENK DEGISTIRME
  
}

void TurnOn() { 
    switch(random(6)){
      case 1:
         for (int i = 0; i < 256; i++) {
             analogWrite(RED_LED, rBright);
             rBright +=1;
             delay(fadeSpeed*random(5));
         }
         for (int i = 0; i < 256; i++) {
             analogWrite(BLUE_LED, bBright);
             bBright += 1;
             delay(fadeSpeed*random(5));
         } 
         for (int i = 0; i < 256; i++) {
             analogWrite(GREEN_LED, gBright);
             gBright +=1;
             delay(fadeSpeed*random(5));
         }
        break;
        
      case 2:
         for (int i = 0; i < 256; i++) {
             analogWrite(BLUE_LED, bBright);
             bBright += 1;
             delay(fadeSpeed*random(5));
         }
         for (int i = 0; i < 256; i++) {
             analogWrite(RED_LED, rBright);
             rBright +=1;
             delay(fadeSpeed*random(5));
         }
         for (int i = 0; i < 256; i++) {
             analogWrite(GREEN_LED, gBright);
             gBright +=1;
             delay(fadeSpeed*random(5));
         }
        break;
        
      case 3:
         for (int i = 0; i < 256; i++) {
             analogWrite(BLUE_LED, bBright);
             bBright += 1;
             delay(fadeSpeed*random(5));
         }
         for (int i = 0; i < 256; i++) {
             analogWrite(GREEN_LED, gBright);
             gBright +=1;
             delay(fadeSpeed*random(5));
         }
         for (int i = 0; i < 256; i++) {
             analogWrite(RED_LED, rBright);
             rBright +=1;
             delay(fadeSpeed*random(5));
         }
        break;
          
      case 4:
         for (int i = 0; i < 256; i++) {
             analogWrite(RED_LED, rBright);
             rBright +=1;
             delay(fadeSpeed*random(5));
         }
         for (int i = 0; i < 256; i++) {
             analogWrite(GREEN_LED, gBright);
             gBright +=1;
             delay(fadeSpeed*random(5));
         }
         for (int i = 0; i < 256; i++) {
             analogWrite(BLUE_LED, bBright);
             bBright += 1;
             delay(fadeSpeed*random(5));
         } 
        break; 
        
      case 5:
         for (int i = 0; i < 256; i++) {
             analogWrite(GREEN_LED, gBright);
             gBright +=1;
             delay(fadeSpeed*random(5));
         }      
         for (int i = 0; i < 256; i++) {
             analogWrite(RED_LED, rBright);
             rBright +=1;
             delay(fadeSpeed*random(5));
         }
         for (int i = 0; i < 256; i++) {
             analogWrite(BLUE_LED, bBright);
             bBright += 1;
             delay(fadeSpeed*random(5));
         } 
        break; 
        
      case 6:
         for (int i = 0; i < 256; i++) {
             analogWrite(GREEN_LED, gBright);
             gBright +=1;
             delay(fadeSpeed*random(5));
         }
         for (int i = 0; i < 256; i++) {
             analogWrite(BLUE_LED, bBright);
             bBright += 1;
             delay(fadeSpeed*random(5));
         }
         for (int i = 0; i < 256; i++) {
             analogWrite(RED_LED, rBright);
             rBright +=1;
             delay(fadeSpeed*random(5));
         }         
        break;                  
    }

  
 
}

void TurnOff() {
   for (int i = 0; i < 256; i++) {
       analogWrite(GREEN_LED, brightness);
       analogWrite(RED_LED, brightness);
       analogWrite(BLUE_LED, brightness);
 
       brightness -= 1;
       delay(fadeSpeed*random(5));
   }
   analogWrite(GREEN_LED, 0);
   analogWrite(RED_LED, 0);
   analogWrite(BLUE_LED, 0);
}

void Time() {
  myRTC.updateTime();                    //RTC OKUMA VE TARIH YAZDIRMA
  Serial.print("Tarih/saat: ");
  Serial.print(myRTC.dayofmonth);
  Serial.print("/");
  Serial.print(myRTC.month);
  Serial.print("/");
  Serial.print(myRTC.year);
  Serial.print(" ");
  Serial.print(myRTC.hours);
  Serial.print(":");
  Serial.print(myRTC.minutes);
  Serial.print(":");
  Serial.println(myRTC.seconds);
}

void Sicaklik() {
  sensor_deger = analogRead(sensor_pin);                    //SICAKLIK OLCME
  voltaj_deger = (sensor_deger / 1023.0) * 5000.0;
  sicaklik_deger = voltaj_deger / 10.0;
  Serial.print("Sicaklik: ");
  Serial.println(sicaklik_deger);
}

void Batarya() {
  bat_deger = analogRead(VBAT);                             //GERILIM BOLUCU OKUMA VE BATARYA YUZDESI YAZDIRMA
  Serial.print("Batarya: %");
  Serial.println(analogRead(VBAT)*0.1887);
}

void loop() {
  int aydinlatma = 0;             //AYDINLATMA ROLESI DEGISKEN SIFIRLAMA
  int sarj = 0;                   //SARJ ROLESI DEGISKEN SIFIRLAMA
  int fan = 0;                    //FAN ROLESI DEGISKEN SIFIRLAMA
  

  /*
  Batarya 12.6 Olduğunda 47K ve 10K lık dirençlerden 2.11V okunuyor ve bunun analog karşılığı 420
  Şarj cihazlarının kapanmasını hücre başı 3.2V ile yapacak olursak; Batarya 9.6V'a düştüğünde
  Okunan gerilim değeri 1.62V olacak ve seri porttan alınan değer 324 olmuştur. Batarya için kritik
  olan hücre başı gerilim 3V ve toplam batarya gerilimi 9V'a düştüğünde okunacak gerilim değeri
  1.52V olmuştur ve seri port değeri 302 olmuştur.
  
  
  */

  myRTC.updateTime();                    //RTC OKUMA VE TARIH YAZDIRMA
  Serial.print("Tarih/saat: ");
  Serial.print(myRTC.dayofmonth);
  Serial.print("/");
  Serial.print(myRTC.month);
  Serial.print("/");
  Serial.print(myRTC.year);
  Serial.print(" ");
  Serial.print(myRTC.hours);
  Serial.print(":");
  Serial.print(myRTC.minutes);
  Serial.print(":");
  Serial.println(myRTC.seconds);

  sensor_deger = analogRead(sensor_pin);                    //SICAKLIK OLCME
  voltaj_deger = (sensor_deger / 1023.0) * 5000.0;
  sicaklik_deger = voltaj_deger / 10.0;
  Serial.print("Sicaklik: ");
  Serial.println(sicaklik_deger);

  
  bat_deger = analogRead(VBAT);                             //GERILIM BOLUCU OKUMA VE BATARYA YUZDESI YAZDIRMA
  Serial.print("Batarya: %");
  Serial.println(analogRead(VBAT)*0.1887);

  
  if(bat_deger<=600 && bat_deger>323){                      //BATARYA TAM DOLUYSA TUM SISTEMLER GEREKTIGINDE CALISABILIR
    digitalWrite(role2, LOW);                               //SARJ ACILDI
    digitalWrite(role4, LOW);
      if(myRTC.hours > 19 || myRTC.hours < 5){              //AYDINLATMA SISTEMI 20:00 - 04:00 SAATLERI ARASINDA CALISACAK
        digitalWrite(role1, LOW);
        Serial.println("AYDINLATMA:  ACIK");
        aydinlatma = 1;
      }
      else{
        digitalWrite(role1, HIGH);
        Serial.println("AYDINLATMA:  KAPALI(SAAT)");
        aydinlatma = 0;
      }
    Serial.println("SARJ:  ACIK");
  }
  if(bat_deger<=323 && bat_deger>302){                      //BATARYA AZALIRSA BANK SADECE AYDINLATMA YAPABILECEK
    digitalWrite(role2, HIGH);                              //SARJ KAPATILDI
    digitalWrite(role4, HIGH);
      if(myRTC.hours > 19 || myRTC.hours < 5){              //AYDINLATMA SISTEMI 20:00 - 04:00 SAATLERI ARASINDA CALISACAK
        digitalWrite(role1, LOW);
        Serial.println("AYDINLATMA:  ACIK");
        aydinlatma = 1;
      }
      else{
        digitalWrite(role1, HIGH);
        Serial.println("AYDINLATMA:  KAPALI(SAAT)");
        aydinlatma = 0;
      }
    Serial.println("SARJ: KAPALI");
  }
LB:
  bat_deger = analogRead(VBAT);                             //BATARYA KAPASITESI HER LOOPTA TEKRAR KONTROL EDILIR
  if(bat_deger <= 302){                                     //BATARYANIN OMRUNU AZALTMAMAK ICIN ASIRI DESARJ KORUMASI
    Time();
    Sicaklik();
    Serial.print("Batarya: %");                             //BUTUN SISTEMLER DEVRE DISI
    Serial.println(analogRead(VBAT)*0.1887);
    Serial.println("AYDINLATMA:  KAPALI(LB)");
    Serial.println("SARJ: KAPALI(LB)");
    Serial.println("FAN:  KAPALI(LB)");
    Serial.println("--------------------------------------------------------------");
    digitalWrite(role1, HIGH);
    digitalWrite(role2, HIGH);
    digitalWrite(role3, HIGH);
    digitalWrite(role4, HIGH);
    aydinlatma = 0;
    delay(2000);
    goto LB;                                                //SARJ DUSUKSE DOLMASINI BEKLER(BASKA BIR LOOPA GONDER SARJIN %60 OLMASINI BEKLESIN)
  }
  HT:
  sensor_deger = analogRead(sensor_pin);                   //SONSUZ LOOPA GIRMESINI ENGELLEMEK ICIN SICAKLIK TEKRAR OKUNUYOR
  voltaj_deger = (sensor_deger / 1023.0) * 5000.0;
  sicaklik_deger = voltaj_deger / 10.0;
  if(sicaklik_deger > 40 && sicaklik_deger < 55){          //SICAKLIK YUKSELIRSE FANI ACIYOR
    digitalWrite(role3, LOW);
    Serial.println("FAN:  ACIK");
    Serial.println("--------------------------------------------------------------");
  }
  if(sicaklik_deger > 55){                                //SICAKLIK COK YUKSELIRSE DIGER SISTEMLERI KAPATIYOR VE SISTEMI SOGUTUYOR
    Time();
    Serial.print("Sicaklik: ");
    Serial.println(sicaklik_deger);
    Batarya();
    digitalWrite(role1, HIGH);
    digitalWrite(role2, HIGH);
    digitalWrite(role3, LOW);
    digitalWrite(role4, HIGH);
    Serial.println("AYDINLATMA:  KAPALI(HT)");
    Serial.println("SARJ: KAPALI(HT)");
    Serial.println("FAN:  ACIK(HT)");
    Serial.println("--------------------------------------------------------------");
    delay(2000);
    goto HT;
  }
  if(sicaklik_deger < 40){                             //SICAKLIGIN NORMAL DEGERLERDE OLMASI DURUMUNDA FAN KAPALI
    digitalWrite(role3, HIGH);
    Serial.println("FAN:  KAPALI");
    Serial.println("--------------------------------------------------------------");
    delay(1000);
  }
  
  if(aydinlatma == 1){
   TurnOn();
   delay(1000);
   TurnOff();
  }
  delay(500);
}
