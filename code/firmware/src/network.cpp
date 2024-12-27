#include <vector>
#include <iostream>
#include <ArduinoJson.h>
#include <algorithm>
#include <SD.h>

#define structure_file_name "structure.json"

JsonDocument neuralNetwork;
File neuralNetworkFIle;

#define SD_CS_PIN 4

struct neural_network {
    std::vector<std::vector<float>> network_structure;
    std::vector<std::vector<float>> weights; 
};

float relu(float x) {
    return std::max(0, x);
}

JsonDocument load_neuralNetwork() {
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("SD card initialization failed!");
    return {};
  }

  neuroFile = SD.open(structure_file_name, FILE_WRITE);
  deserializeJson(neuralNetwork, neuroFile);

  neuralNetworkFile.close();

  neural_network nn;

  JsonArray structureArray = neuralNetworkDoc["network_structure"].as<JsonArray>();
  JsonArray weightsArray = neuralNetworkDoc["weights"].as<JsonArray>()

      for (JsonVariant row : structureArray) {
          std::vector<float> rowData;
          for (JsonVariant value : row.as<JsonArray>()) {
              rowData.push_back(value.as<float>());
          }
          nn.network_structure.push_back(rowData);
      }

  for (JsonVariant row : weightsArray) {
      std::vector<float> rowData;
      for (JsonVariant value : row.as<JsonArray>()) {
          rowData.push_back(value.as<float>());
      }
      nn.weights.push_back(rowData);
  }

  return nn;
}

// trening powinien byc dokonany przy uzyciu algorytmu w .py
float calculate_output() {
// to do !!!
}