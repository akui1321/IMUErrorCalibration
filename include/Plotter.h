#ifndef PLOTTER_H
#define PLOTTER_H

#include <string>
#include <vector>

class Plotter {
public:
  Plotter(const std::vector<std::vector<double>> &data_before, const std::vector<std::vector<double>> &data_after);
  void plotGraph(std::string type);

private:
  std::vector<std::vector<double>> data_before, data_after;
};

#endif 
