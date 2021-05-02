//
// Created by Matheus Morillo on 4/25/2021.
//

#include <iostream>
#include <list>

#include "HiddenLayer.h"
#include "HiddenNeuron/HiddenNeuron.h"

HiddenLayer::HiddenLayer(int neuronQtt, int inputSize): neuronQtt(neuronQtt), inputSize(inputSize) {
	this->neurons = (HiddenNeuron *) malloc(sizeof(HiddenNeuron) * neuronQtt);

	if (this->neurons) {
		for (int i = 0; i < neuronQtt; i++) {
			this->neurons[i] = HiddenNeuron(inputSize);
		}
	}
}

double* HiddenLayer::feedForward(double* data) {
	double *resultPerNeuron = new double[this->neuronQtt];

	for (int i = 0; i < this->neuronQtt; i++) {
		resultPerNeuron[i] = this->neurons[i].process(data);
	}

	delete[] data;

	return resultPerNeuron;
}