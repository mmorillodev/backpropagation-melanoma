#include "../../entities/NeuralNetwork/NeuralNetworkArgs.h"

class NeuralNetworkContext {

private:
    static NeuralNetworkContext* pinstance_;

protected:
    NeuralNetworkContext();

public:
    NeuralNetworkContext(NeuralNetworkContext& other) = delete;
    void operator=(const NeuralNetworkContext&) = delete;
    static NeuralNetworkContext* getInstance();
    
    NeuralNetworkArgs args;
};