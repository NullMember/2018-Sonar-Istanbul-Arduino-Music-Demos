#include <Arduino.h>
#include <Bounce2.h>
#include <SonarMIDIUSB.h>

const byte butonSayisi = 8;                                     //Daha sonra bircok yerde kullanacagimiz icin buton sayisini bir degiskene yaziyoruz
byte butonPinleri[butonSayisi] = {2, 3, 4, 5, 6, 7, 8, 9};      //Baglayacagimiz butonlarin pinlerini butonPinleri dizisine yaziyoruz
byte notalar[butonSayisi] = {60, 62, 64, 65, 67, 69, 71, 72};   //Butonlara bastigimizda tetiklenecek notalari notalar dizisine yaziyoruz
byte potansPini = A0;                                           //Potans Pini
byte velocity;

Bounce buton[butonSayisi];
// Buton sayisi kadar debouncer olusturuyoruz
SonarMIDIUSB midi;

void setup(){
    pinMode(potansPini, INPUT);                     //Potans pinini giris durumuna getiriyoruz
    
    for(byte i = 0; i < butonSayisi; i++){          //for dongusu ile buton sayisi kadar dongu yapiyoruz
        pinMode(butonPinleri[i], INPUT_PULLUP);     //for dongusu dizileri kullanarak onlarca satirda yapacagimiz isi
        buton[i].attach(butonPinleri[i]);           //cok daha kisa bir sekilde yapabilmemizi sagliyor
        buton[i].interval(10);
    }
}

void loop(){
    velocity = analogRead(potansPini) >> 3;         //velocity (gurluk) degerini potanstan okuyoruz ve 3-bit kaydiriyoruz
    for(byte i = 0; i < butonSayisi; i++){          //for dongusu ile buton satisi kadar dongu yapiyoruz
        buton[i].update();                          //butonlari okuyoruz
        if(buton[i].fell()){                        //eger butona basildiysa
            midi.sendNoteOn(notalar[i], velocity); //potanstan gelen velocity degeri ile birlikte NoteOn mesaji gonderiyoruz
        }
        if(buton[i].rose()){                        //eger buton birakildiysa
            midi.sendNoteOff(notalar[i]);           //NoteOff mesaji gonderiyoruz
        }
    }
}