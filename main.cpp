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
    Neural::Network* nw = new Neural::Network("1 10 10 1", 10);

    int comp = 0, pos = 0;
    while (comp != -1) {
        cout << nw->get_neuron(comp, pos);
        cin >> comp >> pos;
    }


    delete nw;



    return 0;
}
