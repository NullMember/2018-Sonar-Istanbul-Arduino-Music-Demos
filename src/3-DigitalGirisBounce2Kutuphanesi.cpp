/* PullUp direncinin baglanti sekli
            VCC
            |
            |
            <
            > 10k ohm
            <
    uC-------------Pin
    
*/

#include <Arduino.h>
#include <Bounce2.h>

char butonPini = 6;
char ledPini = 13;
Bounce buton;    //Butonu okumak icin Bounce kutuphanesinden bir obje yaratiyoruz 

void setup(){
    Serial.begin(115200); // UART iletisim donanimini 115200 BAUD degerinde aktif hale getiriyoruz
    pinMode(ledPini, OUTPUT); // Led pinini cikis olarak ayarliyoruz
    pinMode(butonPini, INPUT_PULLUP); // Buton'un bagli oldugu pini giris olarak ayarlayarak PullUp direncini aktif hale getiriyoruz
    // PullUp direnci mikrokontrolcu icerisinde pin'i VCC'ye baglayan baglayan direnctir
    // Genellikle direnc degeri cok buyuktur
    // Pin ile GND'nin kisadevre halinde mikrokontrolcuye zarar vermesini engeller
    // Mikrokontrolcu icerisinde yukaridaki sekilde baglidir
    // Buton'a basilmadigi durumda okunan veri her zaman 1 (True) olacaktir
    buton.attach(butonPini); // butonu debouncer'a atiyoruz
    buton.interval(10);      // debounce suresini belirliyoruz
}

void loop(){
    buton.update(); // Bounce2 kutuphanesinde butonun durumunu guncelliyoruz
    if(buton.read() == 0){              // Okudugumuz deger 0'a esitse (butona basildiysa)
        digitalWrite(ledPini, HIGH);    // Ledi yakiyoruz
    }
    else{                               // Okudugumuz deger 0 degil ise (buton birakildiysa)
        digitalWrite(ledPini, LOW);     // Ledi sonduruyoruz
    }
    if(buton.fell()){                   // Butona basildigi anda (Buton 1'den 0'a gectigi kenarda)
        Serial.println("Butona Basildi!"); // Seri monitore "Butona Basildi!" mesajini gonderiyoruz
    }
    if(buton.rose()){                   // Buton birakildigi anda (Buton 0'dan 1'e gectigi anda)
        Serial.println("Buton Birakildi!"); // Seri monitore "Buton Birakildi!" mesajini gonderiyoruz
    }
}