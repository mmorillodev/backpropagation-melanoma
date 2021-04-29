//
// Created by Matheus Morillo on 4/25/2021.
//

#include <fstream>
#include <iostream>
#include <list>

#include "NeuralNetwork.h"
#include "../../utils.h"

NeuralNetwork::NeuralNetwork(NeuralNetworkArgs args) : args(args) {}

void NeuralNetwork::addHiddenLayer(int neuronQtt) {
    int inputQtt = this->hiddenLayers.size() == 0 ? this->args.inputSize : this->hiddenLayers.back().neuronQtt;
    HiddenLayer layer = HiddenLayer(neuronQtt, inputQtt);
    this->hiddenLayers.push_back(layer);
}

void NeuralNetwork::startTraining(string trainingFilePath) {
    HiddenLayer lastHiddenLayer = this->hiddenLayers.back();
    // TODO: Create entity for output layer. Using Hidden due to same behaviour
    this->outputLayer = new HiddenLayer(this->args.outputSize, lastHiddenLayer.neuronQtt);

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