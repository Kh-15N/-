 #include 
 #include 

 #include "DHT.h"

 #define DHTTYPE DHT11


 int pinDHT11=9;
 
 int pinSoilMoisture=A0;
 
 int pinTMP36=A1;


 #define LED_TEMP 5
 #define LED_MOISTURE 6


 #define TEMP_DETECT 30
 #define MOISTURE_DETECT 500


 DHT dht(pinDHT11, DHTTYPE);

// Nokia 5110
 // pin 13 - Serial clock out (SCLK)
 // pin 12 - Serial data out (DIN)
 // pin 11 - Data/Command select (D/C)
 // pin 10 - LCD chip select (CS)
 // pin 8 - LCD reset (RST)
 Adafruit_PCD8544 display = Adafruit_PCD8544(13, 12, 11, 10, 8);

void setup() {

 Serial.begin(9600);
 
 pinMode(LED_TEMP,OUTPUT);digitalWrite(LED_TEMP,LOW);
 pinMode(LED_MOISTURE,OUTPUT);digitalWrite(LED_MOISTURE,LOW);

 dht.begin();

 display.begin();

 display.setContrast(60);
 display.clearDisplay(); 
 display.setTextSize(1); 
 display.setTextColor(BLACK); 

 display.setCursor(15,15);
 display.print("Home Flower");
 display.display();
 delay(2000);
 }

void loop()
 {
 display.clearDisplay();
 display.setCursor(5,0);
 display.print("Home Flower");

 float h = dht.readHumidity();
 display.setCursor(5,10);
 if (isnan(h))
 {
 Serial.println("Failed to read from DHT");
 display.print("airH= error");
 }
 else
 {
 Serial.print("HumidityDHT11= "); Serial.print(h);Serial.println(" %");
 display.print("airH=");display.print(h);display.print("%");
 }

 display.setCursor(5,20);
 int val0=analogRead(pinSoilMoisture);
 Serial.print("SoilMoisture= "); Serial.println(val0);
 display.print("soilM=");display.print(val0);

 display.setCursor(5,30);
 int val1=analogRead(pinTMP36);

 int mV= val1*1000/1024;

 int t=(mV-500)/10+75;
 Serial.print("TempTMP36= "); Serial.print(t);Serial.println(" C");
 display.print("airT=");display.print(t);display.print(" C");


 display.display();

 if(val0 > MOISTURE_DETECT)
 digitalWrite(LED_MOISTURE,HIGH);
 else
 digitalWrite(LED_MOISTURE,LOW);

 if(t > TEMP_DETECT)
 digitalWrite(LED_TEMP,HIGH);
 else
 digitalWrite(LED_TEMP,LOW);

 Serial.println();
 delay(5000);
 }
  