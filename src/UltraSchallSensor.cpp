#include "UltraSchallSensor.h"

UltraSchallSensor::UltraSchallSensor() {
    pinTrig = 22;
    pinEcho = 23;   
    max_distance = 1000; // in cm 
    current_distance = 0;
    delayTime = 50; // Zeit zwischen den Messungen in ms
    USLoopRunning = false;
    initialized = false;

    UltraSchallLoopState = false;
    
}

UltraSchallSensor::UltraSchallSensor(int trigPin, int echoPin, int maxDist, int delayT) {
    pinTrig = trigPin;
    pinEcho = echoPin;   
    max_distance = maxDist; // in cm 
    current_distance = 0;
    delayTime = delayT; // Zeit zwischen den Messungen in ms
    initialized = false;
}

void UltraSchallSensor::setMaxDistance(int maxDist) {
    max_distance = maxDist;
}
void UltraSchallSensor::setDelayTime(int DelayT) {
    delayTime = DelayT;
}
int UltraSchallSensor::getMaxDistance() {
    return max_distance;
}
float UltraSchallSensor::getCurrentDistance() {
    return current_distance;
}

void UltraSchallSensor::begin() {
    pinMode(pinTrig, OUTPUT);
    pinMode(pinEcho, INPUT);
    USLoopRunning = false;
    initialized = true;

}

void UltraSchallSensor::measureDistance() {
    
    if(!initialized) {
        return; // Sensor nicht initialisiert
    }

    // Trigger-Signal senden
    digitalWrite(pinTrig, LOW);
    delayMicroseconds(2);
    digitalWrite(pinTrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinTrig, LOW);

    // Echo-Signal empfangen
    long duration = pulseIn(pinEcho, HIGH, max_distance * 58); // Timeout basierend auf max_distance

    // Distanz berechnen (in cm)
    int distance = duration / 58;

    // Überprüfen ob die gemessene Distanz innerhalb des maximalen Bereichs liegt
    if (distance == 0 || distance > max_distance) {
        current_distance = -1; // Ungültige Messung
    } else {
        current_distance = distance;
    }
}

void UltraSchallSensor::stopUltraSchallSensorLoop() {

    if(!USLoopRunning){
        return;
    }
    
    UltraSchallTicker.detach();
    USLoopRunning = false;
}

void UltraSchallSensor::ultraSchallSensorLoop() {

    if(USLoopRunning){
        return;
    }
    UltraSchallTicker.attach_ms(delayTime, measureDistanceCallBack, this); 
}

void UltraSchallSensor::measureDistanceCallBack(UltraSchallSensor* instance){

    instance->measureDistance();
}