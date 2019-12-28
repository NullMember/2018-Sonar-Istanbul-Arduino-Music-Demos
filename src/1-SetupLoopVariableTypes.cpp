#include <Arduino.h>

// Degisken Tipleri
// Daha ayrintili bilgi icin https://www.arduino.cc/reference/en/#variables
// Integer tipi degiskenler
// 1-byte'lik veri tipleri
char v_char; // signed 1-byte veri tipidir. -128_127 arasindaki degerleri saklayabilir
unsigned char v_uchar; // unsigned 1-byte veri tipidir. 0_255 arasindaki degerleri saklayabilir. unsigned char olarak da tanimlanabilir
// 2-byte'lik veri tipleri
int v_int; // signed 2-byte veri tipidir. -32768_32767 arasindaki degerleri saklayabilir
unsigned int v_uint; // unsigned 2-byte veri tipidir. 0_65535 arasindaki degerleri saklayabilir
// 4-byte'lik veri tipleri
long v_long; // signed 4-byte veri tipidir. -2147483648_2147483647 arasindaki degerleri saklayabilir
unsigned long v_ulong; //unsigned 4-byte veri tipidir. 0_4294967295 arasindaki degerleri saklayabilir

// Floating-Point tipi degisken
// Float tipi degiskenlerde unsigned-signed ayrimi yoktur. Hepsi signed degisken tipleridir
// Single Precision (4-byte) veri tipi
float v_float;

// Arduino yazilim arayuzundeki ana fonksiyonlar

void setup(){
    // Karta enerji verildigi anda ilk olarak calisan fonksiyondur.
    // Kart calismaya devam ettigi surece tekrar cagirilmaz
    // Baslangicta pinlerin giris-cikis durumlarini, seri protokollerin baslangic komutlarini calistirmak için kullanilir
    pinMode(13, OUTPUT); // Ilk arguman olarak verilen pinin ikinci argumanla giris-cikis durumunu ayarlar
}

void loop(){
    // Kart calistigi sure boyunca surekli olarak calistirilan fonksiyondur
    // Fonksiyonun sonuna geldigi anda basa doner
    // Ana islemler genellikle bu fonksiyon icerisine yazilir
    digitalWrite(13, HIGH); //Ilk arguman olarak verilen pinin ikinci argumanla 1-0 olmasi durumunu ayarlar
    delay(1000); // milisaniye cinsinden verilen sure boyunca programin calismasini durdurur
    digitalWrite(13, LOW);
    delay(1000);
}