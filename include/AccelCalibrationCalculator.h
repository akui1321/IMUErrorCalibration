#ifndef ACCEL_CALIBRATION_CALCULATOR_H
#define ACCEL_CALIBRATION_CALCULATOR_H

#include </usr/include/eigen3/Eigen/Dense>
#include <vector>

class AccelCalibrationCalculator {
private:
  Eigen::MatrixXd L; // 3x6 matrix
  Eigen::MatrixXd M; // 3x4 matrix
  Eigen::MatrixXd A; // 4x6 matrix
  double g = 9.7936174;

public:
  AccelCalibrationCalculator(const std::vector<double> &averages_x_up,
                             const std::vector<double> &averages_x_down,
                             const std::vector<double> &averages_y_up,
                             const std::vector<double> &averages_y_down,
                             const std::vector<double> &averages_z_up,
                             const std::vector<double> &averages_z_down);

  Eigen::MatrixXd calculateResult();
};

#endif 
