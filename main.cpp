#include <iostream>
#include <vector>
#include "NeuralNetwork.h"

using namespace std;

int main(int argc, char *argv[]) {
    vector<int> inc;
    vector<int> outc;
    Neuron *n = new Neuron(5.0, 1, 2, 1.0, inc, outc);
    cout << n->value << "\n";
    cout << n->inc.size() << "\n";
    n->inc.push_back(20);
    cout << n->inc.size();

    return 0;
}
