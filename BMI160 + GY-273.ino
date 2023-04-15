#include <Wire.h> //подключаем библиотек для работы по I2C шине
#include <MechaQMC5883.h> //подключаем библиотеку для магнитометра GY-273
#include <DFRobot_BMI160.h> //подключаем библиотеку для акселерометра + гироскопа BMI160

MechaQMC5883 magnetometr; //создаем объект magnetometr
DFRobot_BMI160 accelerometerGyroscope; //создаем объект accelerometerGyroscope
  
void setup() 
{
  Wire.begin(); //запускаем I2C шину
  Serial.begin(9600); //устанавливаем скорость связи 9600

  magnetometr.init(); //инициализируем магнитометр
  accelerometerGyroscope.softReset(); //инициализируем акселерометр + гироскоп
  accelerometerGyroscope.I2cInit(0x69); //подключаем датчик акселерометра + гироскопа к адресу I2C 0x69
}

void loop() 
{
  int forM = 0; //создаем переменную для цикла for() для калибровки значений магнитометра
  int forAG = 0; //создаем переменную для цикла for(), для калибровки значений акселерометра + гироскопа

  int x, y, z; //создаем переменные для хранения значений магнитометра с осей X, Y и Z
  
  int valuesM[3] = {0}; //создаем массив для значений магнитометра
  int valuesAG[6] = {0}; //создаем массив для значений акселерометра + гироскопа; (0 - 2) - значения акселерометра; (3 - 5) - значения гироскопа

  magnetometr.read(&x, &y, &z); //считываем и записываем значения магнитометра с осей X, Y и Z
  accelerometerGyroscope.getAccelGyroData(valuesAG); //записываем данные с акселерометра + гироскопа в массив values
  
  //калибруем значения магнитометра
  valuesM[0] = atan2(x, y) / 0.0174532925; //переводим значения в градусы с плоскости XY
  valuesM[1] = atan2(x, z) / 0.0174532925; //переводим значения в градусы с плоскости XZ
  valuesM[2] = atan2(y, z) / 0.0174532925; //переводим значения в градусы с плоскости YZ

  for(forM = 0; forM < 3; forM++) {
    valuesM[forM] = map(valuesM[forM], -180, 180, 0, 360); //конвертируем значения с плоскостей магнитометра в диапазон 0 - 360 
  }

  //отладка магнитометра
  Serial.print("XY: ");
  Serial.println(valuesM[0]); //выводим значения с плоскости XY

  Serial.print("XZ: ");
  Serial.println(valuesM[1]); //выводим значения с плоскости XZ

  Serial.print("YZ: ");
  Serial.println(valuesM[2]); //выводим значения с плоскости YZ

  //Serial.println("//");

  //калибруем значения акселерометра + гироскопа
  for(forAG = 0; forAG < 6; forAG++) { //калибруем значения акселерометра + гироскопа

    if (forAG < 3) { //калибруем значения гироскопа
      valuesAG[forAG] = valuesAG[forAG] / 16.4; //переводим значения в градусы
      //отладка гироскопа
      Serial.print("A: "); //выводим значения гироскопа
      Serial.println(valuesAG[forAG]); //вывод данных с осей X, Y и Z  
    }

    else { //калибруем значения акселерометра
      valuesAG[forAG] = valuesAG[forAG] / 1670.13; //переводим значения в м/с*с
      //отладка акселерометра
      Serial.print("G: "); //выводим значения акселерометра
      Serial.println(valuesAG[forAG]); //вывод данных с осей X, Y и Z   
    }

  }

}