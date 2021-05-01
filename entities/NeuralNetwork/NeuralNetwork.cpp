//
// Created by Matheus Morillo on 4/25/2021.
//

#include <fstream>
#include <iostream>
#include <list>

#include "NeuralNetwork.h"
#include "../../utilities/utils.h"
#include "../../utilities/singleton/NeuralNetworkContext.h"

NeuralNetwork::NeuralNetwork(NeuralNetworkArgs args) {
    NeuralNetworkContext *context = NeuralNetworkContext::getInstance();
    context->args = args;
}

void NeuralNetwork::addHiddenLayer(int neuronQtt) {
    NeuralNetworkContext* context = NeuralNetworkContext::getInstance();

    int inputQtt = this->hiddenLayers.size() == 0 ? context->args.inputSize : this->hiddenLayers.back().neuronQtt;
    HiddenLayer layer = HiddenLayer(neuronQtt, inputQtt);
    this->hiddenLayers.push_back(layer);
}

void NeuralNetwork::startTraining(string trainingFilePath) {
    NeuralNetworkContext* context = NeuralNetworkContext::getInstance();

    HiddenLayer lastHiddenLayer = this->hiddenLayers.back();
    // TODO: Create entity for output layer. Using Hidden due to same behaviour
    this->outputLayer = new HiddenLayer(context->args.outputSize, lastHiddenLayer.neuronQtt);

    // Input file stream
    ifstream trainingFile(trainingFilePath);

    string line;
    while(getline(trainingFile, line)) {
        list<double> splittedList = split_d(line, ',');

        double *arr = new double[splittedList.size()];
        std::copy(splittedList.begin(), splittedList.end(), arr);
        for (auto& layer : this->hiddenLayers) {
            arr = layer.feedForward(arr);
        }

        
        delete[] arr;
    }

    //Cleanup
    trainingFile.close();
    delete context;
    delete this->outputLayer;
}