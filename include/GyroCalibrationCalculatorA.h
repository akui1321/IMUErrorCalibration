#ifndef GYROCALIBRATIONCALCULATORA_H
#define GYROCALIBRATIONCALCULATORA_H

#define pi 3.1415926535897932384626433832795028841971

// Gyroscope Calibration Using Static Method
class GyroCalibrationCalculatorA {
private:
  double phi = 30.531651244 / 180.0 * pi;
  double omega = 7.292115e-5;
  double b = 0.0, s = 0.0;
  double up = 0.0, down = 0.0;

public:
  GyroCalibrationCalculatorA(double up, double down);
  void calculate();
  double getValueb();
  double getValues();
};

#endif
