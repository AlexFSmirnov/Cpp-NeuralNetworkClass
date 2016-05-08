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

template <typename T>
ostream& operator<<(ostream& os, const vector<T> &vec) {
    for (auto i = vec.begin(); i != vec.end(); i++) {
        os << *i << " ";
    }
    return os;
}


int main(int argc, char *argv[]) {
    Neural::Network* nw = new Neural::Network("1 10 10 1", 80, 0, 3000);

    nw->educate("input.txt", true, 500);

    nw->save("network.net");

    delete nw;

    Neural::Network* nw2 = new Neural::Network("network.net", true);
    nw2->save("n5.net");




    int a;
    while (true) {
        cin >> a;
        cout << nw2->check(to_string(a)) << endl;
    }

    //cout << nw->check("0 0") << endl << nw->check("0 1") << endl << nw->check("1 0") << endl << nw->check("1 1") << endl;


    delete nw2;

    return 0;
}
