#include <vector>


#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H


class Neuron {
    public:
        int comp, pos;
        float value, mistake;
        std::vector<int> inc;
        std::vector<int> outc;

        Neuron(float value, int comp, int pos, float mistake, std::vector<int> inc, std::vector<int> outc);
        virtual ~Neuron();

    protected:
    private:
};

class NeuralNetwork {
    public:
        NeuralNetwork();
        virtual ~NeuralNetwork();
    protected:
    private:
};

#endif // NEURALNETWORK_H
