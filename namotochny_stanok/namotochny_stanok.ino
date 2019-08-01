// пины для подключения контактов STEP, DIR
#define STEP_PIN 8
#define DIR_PIN 9

// задержка между шагами двигателя
#define DELAY_STEPS 1

// количество шагов на 1 оборот
#define STEP_ROUND 800


#define MULTIPLEXER_S0 A0
#define MULTIPLEXER_S1 A1
#define MULTIPLEXER_S2 A2
#define MULTIPLEXER_D0 A3
#define MULTIPLEXER_D1 A4

#define GET_BIT(value, bit_number) (((value) >> (bit_number)) & 0x1)


#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
Adafruit_PCD8544 display = Adafruit_PCD8544(3, 4, 5, 6, 7);

int mode = 0;
enum statuses {CONF, WORK, STOP};
char *menu_str[] =
{
  "CONF",
  "WORK",
  "END",
  "STOP"
};


int counter = 0;
int counter_static = 0;
int time_start = 0; // в секундах
int time_end = 0; // в секундах
String value;

int b1[8];
int b2[8];

void setup() {
  Serial.begin(9600);

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

  pinMode(MULTIPLEXER_S0, OUTPUT);
  pinMode(MULTIPLEXER_S1, OUTPUT);
  pinMode(MULTIPLEXER_S2, OUTPUT);

  pinMode(MULTIPLEXER_D0, INPUT);
  digitalWrite(MULTIPLEXER_D0, HIGH);
  pinMode(MULTIPLEXER_D1, INPUT);
  digitalWrite(MULTIPLEXER_D1, HIGH);

  //  // Крутимся в одну сторону
  //  digitalWrite(DIR_PIN, HIGH);
  //  //  1 оборот
  //  for (int i = 0; i < STEP_ROUND; i++) {
  //    digitalWrite(STEP_PIN, HIGH);
  //    delay(DELAY_STEPS);
  //    digitalWrite(STEP_PIN, LOW);
  //    delay(DELAY_STEPS);
  //  }

  play_display();
}

void loop() {

  if (Serial.available() > 0) {  //если есть доступные данные
    // считываем байт
    value = Serial.readString();

    if (value == "set_turns")
    {
      while (true)
      {
        if (Serial.available() > 0) {  //если есть доступные данные
          // считываем байт
          String s = Serial.readString();
          counter_static = s.toInt();
          break;
        }
      }
    }
    else if (value == "start")
    {
      abc();
    }
    
    play_display();
  }


  //  get_data_multiplexer();
  //
  //  Serial.print(b1[0]);
  //  Serial.print(" ");
  //  Serial.print(b1[1]);
  //  Serial.print(" ");
  //  Serial.print(b1[2]);
  //  Serial.print(" ");
  //  Serial.print(b1[3]);
  //  Serial.print(" ");
  //  Serial.print(b1[4]);
  //  Serial.print(" ");
  //  Serial.print(b1[5]);
  //  Serial.print(" ");
  //  Serial.print(b1[6]);
  //  Serial.print(" ");
  //  Serial.println(b1[7]);
  //
  //  Serial.print(b2[0]);
  //  Serial.print(" ");
  //  Serial.print(b2[1]);
  //  Serial.print(" ");
  //  Serial.print(b2[2]);
  //  Serial.print(" ");
  //  Serial.print(b2[3]);
  //  Serial.print(" ");
  //  Serial.print(b2[4]);
  //  Serial.print(" ");
  //  Serial.print(b2[5]);
  //  Serial.print(" ");
  //  Serial.print(b2[6]);
  //  Serial.print(" ");
  //  Serial.println(b2[7]);
  //
  //  Serial.println();
  //
  //  delay(1000);
}

void abc()
{
  mode = 1;
  digitalWrite(DIR_PIN, LOW);

  for (counter; counter < counter_static; counter++)
  {
    if (counter == 0)
      time_start = millis() / 1000;
    if (counter == 1)
      time_end = (millis() / 1000 - time_start) * counter_static;

    play_display();

    //  1 оборот
    for (int i = 0; i < STEP_ROUND; i++) {
      digitalWrite(STEP_PIN, HIGH);
      delay(DELAY_STEPS);
      digitalWrite(STEP_PIN, LOW);
      delay(DELAY_STEPS);
    }
  }
  mode++;
}

void get_data_multiplexer()
{
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(MULTIPLEXER_S0, bitRead(i, 0));
    digitalWrite(MULTIPLEXER_S1, bitRead(i, 1));
    digitalWrite(MULTIPLEXER_S2, bitRead(i, 2));

    b1[i] = digitalRead(MULTIPLEXER_D0);
    b2[i] = digitalRead(MULTIPLEXER_D1);
  }
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

  display.println("Mode: " + String(menu_str[mode]));
  display.println("Turns: " + String(counter) + "/" + String(counter_static));
  display.println("Time: " + String((millis() / 1000 - time_start)) + "/" + String(time_end));
  display.display();
}
