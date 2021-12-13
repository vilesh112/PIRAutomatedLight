#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#define pin_pir 6
#define pin_led_red 2
#define pin_led_green 3
#define pin_led_blue 4
#define pin_out 8

int pir_state = 0, pir_previous_state = 0;
LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup()
{
    lcd.init();
    lcd.backlight();
    lcd.home();
    pinMode(pin_pir, INPUT);
    pinMode(pin_led_red, OUTPUT);
    pinMode(pin_led_green, OUTPUT);
    pinMode(pin_led_blue, OUTPUT);
    pinMode(pin_out, OUTPUT);
    lcd.print("Setting Up");
    lcd.blink();
    delay(7000);
    lcd.setCursor(0, 1);
    lcd.clear();
    lcd.print("Ready");
    delay(1000);
    lcd.noBlink();
    lcd.clear();
    lcd.noBacklight();
    digitalWrite(pin_led_green, HIGH);
}
void loop()
{
    pir_state = digitalRead(pin_pir);
    if (pir_state == HIGH && pir_previous_state == LOW)
    {
        lcd.backlight();
        lcd.clear();
        digitalWrite(pin_out, HIGH);
        digitalWrite(pin_led_blue, HIGH);        
        digitalWrite(pin_led_green, LOW);
        lcd.setCursor(0, 0);
        lcd.print("Motion Detected");
        lcd.setCursor(0, 1);
        lcd.print("Welcome Home");
        pir_previous_state = 1;
        delay(3000);
    }
    else if (pir_state == LOW && pir_previous_state == HIGH)
    {
        digitalWrite(pin_out, LOW);
        digitalWrite(pin_led_blue, LOW);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Motion not");
        lcd.setCursor(0, 1);
        lcd.print("Detected, Bye...");
        pir_previous_state = 0;
        digitalWrite(pin_led_red, HIGH);
        digitalWrite(pin_led_green, LOW);
        delay(5000);
        digitalWrite(pin_led_green, HIGH);
        digitalWrite(pin_led_red, LOW);
        lcd.noBacklight();
    }
}