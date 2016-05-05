#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "NeuralNetwork.h"

using namespace std;

/* cout << Neuron */
ostream& operator<<(ostream& os, Neuron *n) {
    os << "Value: " << n->value << "\n";
    os << "Component: " << n->comp << "\n";
    os << "Position: " << n->pos << "\n";
    os << "Mistake: " << n->mistake << "\n";
    os << "Incoming neurons' indexes: \n";
    for (auto i = (n->inc).begin(); i != (n->inc).end(); ++i) os << *i << " ";
    os << "\nOutcoming neurons' indexes: \n";
    for (auto i = (n->outc).begin(); i != (n->outc).end(); ++i) os << *i << " ";
    os << "\n";
    return os;
}


int main(int argc, char *argv[]) {
    vector<int> inc;
    vector<int> outc;
    Neuron *n = new Neuron(5.2, 1, 2, 1.3, inc, outc);
    for (int i = 0; i < 8; i++) n->inc.push_back(i);
    for (int i = 0; i < 12; i++) n->outc.push_back(i);
    cout << n;


    return 0;
}
