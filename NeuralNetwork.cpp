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
    cerr << "Deleted neuron " + to_string(comp) + " " + to_string(pos) + "\n";
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

    // Creating the neuron matrix.
    Network::neurons.resize(tplate.size());
    for (int comp = 0; comp < tplate.size(); comp++) {
        Network::neurons[comp].resize(tplate[comp]);
        for (int pos = 0; pos < tplate[comp]; pos++) {
            Neural::Neuron* tmp = new Neural::Neuron(comp, pos);
            Network::neurons[comp][pos] = tmp;
        }
    }

    // Adding incoming neurons
    for (int comp = 0; comp < tplate.size() - 1; comp++) {  // Cycling through components. We don't need the last one, because there are no outputs from the last neurons.
        for (int from = 0; from < tplate[comp]; from++) {  // The neuron, to which we are going to add 'neighbors' (outputs)
            for (int to = 0; to < tplate[comp + 1]; to++) {  // Cycling through 'from' neuron neighbors.
                if (rand() % 100 < syn_prc) {  // And deciding, if we are going to create a synapse between them.
                    Network::create_synapse(comp, from, to, (100 - rand() % 200) / 100.0);  // And creating that synapse;
                    clog << "Added!\n";
                }
            }
            if (Network::neurons[comp][from]->outc.size() == 0) {  // Every neuron should have at least one input and one output. Otherwise it is useless. So we are checking if we didn't add any
                int to = rand() % tplate[comp + 1];  // Choosing random neuron from the next component
                Network::create_synapse(comp, from, to, (100 - rand() % 200) / 100.0);  // And creating the synapse;
            }
        }
    }
    // And now we are adding random input to neuron, which don't have them
    for (int comp = 1; comp < tplate.size(); comp++) {
        for (int to = 0; to < tplate[comp]; to++) {
            if (Network::neurons[comp][to]->inc.size() == 0) {  // If there are no inputs,
                int from = rand() % (tplate[comp - 1]);         // Choosing the neuron from previous component
                Network::create_synapse(comp, from, to, (100 - rand() % 200) / 100.0);  // And yeah, creating the synapse.
            }
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
    cerr << "Deleted network!" << endl;
}

void Neural::Network::create_synapse(int comp, int from, int to, float weight) {
    Network::neurons[comp][from]->outc.push_back(to);     // Adding output synapse to 'from' neuron
    Network::neurons[comp + 1][to]->inc.push_back(from);  // And input synapse to 'to' neuron
    Network::matrix[comp][from][to] = weight;  // Creating the weight of the synapse between these neurons. It should be random in range from -0.99 to +0.99
}

float Neural::Network::get_weight(int comp, int from, int to) {
    return Network::matrix.at(comp).at(from).at(to);
}

Neural::Neuron* Neural::Network::get_neuron(int comp, int pos) {
    return Network::neurons[comp][pos];
}
