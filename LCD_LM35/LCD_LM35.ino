#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

const int analogIn = A0;
const int ServoPin =9; // Pin al que esta conectado el motor
int temperatureLimit =25; //Límite de temperatura inicial
int temperatureLimitSerial = -1; //valor -1 indicaque no se ha recibido límite por serial
LiquidCrystal_I2C lcd(0x27,16,2);

int RawValue = 0;
double Voltage = 0;
double tempC = 0;
double tempF = 0;
Servo Servo1;

void setup() {
  Serial.begin(9600);
  Servo1.attach(ServoPin);
  lcd.init();

  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Iniciando");
  lcd.setCursor(2,1);
  lcd.print("LCD");
}

void loop() {
  if (Serial.available() > 0) {
    //Si hay datos disponibles en el puerto serie
    temperatureLimit = Serial.parseInt();
    Serial.println("Valor recibido:");
    Serial.println(temperatureLimitSerial);
    lcd.setCursor(0,0);
    lcd.print("Valor Recibido:"+temperatureLimitSerial);
    }
    
    RawValue = analogRead(analogIn);
    Voltage = (RawValue / 1023.0) * 5000;
    tempC = Voltage * 0.1;
    tempF = (tempC * 1.8) + 32;

    Serial.print("Temperatura (C): ");
    Serial.println(tempC, 1);
    lcd.setCursor(0,0);
    lcd.print("Temperatura");
    lcd.setCursor(2,1);
    lcd.print(tempC);

    int currentLimit = (temperatureLimitSerial != -1) ? temperatureLimitSerial : temperatureLimit;

    //Controla el  motor en funcion del limite de temperatura
    if (tempC > temperatureLimit){

      Servo1.write(0);
      delay(1000);
      Servo1.write(90);
      delay(1000);
      Servo1.write(180);
      delay(1000);
    } else{

      Servo1.write(90);

    }

    delay(500);
  }