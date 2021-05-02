#include <iostream>
#include <ctime>
#include <cmath>

#include "entities/NeuralNetwork/NeuralNetwork.h"
#include "entities/HiddenLayer/HiddenNeuron/HiddenNeuron.h"
#include "entities/NeuralNetwork/NeuralNetwork.h"
#include "entities/NeuralNetwork/NeuralNetworkArgs.h"

#define INPUT_QTT 9
#define OUTPUT_QTT 1
#define LEARNING_RATE 0.5
#define MAXIMUM_ERROR 0.05

using namespace std;

int main() {
    NeuralNetworkArgs args;
    args.inputSize = INPUT_QTT;
    args.outputSize = OUTPUT_QTT;
    args.learningRate = LEARNING_RATE;
    args.maximumError = MAXIMUM_ERROR;

    NeuralNetwork network = NeuralNetwork(args);
    network.addHiddenLayer(24);
    network.addHiddenLayer(12);

    network.startTraining("C:/Users/Matheus Morillo/Downloads/Dados_Processados.csv");

    return 0;
}

//TODO: Remove later
#define NEURON_QTT 5

void oldVersion() {
    srand(time(nullptr));

    const double samples[4][3] = {
            {0.0, 0.0, 0.0},
            {0.0, 1.0, 1.0},
            {1.0, 0.0, 1.0},
            {1.0, 1.0, 0.0}
    };

    Neuron *neurons[NEURON_QTT];
    Neuron *outputNeurons[OUTPUT_QTT];

    for(auto &neuron : neurons) {
        neuron = new HiddenNeuron(INPUT_QTT);
    }

    for(auto &outputNeuron : outputNeurons) {
        outputNeuron = new HiddenNeuron(NEURON_QTT);
    }

    double inputs[INPUT_QTT];

    double resultPerNeuron[NEURON_QTT];
    double backPropagation[NEURON_QTT];

    double outputs[OUTPUT_QTT];
    double obtained[OUTPUT_QTT];

    double *weights;

    double summarizedErrors;
    double outputDelta;
    double hiddenDelta;

    int totalIterations = 0;

    cout << "Input\tOutput\tObtained" << endl;

    do {
        summarizedErrors = 0.0;

        for(const double *sample : samples) {

            for(int inputColumn = 0; inputColumn < INPUT_QTT; inputColumn++) {
                cout << "" << sample[inputColumn];
                inputs[inputColumn] = sample[inputColumn];
            }

            cout << "\t|";

            for(int outputColumn = 0, sampleIndex = INPUT_QTT; outputColumn < OUTPUT_QTT; outputColumn++, sampleIndex++) {
                cout << " " << sample[sampleIndex];
                outputs[outputColumn] = sample[sampleIndex];
            }

            for(int neuronIndex = 0; neuronIndex < NEURON_QTT; neuronIndex++) {
                resultPerNeuron[neuronIndex] = neurons[neuronIndex]->process(inputs);
            }

            cout << "\t|";

            for(int neuronIndex = 0; neuronIndex < OUTPUT_QTT; neuronIndex++) {
                obtained[neuronIndex] = outputNeurons[neuronIndex]->process(resultPerNeuron);

                cout << " " << obtained[neuronIndex];
            }

            cout << endl;

            // update output layer weights
            for(int neuronIndex = 0; neuronIndex < OUTPUT_QTT; neuronIndex++) {
                weights = outputNeurons[neuronIndex]->getWeights();

                outputDelta
                        = (outputs[neuronIndex] - obtained[neuronIndex])
                          * obtained[neuronIndex] * (1.0 - obtained[neuronIndex]);

                summarizedErrors
                        += pow(outputs[neuronIndex] - obtained[neuronIndex], 2.0);

                outputNeurons[neuronIndex]->setBias(outputNeurons[neuronIndex]->getBias() + LEARNING_RATE * outputDelta * 1.0);

                for(int weightIndex = 0; weightIndex < NEURON_QTT; weightIndex++) {
                    weights[weightIndex] = weights[weightIndex] + LEARNING_RATE * outputDelta * resultPerNeuron[weightIndex];

                    backPropagation[weightIndex] = outputDelta * weights[weightIndex];
                }
            }

            // update hidden layer weights
            for(int neuronIndex = 0; neuronIndex < NEURON_QTT; neuronIndex++) {
                weights = neurons[neuronIndex]->getWeights();

                hiddenDelta = resultPerNeuron[neuronIndex] * (1.0 - resultPerNeuron[neuronIndex]) * backPropagation[neuronIndex];

                neurons[neuronIndex]->setBias(neurons[neuronIndex]->getBias() + LEARNING_RATE * hiddenDelta * 1.0);

                for(int weightIndex = 0; weightIndex < INPUT_QTT; weightIndex++) {
                    weights[weightIndex] = weights[weightIndex] + LEARNING_RATE * hiddenDelta * resultPerNeuron[weightIndex];
                }
            }
        }

        cout << "Summarized error: " << summarizedErrors << endl;

        ++totalIterations;

    } while (summarizedErrors > MAXIMUM_ERROR);

    cout << "\nTotal of iterations: " << totalIterations << endl;
}