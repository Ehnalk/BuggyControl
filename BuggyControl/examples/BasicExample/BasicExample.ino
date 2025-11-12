#include <Arduino.h>
#include <BuggyControl.h>

// Beispiel-Setup für die BuggyControl-Bibliothek

// Motor initialisieren
Motor motor(13,      // pin_front
            12,      // pin_back
            100,     // max_duty
            30,      // min_duty
            1000,    // direction_change_delay (ms)
            10000);  // freq (Hz)

// Servo initialisieren
SteeringServo steering(23,   // pin
                       90,   // rest_position
                       20,   // max_steering_degree
                       6);   // deadzone

// LEDs initialisieren
LEDManager leftIndicator({16}, 0, 100, 1000);    // Pin 16, aus, 100% brightness, 1kHz
LEDManager rightIndicator({5}, 0, 100, 1000);    // Pin 5, aus, 100% brightness, 1kHz
LEDManager frontLights({19}, 1, 100, 1000);      // Pin 19, an, 100% brightness, 1kHz
LEDManager rearLights({18}, 1, 100, 1000);       // Pin 18, an, 100% brightness, 1kHz

void setup() {
  Serial.begin(115200);
  Serial.println("BuggyControl Test gestartet...");

  // Pins als Output setzen
  pinMode(16, OUTPUT); // Blinker links
  pinMode(19, OUTPUT); // Frontlicht
  pinMode(5, OUTPUT);  // Blinker rechts
  pinMode(18, OUTPUT); // Rücklicht
  pinMode(23, OUTPUT); // Servo

  Serial.println("BuggyControl Bibliothek initialisiert!");
  Serial.println("Teste Motor...");

  // Teste Motor vorwärts
  motor.changeSpeed(50);  // 50% vorwärts
  delay(2000);
  motor.changeSpeed(-50); // Stopp
  delay(1000);

  Serial.println("Teste Lenkung...");
  // Teste Lenkung
  steering.steer(50);  // 50% rechts
  delay(1000);
  steering.steer(-100); // zurück und 50% links
  delay(1000);
  steering.setRestPosition(); // zurück zur Mitte

  Serial.println("Teste LEDs...");
  // Teste Blinker
  leftIndicator.startIndicating();
  delay(3000);
  leftIndicator.stopIndicating();

  rightIndicator.startIndicating();
  delay(3000);
  rightIndicator.stopIndicating();

  Serial.println("Setup abgeschlossen!");
}

void loop() {
  // Hier kann deine Loop-Logik rein
  delay(100);
}
