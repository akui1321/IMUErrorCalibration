#include "Plotter.h"
#include <fstream>
#include <iostream>

#define rad_to_degree 57.295779513082320876798154814105170332405

Plotter::Plotter(const std::vector<std::vector<double>> &data_before, const std::vector<std::vector<double>> &data_after) : data_before(data_before), data_after(data_after) {}

// Plot the graph
void Plotter::plotGraph(std::string type) {
  // Write data to temporary files
  std::ofstream tempDataFileXBefore("temp_data_X_before.txt");
  std::ofstream tempDataFileYBefore("temp_data_Y_before.txt");
  std::ofstream tempDataFileZBefore("temp_data_Z_before.txt");
  std::ofstream tempDataFileXAfter("temp_data_X_after.txt");
  std::ofstream tempDataFileYAfter("temp_data_Y_after.txt");
  std::ofstream tempDataFileZAfter("temp_data_Z_after.txt");

  if (!tempDataFileXBefore.is_open() || !tempDataFileYBefore.is_open() || !tempDataFileZBefore.is_open() ||
      !tempDataFileXAfter.is_open() || !tempDataFileYAfter.is_open() || !tempDataFileZAfter.is_open()) {
    std::cerr << "Unable to open temporary data file!" << std::endl;
    return;
  }

  if(type=="gyo") {
    for (auto &row : data_before) {
      for (int i = 1; i < 4;++i) {
        row[i] *= rad_to_degree;
      }
    }
    for (auto &row : data_after) {
      for (int i = 1; i < 4; ++i) {
        row[i] *= rad_to_degree;
      }
    }
  }

  for (const auto &row : data_before) {
    tempDataFileXBefore << row[0] << ' ' << row[1] << std::endl;
    tempDataFileYBefore << row[0] << ' ' << row[2] << std::endl;
    tempDataFileZBefore << row[0] << ' ' << row[3] << std::endl;
  }

  for (const auto &row : data_after) {
    tempDataFileXAfter << row[0] << ' ' << row[1] << std::endl;
    tempDataFileYAfter << row[0] << ' ' << row[2] << std::endl;
    tempDataFileZAfter << row[0] << ' ' << row[3] << std::endl;
  }

  // for (int i = 500; i < 3500;++i) {
  //   tempDataFileYBefore << data_before[i][0] << ' ' << data_before[i][2] << std::endl;
  //   tempDataFileYAfter << data_after[i][0] << ' ' << data_after[i][2] << std::endl;
  // }

  tempDataFileXBefore.close();
  tempDataFileYBefore.close();
  tempDataFileZBefore.close();
  tempDataFileXAfter.close();
  tempDataFileYAfter.close();
  tempDataFileZAfter.close();

  // Using gnuplot scripts
  std::ofstream gpFileX("plot_script_X.plt");
  std::ofstream gpFileY("plot_script_Y.plt");
  std::ofstream gpFileZ("plot_script_Z.plt");

  if (!gpFileX.is_open() || !gpFileY.is_open() || !gpFileZ.is_open()) {
    std::cerr << "Unable to create gnuplot script file!" << std::endl;
    return;
  }

  // Gnuplot script for X values
  gpFileX << "set term x11 persist\n";
  gpFileX << "set title 'X Values Before and After'\n";
  gpFileX << "set xlabel 'time(s)'\n";
  if (type=="acc") {
    gpFileX << "set ylabel 'acceleration(m/s^2)'\n";
  }
  if (type=="gyo") {
    gpFileX << "set ylabel 'angular velocity(degree/s)'\n";
  }
  gpFileX << "plot 'temp_data_X_before.txt' with lines title 'X before',"
             "'temp_data_X_after.txt' with lines title 'X after'\n";

  // Gnuplot script for Y values
  gpFileY << "set term x11 persist\n";
  gpFileY << "set title 'Y Values Before and After'\n";
  gpFileY << "set xlabel 'time(s)'\n";
  if (type == "acc") {
    gpFileY << "set ylabel 'acceleration(m/s^2)'\n";
  }
  if (type == "gyo") {
    gpFileY << "set ylabel 'angular velocity(degree/s)'\n";
  }
  gpFileY << "plot 'temp_data_Y_before.txt' with lines title 'Y before',"
             "'temp_data_Y_after.txt' with lines title 'Y after'\n";

  // Gnuplot script for Z values
  gpFileZ << "set term x11 persist\n";
  gpFileZ << "set title 'Z Values Before and After'\n";
  gpFileZ << "set xlabel 'time(s)'\n";
  if (type == "acc") {
    gpFileZ << "set ylabel 'acceleration(m/s^2)'\n";
  }
  if (type == "gyo") {
    gpFileZ << "set ylabel 'angular velocity(degree/s)'\n";
  }
  gpFileZ << "plot 'temp_data_Z_before.txt' with lines title 'Z before',"
             "'temp_data_Z_after.txt' with lines title 'Z after'\n";

  gpFileX.close();
  gpFileY.close();
  gpFileZ.close();

  // Execute the gnuplot scripts
  system("gnuplot plot_script_X.plt");
  system("gnuplot plot_script_Y.plt");
  system("gnuplot plot_script_Z.plt");

  // Delete temporary files
  remove("temp_data_X_before.txt");
  remove("temp_data_X_after.txt");
  remove("temp_data_Y_before.txt");
  remove("temp_data_Y_after.txt");
  remove("temp_data_Z_before.txt");
  remove("temp_data_Z_after.txt");
  remove("plot_script_X.plt");
  remove("plot_script_Y.plt");
  remove("plot_script_Z.plt");

  std::cout << "Press enter to continue..." << std::endl;
  std::cin.get();
}
