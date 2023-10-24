#include <OneWire.h>
/*
* Описание взаимодействия с цифровым датчиком ds18b20 
* Подключение ds18b20 к ардуино через пин 8  
*/
OneWire ds(2); // Создаем объект OneWire для шины 1-Wire, с помощью которого будет осуществляться работа с датчиком
int counter = 0;
void setup(){
  Serial.begin(9600);
  Serial.println("Время, с || Температура");
  for (byte i = 3; i < 13; i++)
  pinMode(i, OUTPUT);
}

void loop(){
  // Определяем температуру от датчика DS18b20
  counter++;
  byte data[2]; // Место для значения температуры
  
  ds.reset(); // Начинаем взаимодействие со сброса всех предыдущих команд и параметров
  ds.write(0xCC); // Даем датчику DS18b20 команду пропустить поиск по адресу. В нашем случае только одно устрйоство 
  ds.write(0x44); // Даем датчику DS18b20 команду измерить температуру. Само значение температуры мы еще не получаем - датчик его положит во внутреннюю память
  
  delay(1000); // Микросхема измеряет температуру, а мы ждем.  
  
  ds.reset(); // Теперь готовимся получить значение измеренной температуры
  ds.write(0xCC); 
  ds.write(0xBE); // Просим передать нам значение регистров со значением температуры
 
  // Получаем и считываем ответ
  data[0] = ds.read(); // Читаем младший байт значения температуры
  data[1] = ds.read(); // А теперь старший

  // Формируем итоговое значение: 
  //    - сперва "склеиваем" значение, 
  //    - затем умножаем его на коэффициент, соответсвующий разрешающей способности (для 12 бит по умолчанию - это 0,0625)
  float temperature =  ((data[1] << 8) | data[0]) * 0.0625;
  
  // Выводим полученное значение температуры в монитор порта
  
  Serial.print(counter);
  Serial.print(" ");
 
 Serial.println(temperature);

  byte Number_100 = int(temperature) / 100;
  byte Number_10 = (int(temperature) % 100) / 10;
  byte Number_1 = int(temperature) % 10;
  
  Serial.println(Number_100);
  Serial.println(Number_10);
  Serial.println(Number_1);
 
  digitalWrite(3, !((Number_1 >> 0) & 0b0001));
  digitalWrite(4, !((Number_1 >> 1) & 0b0001));
  digitalWrite(5, !((Number_1 >> 2) & 0b0001));
  digitalWrite(6, !((Number_1 >> 3) & 0b0001));
  digitalWrite(7, !((Number_10 >> 0) & 0b0001));
  digitalWrite(8, !((Number_10 >> 1) & 0b0001));
  digitalWrite(9, !((Number_10 >> 2) & 0b0001));
  digitalWrite(10, !((Number_10 >> 3) & 0b0001));
  digitalWrite(11, !((Number_100 >> 0) & 0b0001));
  digitalWrite(12, !((Number_100 >> 1) & 0b0001));
  
  Serial.print((Number_1 >> 0) & 0b0001);
  Serial.print((Number_1 >> 1) & 0b0001);
  Serial.print((Number_1 >> 2) & 0b0001);
  Serial.print((Number_1 >> 3) & 0b0001);
  Serial.print((Number_10 >> 0) & 0b0001);
  Serial.print((Number_10 >> 1) & 0b0001);
  Serial.print((Number_10 >> 2) & 0b0001);
  Serial.print((Number_10 >> 3) & 0b0001);
  Serial.print((Number_100 >> 0) & 0b0001);
  Serial.print((Number_100 >> 1) & 0b0001);

}
