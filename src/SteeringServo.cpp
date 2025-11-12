#include "SteeringServo.h"

SteeringServo::SteeringServo() {
  // Default-Konstruktor für globale Initialisierung
  pin = 0;
  rest_position = 90;
  current_steering_degree = 90;
  max_steering_degree = 0;
  deadzone = 0;
}

SteeringServo::SteeringServo(int _pin, int _rest_position, int _max_steering_degree, int _deadzone) {
  pin = _pin;
  rest_position = _rest_position;
  current_steering_degree = rest_position;
  max_steering_degree = _max_steering_degree;
  deadzone = _deadzone;

  servo.attach(pin);
  delay(500);
  servo.write(rest_position);
}

void SteeringServo::steer(int steering_vector) {
  steering_vector = percentToDegree(steering_vector);
  int target_steering_degree = current_steering_degree + steering_vector;

  if (target_steering_degree < rest_position - max_steering_degree) {
    target_steering_degree = rest_position - max_steering_degree;
  } else if (target_steering_degree > rest_position + max_steering_degree) {
    target_steering_degree = rest_position + max_steering_degree;
  } else if (target_steering_degree < rest_position + deadzone && target_steering_degree > rest_position) {
    target_steering_degree = rest_position;
  } else if (target_steering_degree > rest_position - deadzone && target_steering_degree < rest_position) {
    target_steering_degree = rest_position;
  }

  servo.write(target_steering_degree);
  current_steering_degree = target_steering_degree;
}

int SteeringServo::percentToDegree(int steering_percent) {
  int steering_degree = (steering_percent * max_steering_degree) / 100;
  return steering_degree;
}

int SteeringServo::getCurrentSteeringDegree() {
  return current_steering_degree;
}

void SteeringServo::setRestPosition() {
  servo.write(rest_position);
  current_steering_degree = rest_position;
}
