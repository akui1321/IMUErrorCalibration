#ifndef GYROCALIBRATIONCALCULATORB_H
#define GYROCALIBRATIONCALCULATORB_H

#define pi 3.1415926535897932384626433832795028841971

#include <vector>

// Gyroscope Calibration Using Two-Position Method
class GyroCalibrationCalculatorB {
public:
  GyroCalibrationCalculatorB(const std::vector<std::vector<double>> &data1, const std::vector<std::vector<double>> &data2);
  
  void getTotalDistanceX();
  void getTotalDistanceY();
  void getTotalDistanceZ();
  void calculate();
  double Getb();
  double Gets();
  double alpha1, alpha2;  
private:
  std::vector<std::vector<double>> data1;
  std::vector<std::vector<double>> data2;

  double phi = 30.531651244 / 180.0 * pi;
  double omega = 7.292115e-5;
  double b;
  double s;

  double calculateDistance(double time1, double time2, double speed2) const;

  int checkThreshold(const std::vector<std::vector<double>> &data, int m);
};

#endif
