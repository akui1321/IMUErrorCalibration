#include "AccelCalibrationCalculator.h"

AccelCalibrationCalculator::AccelCalibrationCalculator(const std::vector<double> &averages_x_up,
                                                       const std::vector<double> &averages_x_down,
                                                       const std::vector<double> &averages_y_up,
                                                       const std::vector<double> &averages_y_down,
                                                       const std::vector<double> &averages_z_up,
                                                       const std::vector<double> &averages_z_down) {
  
  L = Eigen::MatrixXd(3, 6);
  M = Eigen::MatrixXd(3, 4);
  A = Eigen::MatrixXd(4, 6);

  for (int i = 0; i < 3; ++i) {
    L.row(i) << averages_x_up[3-i], averages_x_down[3-i], averages_y_up[3-i], averages_y_down[3-i], averages_z_up[3-i], averages_z_down[3-i];
  }

  A.fill(0);
  for (int i = 0; i < 6; ++i){
    A(3, i) = 1;
  }

  A(0, 0) = g;
  A(0, 1) = -g;
  A(1, 2) = g;
  A(1, 3) = -g;
  A(2, 4) = g;
  A(2, 5) = -g;

  M.fill(0);
}

// Calibration of the accelerometer
Eigen::MatrixXd AccelCalibrationCalculator::calculateResult() {
  M = L * A.transpose() * (A * A.transpose()).inverse();
  return M;
}
