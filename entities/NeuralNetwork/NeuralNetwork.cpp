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

NeuralIO NeuralNetwork::extractIO(list<double> vector) {
    NeuralNetworkContext* context = NeuralNetworkContext::getInstance();
    NeuralIO io;

    io.inputs = new double[context->args.inputSize];
    io.outputs = new double[context->args.outputSize];
    
    for (int i = 0; i < context->args.inputSize; i++) {
        list<double>::iterator it = vector.begin();
        advance(it, i);
        io.inputs[i] = *it;
    }

    for (int i = 0, j = context->args.inputSize; i < context->args.outputSize; i++, j++) {
        list<double>::iterator it = vector.begin();
        advance(it, j);
        io.outputs[i] = *it;
    }

    return io;
}

void NeuralNetwork::startTraining(string trainingFilePath) {
    NeuralNetworkContext* context = NeuralNetworkContext::getInstance();

    HiddenLayer lastHiddenLayer = this->hiddenLayers.back();
    // TODO: Create entity for output layer. Using HiddenLayer due to same behaviour
    this->outputLayer = new HiddenLayer(context->args.outputSize, lastHiddenLayer.neuronQtt);

    // Input file stream
    ifstream trainingFile(trainingFilePath);

    string line;
    while(getline(trainingFile, line)) {
        list<double> splittedList = split_d(line, ',');

        NeuralIO io = this->extractIO(splittedList);
        for (auto& layer : this->hiddenLayers) {
            io.inputs = layer.feedForward(io.inputs);
        }

        // TODO: Handle output layer result
        this->outputLayer->feedForward(io.inputs);
        
        delete[] io.inputs;
        delete[] io.outputs;
    }

    //Cleanup
    trainingFile.close();
    delete context;
    delete this->outputLayer;
}