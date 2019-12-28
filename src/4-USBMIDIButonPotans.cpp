#include <Arduino.h>
#include <Bounce2.h>
#include <SonarMIDIUSB.h>

byte butonPini = 6; 
byte potansPini = A0;
byte ledPini = 13;
byte nota;

Bounce buton;
SonarMIDIUSB midi;          //MIDI verilerini usb uzerinden gondermek icin SonarMIDIUSB sinifindan bir obje yaratiyoruz

void setup(){
    pinMode(potansPini, INPUT);
    pinMode(ledPini, OUTPUT);
    
    pinMode(butonPini, INPUT_PULLUP);
    buton.attach(butonPini);
    buton.interval(10);
}

void loop(){
    buton.update();
    if(buton.fell()){                       // Eger butona basildiysa
        nota = analogRead(potansPini) >> 3; //potanstan gelen analog veriyi okuyoruz ve 3-bit saga kaydiriyoruz
                                            // Arduino kartlari genellikle analog veriyi 10-bit olarak okurlar
                                            // MIDI protokolunde veriler 7-bit oldugu icin 10-bitlik veriyi 3-bit saga kaydirarak
                                            // 7-bit sonuc elde ediyoruz
        midi.sendNoteOn(nota);              // Potanstan okudugumuz notayi NoteOn mesajiyla MIDI uzerinden gonderiyoruz
        digitalWrite(ledPini, HIGH);        // Led'i yakiyoruz
    }
    if(buton.rose()){                       // Eger buton birakildiysa
        midi.sendNoteOff(nota);             // Daha once NoteOn gonderdigimiz nota icin NoteOff mesaji gonderiyoruz
        digitalWrite(ledPini, LOW);         // Led'i sonduruyoruz
    }
}