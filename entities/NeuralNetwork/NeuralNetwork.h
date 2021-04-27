//
// Created by Matheus Morillo on 4/25/2021.
//

#ifndef BACKPROPAGATION_MELANOMA_NEURALNETWORK_H
#define BACKPROPAGATION_MELANOMA_NEURALNETWORK_H

#include <list>
#include <string>
#include "../HiddenLayer/HiddenLayer.h"

using namespace std;

class NeuralNetwork {
private:
    list<HiddenLayer> hiddenLayers;
    HiddenLayer *outputLayer;
    int inputSize;
    int outputSize;

public:
    explicit NeuralNetwork(int inputSize, int outputSize);
    void addHiddenLayer(int neuronQtt);
    void startTraining(string trainingFilePath);
};


#endif //BACKPROPAGATION_MELANOMA_NEURALNETWORK_H
