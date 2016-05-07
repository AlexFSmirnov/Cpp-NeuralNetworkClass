#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include "NeuralNetwork.h"
using namespace std;


/* Neuron */

Neural::Neuron::Neuron(int comp_, int pos_)
{
    vector<int> tmp;
    Neuron::comp = comp_;
    Neuron::pos = pos_;
    Neuron::value = (100 - rand() % 200) / 100.0;
    Neuron::mistake = 0;
    Neuron::inc = tmp;
    Neuron::outc = tmp;
}
Neural::Neuron::Neuron(string line)
{
    Neuron::string_to_neuron(line);
}

Neural::Neuron::~Neuron()
{
    cout << "Deleted neuron " + to_string(comp) + " " + to_string(pos) + "\n";
}

string Neural::Neuron::neuron_to_string()
{
    stringstream fout("");
    fout << Neuron::value << " " << Neuron::comp << " " << Neuron::pos << " " << Neuron::mistake << " ";
    fout << Neuron::inc.size() << " " << Neuron::outc.size() << " ";
    for (auto i = (Neuron::inc).begin(); i != (Neuron::inc).end(); ++i) fout << *i << " ";
    fout << "";
    for (auto i = (Neuron::outc).begin(); i != (Neuron::outc).end(); ++i) fout << *i << " ";
    fout << "\n";
    return fout.str();
}

void Neural::Neuron::string_to_neuron(string line)
{
    stringstream ss(line);
    int inclen, outclen, tmp;
    ss >> Neuron::value;
    ss >> Neuron::comp;
    ss >> Neuron::pos;
    ss >> Neuron::mistake;
    ss >> inclen;
    ss >> outclen;
    for (int i = 0; i < inclen; i++) {
        ss >> tmp;
        Neuron::inc.push_back(tmp);
    }
    for (int i = 0; i < outclen; i++) {
        ss >> tmp;
        Neuron::outc.push_back(tmp);
    }

}



/* Neural Network */
Neural::Network::Network(string tplate_, int syn_prc, float co, int nmin, int nmax)
{
    Network::syn_prc = syn_prc;
    Network::co = co;
    Network::nmin = nmin;
    Network::nmax = nmax;

    srand(time(0));
    stringstream ss(tplate_);  // Converting the template from string to vector
    for (int x; ss >> x;) {
        Network::tplate.push_back(x);
    }

    // Creating the matrix of weights of synapses between neurons (matrix[x][i][j] is the synapse from the neurons on pos 'i' in comp 'x' to the neuron on pos 'j' in comp 'x + 1'
    // Actually, here we are only set the sizes of vectors.
    Network::matrix.resize(tplate.size() - 1);
    for (int comp = 0; comp < tplate.size() - 1; comp++) {
        Network::matrix[comp].resize(tplate[comp]);
        for (int from = 0; from < tplate[comp]; from++) {
            Network::matrix[comp][from].resize(tplate[comp + 1]);
        }
    }

    Network::neurons.resize(tplate.size());
    for (int comp = 0; comp < tplate.size(); comp++) {
        Network::neurons[comp].resize(tplate[comp]);
        for (int pos = 0; pos < tplate[comp]; pos++) {
            Neural::Neuron* tmp = new Neural::Neuron(comp, pos);
            Network::neurons[comp][pos] = tmp;
        }
    }


}

Neural::Network::~Network()  // Destructor
{
    for (int comp = 0; comp < Network::tplate.size(); comp++) {
        for (int pos = 0; pos < Network::tplate[comp]; pos++) {
            delete Network::neurons[comp][pos];
        }
    }
    cout << "Deleted network!" << endl;
}
