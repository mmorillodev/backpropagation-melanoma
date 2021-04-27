cmake_minimum_required(VERSION 3.17)
project(backpropagation-melanoma)

set(CMAKE_CXX_STANDARD 14)

add_executable(first_machine_learning main.cpp entities/HiddenLayer/Neuron/Neuron.cpp entities/HiddenLayer/HiddenNeuron/HiddenNeuron.cpp entities/HiddenLayer/HiddenNeuron/HiddenNeuron.h entities/NeuralNetwork/NeuralNetwork.cpp entities/NeuralNetwork/NeuralNetwork.h entities/HiddenLayer/HiddenLayer.cpp entities/HiddenLayer/HiddenLayer.h "utils.cpp" "utils.h")