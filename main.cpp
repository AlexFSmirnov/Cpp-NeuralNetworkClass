#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>

#include "NeuralNetwork.h"
using namespace std;

/* cout << Neuron */
ostream& operator<<(ostream& os, Neural::Neuron *n) {
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
    Neural::Network* nw = new Neural::Network("1 2 1");
    cout << nw->matrix.size() << " " << nw->matrix[1].size() << " " << nw->matrix[1][1].size() << endl;
    cout << nw->matrix.at(1).at(1).at(0) << endl;

    cout << nw->neurons[1][1] << endl;
    cout << nw->neurons[1][0] << endl;

    cout << nw->neurons[1][1]->neuron_to_string() << endl;



    return 0;
}
