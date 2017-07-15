#include <SPI.h>
#include <Ethernet.h>
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//char server[] = {192,168,1,33};  
char server[] = {192,168,1,33};   
IPAddress ip(192, 168, 1, 13);
EthernetClient client;
void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac);
  // Дадим время шилду на инициализацию
  delay(1000);
  Serial.println("connecting...");
  if (client.connect(server, 666)) {
    Serial.println("---------------");
    client.println("Hello");
    client.println();
  } 
  else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}
void loop() {
  delay(10000);
  // Если есть доступные биты, читаем их и выводим на экран
  while (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
  // Если соединение прервано, отключаем клиент
  if (!client.connected()) {
    Serial.println();
    Serial.println("---------------");
    Serial.println("disconnecting");
    client.stop();
    // Останавливаем выполнение программы
    while (true);
  }
}
