//
// Created by Matheus Morillo on 4/25/2021.
//

#include <list>

#include "HiddenNeuron/HiddenNeuron.h"

#ifndef BACKPROPAGATION_MELANOMA_HIDDENLAYER_H
#define BACKPROPAGATION_MELANOMA_HIDDENLAYER_H


class HiddenLayer {
public:
    explicit HiddenLayer(int neuronQtt, int inputSize);

    int neuronQtt;
    int inputSize;
    HiddenNeuron *neurons;

    double* feedForward(double* data);
};


#endif //BACKPROPAGATION_MELANOMA_HIDDENLAYER_H
