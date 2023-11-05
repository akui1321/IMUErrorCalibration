#include "GyroCalibrationCalculatorB.h"
#include <cmath>

GyroCalibrationCalculatorB::GyroCalibrationCalculatorB(const std::vector<std::vector<double>> &data1, const std::vector<std::vector<double>> &data2) : data1(data1), data2(data2) {
}

// Calculate the total rotation angle
double GyroCalibrationCalculatorB::calculateDistance(double time1, double time2, double speed2) const {
  return speed2 * (time2 - time1);
}

void GyroCalibrationCalculatorB::getTotalDistanceX() {
  int data1_start = checkThreshold(data1, 6);
  int data2_start = checkThreshold(data2, 6);
  for (size_t i = 0; i < 4000; ++i) {
    alpha1 += calculateDistance(data1[data1_start][0], data1[data1_start + 1][0], data1[data1_start + 1][6]);
    alpha2 += calculateDistance(data2[data2_start][0], data2[data2_start + 1][0], data2[data2_start + 1][6]);
    data1_start++;
    data2_start++;
  }
}

void GyroCalibrationCalculatorB::getTotalDistanceY() {
  int data1_start = checkThreshold(data1, 5);
  int data2_start = checkThreshold(data2, 5);
  for (size_t i = 0; i < 4000; ++i) {
    alpha1 += calculateDistance(data1[data1_start][0], data1[data1_start + 1][0], data1[data1_start + 1][5]);
    alpha2 += calculateDistance(data2[data2_start][0], data2[data2_start + 1][0], data2[data2_start + 1][5]);
    data1_start++;
    data2_start++;
  }
}

void GyroCalibrationCalculatorB::getTotalDistanceZ() {
  int data1_start = checkThreshold(data1, 4);
  int data2_start = checkThreshold(data2, 4);
  for (size_t i = 0; i < 4000; ++i) {
    alpha1 += calculateDistance(data1[data1_start][0], data1[data1_start + 1][0], data1[data1_start + 1][4]);
    alpha2 += calculateDistance(data2[data2_start][0], data2[data2_start + 1][0], data2[data2_start + 1][4]);
    data1_start++;
    data2_start++;
  }
}

// Calculate the bias and scale factor
void GyroCalibrationCalculatorB::calculate() {
  b = (alpha1 + alpha2) / 2.0 / 40.0 - (omega * sin(phi));
  s = (alpha1 - alpha2) / 2.0 / 2.0 / pi - 1;
}

double GyroCalibrationCalculatorB::Getb() {
  return b;
}

double GyroCalibrationCalculatorB::Gets() {
  return s;
}

// Determine if it has started rotating
int GyroCalibrationCalculatorB::checkThreshold(const std::vector<std::vector<double>> &data,int m) {
  int p;
  for (int i = 0; i < data.size() - 100; ++i) {
    double diff = std::abs(data[i][m] - data[i + 100][m]);
    if (diff > 0.0523598775598298873077107230546583814032) {
      p = i;
      break;
    }
  }
  return p;
}
