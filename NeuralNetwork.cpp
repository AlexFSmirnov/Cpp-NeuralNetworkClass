#include <iostream>
#include <vector>
#include "NeuralNetwork.h"
using namespace std;


/* Neuron */
Neuron::Neuron(float value, int comp, int pos, float mistake, vector<int> inc, vector<int> outc) {
    Neuron::value = value;
    Neuron::comp = comp;
    Neuron::pos = pos;
    Neuron::mistake = mistake;
    Neuron::inc = inc;
    Neuron::outc = outc;
}

Neuron::~Neuron() {
    //dtor
}




/* Neural Network */
NeuralNetwork::NeuralNetwork() {
    //ctor
}

NeuralNetwork::~NeuralNetwork() {
    //dtor
}
