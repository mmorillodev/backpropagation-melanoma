//
// Created by Matheus Morillo on 4/25/2021.
//

#ifndef BACKPROPAGATION_MELANOMA_NEURALNETWORK_H
#define BACKPROPAGATION_MELANOMA_NEURALNETWORK_H

#include <list>
#include <string>

#include "../HiddenLayer/HiddenLayer.h"
#include "NeuralNetworkArgs.h"

using namespace std;

struct NeuralIO {
    double* inputs;
    double* outputs;
};

class NeuralNetwork {
private:
    list<HiddenLayer> hiddenLayers;
    HiddenLayer *outputLayer;
    
    NeuralIO extractIO(list<double> vector);

public:
    explicit NeuralNetwork(NeuralNetworkArgs args);
    void addHiddenLayer(int neuronQtt);
    void startTraining(string trainingFilePath);
};


#endif //BACKPROPAGATION_MELANOMA_NEURALNETWORK_H
