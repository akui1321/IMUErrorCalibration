cmake_minimum_required(VERSION 3.0)

project(IMUErrorCalibration)

add_subdirectory(src)

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

add_executable(CalibrationExecutable main.cpp)

target_link_libraries(CalibrationExecutable PRIVATE AccelCalibrationCalculator GyroCalibrationCalculatorA GyroCalibrationCalculatorB ErrorCompensation Plotter IMUDataReader)
