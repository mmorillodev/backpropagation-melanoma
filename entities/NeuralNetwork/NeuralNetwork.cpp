//
// Created by Matheus Morillo on 4/25/2021.
//

#include <fstream>
#include <iostream>
#include <list>

#include "NeuralNetwork.h"
#include "../../utils.h"

NeuralNetwork::NeuralNetwork(int inputSize, int outputSize) : inputSize(inputSize), outputSize(outputSize) {}

void NeuralNetwork::addHiddenLayer(int neuronQtt) {
    HiddenLayer layer = HiddenLayer(neuronQtt, this->inputSize);
    this->hiddenLayers.push_back(layer);
}

void NeuralNetwork::startTraining(string trainingFilePath) {
    HiddenLayer lastHiddenLayer = this->hiddenLayers.back();
    this->outputLayer = new HiddenLayer(this->outputSize, lastHiddenLayer.neuronQtt);

    // Input file stream
    ifstream File(trainingFilePath);

    string line;
    while(getline(File, line)) {
        list<double> splittedList = split_d(line, ',');

        double *arr = new double[splittedList.size()];
        std::copy(splittedList.begin(), splittedList.end(), arr);
        for (auto& layer : this->hiddenLayers) {
            arr = layer.feedForward(arr);
        }

        
        delete[] arr;
    }

    //Cleanup
    File.close();
    delete this->outputLayer;
}