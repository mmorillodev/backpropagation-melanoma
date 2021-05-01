#include "NeuralNetworkContext.h"

NeuralNetworkContext::NeuralNetworkContext() {}

NeuralNetworkContext* NeuralNetworkContext::pinstance_ = nullptr;

NeuralNetworkContext* NeuralNetworkContext::getInstance() {
    if (pinstance_ == nullptr) {
        pinstance_ = new NeuralNetworkContext();
    }
    return pinstance_;
}