#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "NeuralNetwork.h"
using namespace std;


/* Neuron */
Neural::Neuron::Neuron(float value, int comp, int pos, float mistake, vector<int> inc, vector<int> outc)
{
    Neuron::value = value;
    Neuron::comp = comp;
    Neuron::pos = pos;
    Neuron::mistake = mistake;
    Neuron::inc = inc;
    Neuron::outc = outc;
}

Neural::Neuron::Neuron()
{
    Neuron::get_from_file();
}

Neural::Neuron::~Neuron()
{
    //dtor
}

void Neural::Neuron::print_to_file()
{
    ofstream fout;
    fout.open("network.net", ios::app);
    fout << Neuron::value << " " << Neuron::comp << " " << Neuron::pos << " " << Neuron::mistake << " ";
    fout << Neuron::inc.size() << " " << Neuron::outc.size() << " ";
    for (auto i = (Neuron::inc).begin(); i != (Neuron::inc).end(); ++i) fout << *i << " ";
    fout << "";
    for (auto i = (Neuron::outc).begin(); i != (Neuron::outc).end(); ++i) fout << *i << " ";
    fout << "";
    fout.close();
}

void Neural::Neuron::get_from_file()
{
    ifstream fin;
    fin.open("network.net", ios::in);
    string line;
    getline(fin, line);
    fin.close();

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
Neural::Network::Network()
{
    //ctor
}

Neural::Network::~Network()
{
    //dtor
}
