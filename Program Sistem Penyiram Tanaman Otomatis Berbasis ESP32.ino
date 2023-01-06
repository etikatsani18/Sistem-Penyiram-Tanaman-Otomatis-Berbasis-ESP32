//  Sistem Penyiram Tanaman Otomatis Berbasis ESP32
//  KELOMPOK C7
//  ETIKA  TSANI        07
//  ROSHID ARDIANSYAH 21

#define uS_TO_S_FACTOR 1000000 // Mengkonversi milisecon ke secon
#define TIME_TO_SLEEP 30  // waktu menuju sleep 30 secon

//Inisiasi Untuk Tampilan Blynk
#define BLYNK_TEMPLATE_ID           "TMPLn-jQSvce"
#define BLYNK_DEVICE_NAME           "Monitoring Penyiraman Tanaman Otomatis"
#define BLYNK_AUTH_TOKEN            "X1Qx3KVjE4Y3d2ggFk8rfmvElvejLluN"


#define BLYNK_PRINT Serial

//Library Yang Digunakan
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

char auth[] = BLYNK_AUTH_TOKEN;

// SSID dan Pasword yang  digunakan
char ssid[] = "Redmi Note 9 Pro";
char pass[] = "28100203";



BlynkTimer timer;
//Pin alamat yang digunakan
LiquidCrystal_I2C lcd(0X27 ,16, 2);
const int relay = 14;    // deklarasi pin dht11 14
const int soilmoisture = 34;  //deklarasi pin sensor soilmoisture 34
float persen;

void setup()
{
  
  Serial.begin(115200);
  pinMode (relay,OUTPUT);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, analogSense);   //Waktu pembacaan memory pada deepsleep
//Tampilan Awal  LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("    Penyiram");
  lcd.setCursor(0,1);
  lcd.print("    Otomatis");
  delay(5000);
  lcd.clear();
//Pengulangan hasil pembacaan sensor
  for(int i=0; i<5; i++){
    analogSense();
    delay(500);
}
  //pengaturan untuk timer DeepSleep
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Blynk.run();
  timer.run(); 
}

void loop()
{
  Blynk.run();
  timer.run();  
}
 void analogSense(){   //Sensor kelembaban tanah
    float soil = analogRead(soilmoisture);  //mendeteksi nilai dari sensor soil moisture
    persen=(soil/8192)*100;  //mempersentasikan hasil pembacaan nilai sensor ke persen
//Tampilan pada serial moitor
    Serial.print("\nSoil Moisture: ");
    Serial.print(soil);
    delay(800);
    Serial.print("Hasil Persen: ");
    Serial.print(persen);
    delay(900);
//Tampilan pada Blynk melalui virtual PIN
    Blynk.virtualWrite(V3, soil);
    Blynk.virtualWrite(V7, persen);

//Untuk kondisi tanah kering
     if(persen>25){  //jika kelembaban tanah <= 25, maka pompa on
    relayON();
    lcd.setCursor(0,0);
    lcd.print("T Kering: ");
    lcd.print(persen);
    lcd.print("%");
    lcd.setCursor(0,1);
    lcd.print("Pompa Nyala");

  }

//Untuk kondisi  tanah basah
    else if(persen<=25){// jika kelembaban tanah > 25 pompa off
    relayOFF();
    lcd.setCursor(0,0);
    lcd.print("T Basah: ");
    lcd.print(persen);
    lcd.print("%");
    lcd.setCursor(0,1);
    lcd.print("Pompa  Mati ");

    }
    delay(100);
  }

//Inisiasi penggunaan relay
  void relayON(){
  digitalWrite(relay, HIGH);
  WidgetLED relay(V8);
  relay.on();
}
void relayOFF(){
  digitalWrite(relay, LOW);
  WidgetLED relay(V8);
  relay.off();
}
//  Sistem Penyiram Tanaman Otomatis Berbasis ESP32
//  KELOMPOK C7
//  ETIKA  TSANI        07
//  ROSHID ARDIANSYAH 21

#define uS_TO_S_FACTOR 1000000 // Mengkonversi milisecon ke secon
#define TIME_TO_SLEEP 30  // waktu menuju sleep 30 secon

//Inisiasi Untuk Tampilan Blynk
#define BLYNK_TEMPLATE_ID           "TMPLn-jQSvce"
#define BLYNK_DEVICE_NAME           "Monitoring Penyiraman Tanaman Otomatis"
#define BLYNK_AUTH_TOKEN            "X1Qx3KVjE4Y3d2ggFk8rfmvElvejLluN"


#define BLYNK_PRINT Serial

//Library Yang Digunakan
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

char auth[] = BLYNK_AUTH_TOKEN;

// SSID dan Pasword yang  digunakan
char ssid[] = "Redmi Note 9 Pro";
char pass[] = "28100203";



BlynkTimer timer;
//Pin alamat yang digunakan
LiquidCrystal_I2C lcd(0X27 ,16, 2);
const int relay = 14;    // deklarasi pin dht11 14
const int soilmoisture = 34;  //deklarasi pin sensor soilmoisture 34
float persen;

void setup()
{
  
  Serial.begin(115200);
  pinMode (relay,OUTPUT);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, analogSense);   //Waktu pembacaan memory pada deepsleep
//Tampilan Awal  LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("    Penyiram");
  lcd.setCursor(0,1);
  lcd.print("    Otomatis");
  delay(5000);
  lcd.clear();
//Pengulangan hasil pembacaan sensor
  for(int i=0; i<5; i++){
    analogSense();
    delay(500);
}
  //pengaturan untuk timer DeepSleep
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Blynk.run();
  timer.run(); 
}

void loop()
{
  Blynk.run();
  timer.run();  
}
 void analogSense(){   //Sensor kelembaban tanah
    float soil = analogRead(soilmoisture);  //mendeteksi nilai dari sensor soil moisture
    persen=(soil/8192)*100;  //mempersentasikan hasil pembacaan nilai sensor ke persen
//Tampilan pada serial moitor
    Serial.print("\nSoil Moisture: ");
    Serial.print(soil);
    delay(800);
    Serial.print("Hasil Persen: ");
    Serial.print(persen);
    delay(900);
//Tampilan pada Blynk melalui virtual PIN
    Blynk.virtualWrite(V3, soil);
    Blynk.virtualWrite(V7, persen);

//Untuk kondisi tanah kering
     if(persen>25){  //jika kelembaban tanah <= 25, maka pompa on
    relayON();
    lcd.setCursor(0,0);
    lcd.print("T Kering: ");
    lcd.print(persen);
    lcd.print("%");
    lcd.setCursor(0,1);
    lcd.print("Pompa Nyala");

  }

//Untuk kondisi  tanah basah
    else if(persen<=25){// jika kelembaban tanah > 25 pompa off
    relayOFF();
    lcd.setCursor(0,0);
    lcd.print("T Basah: ");
    lcd.print(persen);
    lcd.print("%");
    lcd.setCursor(0,1);
    lcd.print("Pompa  Mati ");
    }
    delay(100);
  }

//Inisiasi penggunaan relay
  void relayON(){
  digitalWrite(relay, LOW);
  WidgetLED relay(V8);
  relay.on();
}
void relayOFF(){
  digitalWrite(relay, HIGH);
  WidgetLED relay(V8);
  relay.off();
}
