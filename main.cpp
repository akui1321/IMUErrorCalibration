#include "AccelCalibrationCalculator.h"
#include "ErrorCompensation.h"
#include "GyroCalibrationCalculatorA.h"
#include "GyroCalibrationCalculatorB.h"
#include "IMUDataReader.h"
#include "Plotter.h"
#include <iostream>
#include <iomanip>

int main() {
  std::vector<double> averages_x_up, averages_x_down, averages_y_up, averages_y_down, averages_z_up, averages_z_down;

  // Open all files and read the data
  IMUDataReader x_up("/home/akui/Downloads/imu_231008/imu_data/x_up.ASC");

  if (x_up.readDataFile()) {
    x_up.applyTransformations();
    x_up.calculateAverages();
    averages_x_up = x_up.getAverages();
  }

  IMUDataReader x_down("/home/akui/Downloads/imu_231008/imu_data/x_down.ASC");

  if (x_down.readDataFile()) {
    x_down.applyTransformations();
    x_down.calculateAverages();
    averages_x_down = x_down.getAverages();
  }

  IMUDataReader y_up("/home/akui/Downloads/imu_231008/imu_data/y_up.ASC");

  if (y_up.readDataFile()) {
    y_up.applyTransformations();
    y_up.calculateAverages();
    averages_y_up = y_up.getAverages();
  }

  IMUDataReader y_down("/home/akui/Downloads/imu_231008/imu_data/y_down.ASC");

  if (y_down.readDataFile()) {
    y_down.applyTransformations();
    y_down.calculateAverages();
    averages_y_down = y_down.getAverages();
  }

  IMUDataReader z_up("/home/akui/Downloads/imu_231008/imu_data/z_up.ASC");

  if (z_up.readDataFile()) {
    z_up.applyTransformations();
    z_up.calculateAverages();
    averages_z_up = z_up.getAverages();
  }

  IMUDataReader z_down("/home/akui/Downloads/imu_231008/imu_data/z_down.ASC");

  if (z_down.readDataFile()) {
    z_down.applyTransformations();
    z_down.calculateAverages();
    averages_z_down = z_down.getAverages();
  }

  IMUDataReader y_neg("/home/akui/Downloads/imu_231008/imu_data/y_neg.ASC");

  if (y_neg.readDataFile()) {
    y_neg.applyTransformations();
  }

  IMUDataReader y_pos("/home/akui/Downloads/imu_231008/imu_data/y_pos.ASC");

  if (y_pos.readDataFile()) {
    y_pos.applyTransformations();
  }

  IMUDataReader x_neg("/home/akui/Downloads/imu_231008/imu_data/x_neg.ASC");

  if (x_neg.readDataFile()) {
    x_neg.applyTransformations();
  }

  IMUDataReader x_pos("/home/akui/Downloads/imu_231008/imu_data/x_pos.ASC");

  if (x_pos.readDataFile()) {
    x_pos.applyTransformations();
  }

  IMUDataReader z_neg("/home/akui/Downloads/imu_231008/imu_data/z_neg.ASC");

  if (z_neg.readDataFile()) {
    z_neg.applyTransformations();
  }

  IMUDataReader z_pos("/home/akui/Downloads/imu_231008/imu_data/z_pos.ASC");

  if (z_pos.readDataFile()) {
    z_pos.applyTransformations();
  }

  // Calibration of the accelerometer
  AccelCalibrationCalculator AccelCalibration(averages_x_up, averages_x_down, averages_y_up, averages_y_down, averages_z_up, averages_z_down);
  Eigen::MatrixXd M = AccelCalibration.calculateResult();
  std::cout << "Accelerometer bias, Scale Factor and Cross-Axis Coupling Matrix: " << std::endl
            << M << std::endl
            << std::endl;

  // Gyroscope Calibration Using Static Method
  GyroCalibrationCalculatorA GyroCalibrationX(averages_x_up[6], averages_x_down[6]);
  GyroCalibrationCalculatorA GyroCalibrationY(averages_y_up[5], averages_y_down[5]);
  GyroCalibrationCalculatorA GyroCalibrationZ(averages_z_up[4], averages_z_down[4]);
  GyroCalibrationX.calculate();
  GyroCalibrationY.calculate();
  GyroCalibrationZ.calculate();
  std::cout << std::fixed << std::setprecision(18);
  std::cout << "The static method-derived bias: " << std::endl
            << "X: " << GyroCalibrationX.getValueb() << std::endl
            << "Y: " << GyroCalibrationY.getValueb() << std::endl
            << "Z: " << GyroCalibrationZ.getValueb() << std::endl
            << std::endl;

  // Gyroscope Calibration Using Two-Position Method
  GyroCalibrationCalculatorB GyroCalculatorY(y_pos.getRawData(), y_neg.getRawData());
  GyroCalculatorY.getTotalDistanceY();
  GyroCalculatorY.calculate();
  GyroCalibrationCalculatorB GyroCalculatorX(x_pos.getRawData(), x_neg.getRawData());
  GyroCalculatorX.getTotalDistanceX();
  GyroCalculatorX.calculate();
  GyroCalibrationCalculatorB GyroCalculatorZ(z_pos.getRawData(), z_neg.getRawData());
  GyroCalculatorZ.getTotalDistanceZ();
  GyroCalculatorZ.calculate();
  std::cout << "The bias and scale factor obtained by the two-position method: " << std::endl
            << "X:    "
            << "b: " << GyroCalculatorX.Getb() << "  "
            << "s: " << GyroCalculatorX.Gets() << std::endl
            << "Y:    "
            << "b: " << GyroCalculatorY.Getb() << "  "
            << "s: " << GyroCalculatorY.Gets() << std::endl
            << "Z:    "
            << "b: " << GyroCalculatorZ.Getb() << "  "
            << "s: " << GyroCalculatorZ.Gets() << std::endl
            << std::endl;

  std::vector<std::vector<double>>
      acc_result,
      gyo_result;

  // Accelerometer Data Compensation
  ErrorCompensation Compensation_x_up_acc(x_up.getRawData(), M);
  acc_result = Compensation_x_up_acc.calculateResultMatrix();

  // Gyroscope Data Compensation
  ErrorCompensation Compensation_y_pos_gyro(y_pos.getRawData(), GyroCalculatorX.Gets(), GyroCalculatorX.Gets(), GyroCalculatorZ.Gets(), GyroCalculatorX.Getb(), GyroCalculatorY.Getb(), GyroCalculatorZ.Getb());
  gyo_result = Compensation_y_pos_gyro.calculateResultMatrix();

  // Plotting Accelerometer Data Before and After Compensation
  x_up.origin();
  Plotter plot_acc(x_up.plot_acc_origin, acc_result);
  plot_acc.plotGraph("acc");

  // Plotting Gyroscope Data Before and After Compensation
  y_pos.origin();
  Plotter plot_gyo(y_pos.plot_gyo_origin, gyo_result);
  plot_gyo.plotGraph("gyo");

  return 0;
}
