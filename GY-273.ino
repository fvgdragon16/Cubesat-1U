#include <Wire.h> //подключаем библиотек для работы по I2C шине
#include <MechaQMC5883.h> //подключаем библиотеку для магнитометра GY-273

MechaQMC5883 magnetometr; //создаем объект magnetometr 
  
void setup() 
{
  Wire.begin(); //запускаем I2C шину

  Serial.begin(9600); //устанавливаем скорость связи 9600

  magnetometr.init(); //инициализируем магнитометр 
}

void loop() 
{
  int forM = 0; //создаем переменую для цикла for() для калибровки значений магнитометра
  int valuesM[3] = {0}; //создаем массив для значений магнитометра

  int x, y, z; //создаем перменые для хранения значений магнитометра с осей X, Y и Z
  magnetometr.read(&x, &y, &z); //считываем и записываем значения магнитометра с осей X, Y и Z 
  
  valuesM[0] = atan2(x, y) / 0.0174532925; //перерводим значения в градусы с плоскости XY
  valuesM[1] = atan2(x, z) / 0.0174532925; //перерводим значения в градусы с плоскости XZ
  valuesM[2] = atan2(y, z) / 0.0174532925; //перерводим значения в градусы с плоскости YZ

  for(forM = 0; forM < 3; forM++) {
    valuesM[forM] = map(valuesM[forM], -180, 180, 0, 360); //конвертируем значения с плоскостей магнитометра в диапозон 0 - 360 
  }

  //отладка
  //Serial.print("XY: ");
  //Serial.println(valuesM[0]); //выводим значения с плоскости XY

  //Serial.print("XZ: ");
  //Serial.println(valuesM[1]); //выводим значения с плоскости XZ

  //Serial.print("YZ: ");
  //Serial.println(valuesM[2]); //выводим значения с плоскости YZ

  //Serial.println("//");
}