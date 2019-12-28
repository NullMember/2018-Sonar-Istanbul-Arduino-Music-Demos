#include <Arduino.h>

int potans;
char potansPini = A0;

void setup(){
    Serial.begin(115200); // UART iletisim donanimini aktif hale getirir.
                          // Verilen arguman saniyede gonderilebilecek maksimum bit sayisini ifade eder. BAUD olarak adlandirilir.
    pinMode(A0, INPUT); // Potans'in bagli oldugu pini giris olarak ayarliyoruz
}

void loop(){
    potans = analogRead(potansPini); // A0 pininden gelen analog degeri okuyarak potans degiskenine yaziyoruz.
    Serial.print("Okunan deger: "); // Serial.print fonksiyonu UART uzerinden yazi veya sayi gondermek icin kullanilabilir
                                    // Gonderilen deger Arduino IDE icerisindeki seri monitorden okunabilir
    Serial.println(potans);         // Serial.println fonksiyonu Serial.print ile ayni isleve sahiptir
                                    // Aradaki tek fark girilen veri UART uzerinden gonderildikten sonra satir atlama komutunun da gonderilmesidir
    delay(50);                      // Okunacak degerin cok hizli degismemesi icin delay komutu kullaniyoruz
}