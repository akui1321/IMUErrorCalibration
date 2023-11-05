#include "ErrorCompensation.h"

// Accelerometer Data Compensation
ErrorCompensation::ErrorCompensation(const std::vector<std::vector<double>> &rawData, const Eigen::MatrixXd &M) {
  acc = true;
  RawData = rawData;
  mc = Eigen::MatrixXd(3, 1);
  m = Eigen::MatrixXd(3, 1);
  b = Eigen::MatrixXd(3, 1);
  comp = Eigen::MatrixXd(3, 3);

  comp = M.block(0, 0, 3, 3);
  b = M.block(0, 3, 3, 1);
}

// Gyroscope Data Compensation
ErrorCompensation::ErrorCompensation(const std::vector<std::vector<double>> &rawData, double sx, double sy, double sz, double bx, double by, double bz) {
  // Assuming that the input matrix is correctly sized.
  acc = false;
  RawData = rawData;
  mc = Eigen::MatrixXd(3, 1);
  m = Eigen::MatrixXd(3, 1);
  b = Eigen::MatrixXd(3, 1);
  comp = Eigen::Matrix3d::Identity();

  comp(0, 0) += sx;
  comp(1, 1) += sy;
  comp(2, 2) += sz;

  b(0, 0) = bx;
  b(1, 0) = by;
  b(2, 0) = bz;
}

std::vector<std::vector<double>> ErrorCompensation::calculateResultMatrix() {
  if(acc) {
    for (auto &entry : RawData) {
      for (int i = 0; i < 3; ++i) {
        m(i, 0) = entry[3 - i];
      }
      
      mc = comp.inverse() * (m - b);
      result.push_back({entry[0], mc(0, 0), mc(1, 0), mc(2, 0)});
    }

    return result;
  } 
  else {
    for (auto &entry : RawData) {
      for (int i = 0; i < 3; ++i) {
        m(i, 0) = entry[6 - i];
      }

      mc = comp.inverse() * (m - b);
      result.push_back({entry[0], mc(0, 0), mc(1, 0), mc(2, 0)});
    }

    return result;
  }
}
