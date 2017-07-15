#include <SPI.h>
#include <MFRC522.h>

const int RST_PIN = 9; // пин RST
const int SS_PIN = 10; // пин SDA (SS)
int piezo = 5;
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600); // инициализация послед. порта
  SPI.begin(); // инициализация шины SPI
  mfrc522.PCD_Init(); // инициализация считывателя RC522
  pinMode(piezo, OUTPUT);
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent())
    if (mfrc522.PICC_ReadCardSerial())
    {
        dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
        delay(1500);
    }
}
void dump_byte_array(byte *buffer, byte bufferSize)
{  
  for (byte i = 0; i < bufferSize; i++)
  {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
  Serial.println();
}

