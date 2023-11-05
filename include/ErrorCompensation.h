#ifndef ERROR_COMPENSATION_H
#define ERROR_COMPENSATION_H

#include </usr/include/eigen3/Eigen/Dense>
#include <vector>

class ErrorCompensation {
private:
  Eigen::MatrixXd mc; // 3x1 matrix
  Eigen::MatrixXd m; // 3x1 matrix
  Eigen::MatrixXd b; // 3x1 matrix
  Eigen::Matrix3d comp; // 3x3 matrix
  std::vector<std::vector<double>> RawData;
  bool acc;
  std::vector<std::vector<double>> result;

public:
  ErrorCompensation(const std::vector<std::vector<double>> &rawData, const Eigen::MatrixXd &M);

  // Overloaded constructor
  ErrorCompensation(const std::vector<std::vector<double>> &rawData, double sx, double sy, double sz, double bx, double by, double bz);

  std::vector<std::vector<double>> calculateResultMatrix();
};

#endif 
