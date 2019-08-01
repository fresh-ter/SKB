// пины для подключения контактов STEP, DIR
#define STEP_PIN 8
#define DIR_PIN 9

// задержка между шагами двигателя
#define DELAY_STEPS 50

// количество шагов на 1 оборот
#define STEP_ROUND 200



#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
Adafruit_PCD8544 display = Adafruit_PCD8544(3, 4, 5, 6, 7);

int counter = 0;
int counter_static = 10;
int time_start = 0; // в секундах
int time_end = 0; // в секундах
String value;

void setup() {
  //Serial.begin(9600);

  // инициализация и очистка дисплея
  display.begin();
  display.clearDisplay();
  display.display();

  display.setContrast(60); // установка контраста
  delay(1000);
  display.setTextSize(1);  // установка размера шрифта
  display.setTextColor(BLACK); // установка цвета текста
  display.setCursor(0, 0); // установка позиции курсора

  display.println("Hello, world!");
  display.display();


  // режим для STEP и DIR как OUTPUT
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  // начальные значения
  digitalWrite(STEP_PIN, 1);
  digitalWrite(DIR_PIN, 0);


  //  // Крутимся в одну сторону
  //  digitalWrite(DIR_PIN, HIGH);
  //  //  1 оборот
  //  for (int i = 0; i < STEP_ROUND; i++) {
  //    digitalWrite(STEP_PIN, HIGH);
  //    delay(DELAY_STEPS);
  //    digitalWrite(STEP_PIN, LOW);
  //    delay(DELAY_STEPS);
  //  }
}

void loop() {
  //  if (Serial.available() > 0) {  //если есть доступные данные
  //    // считываем байт
  //    value = Serial.readString();
  //
  //    //value = atoi(incomingByte);
  //
  //
  //
  //    if (value == "100")
  //    {
  //      digitalWrite(DIR_PIN, LOW);
  //      //  1 оборот
  //      for (int i = 0; i < STEP_ROUND; i++) {
  //        digitalWrite(STEP_PIN, HIGH);
  //        delay(DELAY_STEPS);
  //        digitalWrite(STEP_PIN, LOW);
  //        delay(DELAY_STEPS);
  //      }
  //    }
  //  }

  digitalWrite(DIR_PIN, LOW);


  for (counter; counter <= counter_static; counter++)
  {
    if(counter == 0)
      time_start = millis()/1000;
    if(counter == 1)
      time_end = (millis()/1000 - time_start)*counter_static;

    play_display();
    
    //  1 оборот
    for (int i = 0; i < STEP_ROUND; i++) {
      digitalWrite(STEP_PIN, HIGH);
      digitalWrite(STEP_PIN, LOW);
      delay(DELAY_STEPS);
    }
  }



  //  // Крутимся в одну сторону
  //  digitalWrite(DIR_PIN, HIGH);
  //  //  1 оборот
  //  for (int i = 0; i < STEP_ROUND; i++) {
  //    digitalWrite(STEP_PIN, HIGH);
  //    delay(DELAY_STEPS);
  //    digitalWrite(STEP_PIN, LOW);
  //    delay(DELAY_STEPS);
  //  }
  //  // Затем меняем направление и крутимся в другую сторону
  //  digitalWrite(DIR_PIN, LOW);
  //  // сделать 1 оборот
  //  for (int i = 0; i < STEP_ROUND; i++) {
  //    digitalWrite(STEP_PIN, HIGH);
  //    delay(DELAY_STEPS);
  //    digitalWrite(STEP_PIN, LOW);
  //    delay(DELAY_STEPS);
  //  }
}

void play_display()
{
  display.clearDisplay();
  display.display();

  //display.setContrast(60); // установка контраста
  //delay(1000);
  //display.setTextSize(1);  // установка размера шрифта
  //display.setTextColor(BLACK); // установка цвета текста
  display.setCursor(0, 0); // установка позиции курсора

  display.println("Mode: ###");
  display.println("Turns: " + String(counter) + "/" + String(counter_static));
  display.println("Time: " + String((millis()/1000 - time_start)) + "/" + String(time_end));
  display.display();
}
