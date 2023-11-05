#include "IMUDataReader.h"
#include <fstream>
#include <iostream>
#include <sstream>

IMUDataReader::IMUDataReader(const std::string &filename) : filename(filename) {}

// Read file
bool IMUDataReader::readDataFile() {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: Unable to open file." << std::endl;
    return false;
  }

  std::string line;
  while (std::getline(file, line)) {
    processLine(line);
  }

  file.close();
  return true;
}

// Process data line by line
void IMUDataReader::processLine(const std::string &line) {
  std::istringstream iss(line);
  std::string token;
  std::string prevToken;

  while (std::getline(iss, token, ',')) {
    if (token == "00000077") {
      std::vector<double> values;

      if (!prevToken.empty()) {
        values.push_back(std::stod(prevToken));
      }

      while (std::getline(iss, token, ',')) {
        if (token.find('*') != std::string::npos) {
          token = token.substr(0, token.find('*'));
          values.push_back(std::stod(token));
          break;
        }
        values.push_back(std::stod(token));
      }
      rawData.push_back(values);
      break;
    }

    prevToken = token;
  }
}

// Calculate the average
void IMUDataReader::calculateAverages() {
  if (rawData.empty()) {
    std::cerr << "Error: No data to process." << std::endl;
    return;
  }

  int numEntries = rawData.size();
  int numValues = rawData[0].size();
  averages.resize(numValues, 0.0);

  for (const auto &entry : rawData) {
    for (int i = 0; i < numValues; ++i) {
      averages[i] += entry[i];
    }
  }

  for (double &average : averages) {
    average /= numEntries;
  }
}

std::vector<double> IMUDataReader::getAverages() {
  return averages;
}

// Data preprocessing
void IMUDataReader::applyTransformations() {
  if (rawData[0].size() != 7) {
    std::cerr << "Error: No data to process." << std::endl;
    return;
  }

  for (auto &entry : rawData) {
    for (int i = 1; i < 4; ++i) {
      entry[i] *= (accScale * 100.0);
    }

    for (int i = 4; i < 7;++i) {
      entry[i] *= (gyoScale * 100.0);
    }

    entry[2] = -entry[2];
    entry[5] = -entry[5];
  }
}

std::vector<std::vector<double>> IMUDataReader::getRawData() {
  return rawData;
}

void IMUDataReader::origin() {
  plot_acc_origin.resize(rawData.size(), std::vector<double>(4));
  plot_gyo_origin.resize(rawData.size(), std::vector<double>(4));

  for (size_t i = 0; i < rawData.size(); ++i) {
    plot_acc_origin[i][0] = rawData[i][0];
    for (size_t j = 1; j < 4; ++j) {
      plot_acc_origin[i][j] = rawData[i][4 - j];
    }

    plot_gyo_origin[i][0] = rawData[i][0];
    for (size_t j = 1; j < 4;++j) {
      plot_gyo_origin[i][j] = rawData[i][7 - j];
    }
  }
}
