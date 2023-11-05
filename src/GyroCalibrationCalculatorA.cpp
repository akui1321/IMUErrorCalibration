#include "GyroCalibrationCalculatorA.h"
#include <cmath>

GyroCalibrationCalculatorA::GyroCalibrationCalculatorA(double up, double down)
    : up(up), down(down) {}

// Gyroscope Calibration Using Static Method
void GyroCalibrationCalculatorA::calculate() {
  b = (up + down) / 2.0;
  s = (up - down) / 2.0 / omega / sin(phi) - 1;
}

double GyroCalibrationCalculatorA::getValueb() {
  return b;
}

double GyroCalibrationCalculatorA::getValues() {
  return s;
}