#include <Arduino.h>
#include <SonarMIDIUSB.h>

byte triggerPin = 2;
byte echoPin = 3;

unsigned int gecenSure;
float mesafe;

void setup(){
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop(){
    digitalWrite(triggerPin, LOW);          //Daha once trigger pininin durumu degistirilmis olabilecegi icin LOW yapiyoruz
    delayMicroseconds(2);                   //2uS bekliyoruz
    digitalWrite(triggerPin, HIGH);         //Trigger pinini HIGH yaparak
    delayMicroseconds(10);                  //10uS'lik bir sinyal gonderiyoruz
    digitalWrite(triggerPin, LOW);          //Ve sinyali kesiyoruz
    
    gecenSure = pulseIn(echoPin, HIGH);     //pulseIn fonksiyonu sayesinde sinyali gonderdigimiz andan itibaren
                                            //echoPin HIGH okuyana kadar kac uS gectigini hesapliyoruz
                                            
    mesafe = (gecenSure * 340) / 2;         //Mesafeyi (gecenSure * sesin havadaki hizi) / 2(gidis+gelis)
                                            //Formuluyle hesapliyoruz
}