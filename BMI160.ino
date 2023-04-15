#include <DFRobot_BMI160.h> //подключаем библиотеку для акселерометра + гироскопа BMI160 

DFRobot_BMI160 accelerometerGyroscope; //создаем объект accelerometerGyroscope

void setup()
{
  Serial.begin(9600); //устанавливаем скорость связи 9600

  accelerometerGyroscope.softReset(); //инициализируем акселерометр + гироскоп
  accelerometerGyroscope.I2cInit(0x69); //подключаем датчик акселерометра + гиолскопа к адресу I2C 0x69
}

void loop()
{
  int forAG = 0; //создаем переменую для цикла for(), для калибровки значений акселерометра + гироскопа
  int valuesAG[6] = {0}; //создаем массив для значений акселерометра + гироскопа; (0 - 2) - значения акселерометра; (3 - 5) - значения гироскопа

  accelerometerGyroscope.getAccelGyroData(valuesAG); //записываем данные с акселерометра + гироскопа в массив values
  
  for(forAG = 0; forAG < 6; forAG++) { //калибруем значения акселерометра + гироскопа

    if (forAG < 3) { //калибруем значения гироскопа
      valuesAG[forAG] = valuesAG[forAG] / 16.4; //переводим згачения в градусы
      //отладка
      //Serial.print("A: "); //выводим значения гироскопа
      //Serial.println(valuesAG[forAG]); //вывод данных с осей X, Y и Z  
    }

    else { //калибруем значения акселерометра
      valuesAG[forAG] = valuesAG[forAG] / 1670.13; //переводим значения в м/с*с
      //отладка
      //Serial.print("G: "); //выводим значения акселерометра
      //Serial.println(valuesAG[forAG]); //вывод данных с осей X, Y и Z   
    }

  }
}