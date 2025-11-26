#ifndef ULTRASCHALL_SENSOR_H
#define ULTRASCHALL_SENSOR_H

#include <Arduino.h>
#include <Motor.h>

class UltraSchallSensor {
private:
    int pinTrig; // Trigger Pin
    int pinEcho; // Echo Pin
    int max_distance; // maximale Distanz in cm
 // aktuelle Distanzmessung
    int delayTime; // Zeit zwischen den Messungen in ms
    bool USLoopRunning;
    bool initialized; // Flag ob begin() aufgerufen wurde

    Ticker UltraSchallTicker;
    bool UltraSchallLoopState;
    void measureDistance();

    void ultraSchallSensorLoop();
    static void measureDistanceCallBack(UltraSchallSensor* instance);
    void stopUltraSchallSensorLoop();

public:
    float current_distance;
    UltraSchallSensor(int trigPin, int echoPin, int maxDist, int delayT);
    UltraSchallSensor(); // Default-Konstruktor

    void begin(); // Muss in setup() aufgerufen werden!
    void setMaxDistance(int maxDist);
    void setDelayTime(int DelayT);
    int getMaxDistance();
    float getCurrentDistance();
};

#endif // ULTRASCHALL_SENSOR_H
