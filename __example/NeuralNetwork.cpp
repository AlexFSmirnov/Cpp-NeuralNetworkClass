#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <math.h>
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

string Neural::Neuron::neuron_to_string()
{
    stringstream fout("");
    fout << Neuron::value << " " << Neuron::comp << " " << Neuron::pos << " " << Neuron::mistake << " ";
    fout << Neuron::inc.size() << " " << Neuron::outc.size() << " ";
    for (auto i = (Neuron::inc).begin(); i != (Neuron::inc).end(); ++i) fout << *i << " ";
    for (auto i = (Neuron::outc).begin(); i != (Neuron::outc).end(); ++i) fout << *i << " ";
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
Neural::Network::Network(string tplate_, int syn_prc, int nmin, int nmax, double co)
{
    Network::tplate_ = tplate_;
    Network::syn_prc = syn_prc;
    Network::nmin = nmin;
    Network::nmax = nmax;
    Network::co = co;

    srand(time(0));

    Network::init();  // Resizing network's matrices, converting template

    // Adding incoming neurons
    for (int comp = 0; comp < tplate.size() - 1; comp++) {  // Cycling through components. We don't need the last one, because there are no outputs from the last neurons.
        for (int from = 0; from < tplate[comp]; from++) {  // The neuron, to which we are going to add 'neighbors' (outputs)
            for (int to = 0; to < tplate[comp + 1]; to++) {  // Cycling through 'from' neuron neighbors.
                if (rand() % 100 < syn_prc) {  // And deciding, if we are going to create a synapse between them.
                    Network::create_synapse(comp, from, to, (100 - rand() % 200) / 100.0);  // And creating that synapse;";
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
                int from = rand() % tplate[comp - 1];         // Choosing the neuron from previous component
                Network::create_synapse(comp - 1, from, to, (100 - rand() % 200) / 100.0);  // And yeah, creating the synapse.
            }
        }
    }
}

Neural::Network::Network(string filename, bool load) {
    Network::load(filename);
}

Neural::Network::~Network()  // Destructor
{
    for (int comp = 0; comp < Network::tplate.size(); comp++) {  // Deleting all neurons
        for (int pos = 0; pos < Network::tplate[comp]; pos++) {
            delete Network::neurons[comp][pos];
        }
    }
}

void Neural::Network::init()  // Resizing matrices and converting template
{
    stringstream ss(Network::tplate_);  // Converting the template from string to vector
    Network::tplate.clear();  // Clearing the template, because some trash from the last network might be here
    for (int x; ss >> x;) {
        Network::tplate.push_back(x);
    }
    // Creating the matrix of weights of synapses between neurons (matrix[x][i][j] is the synapse from the neurons on pos 'i' in comp 'x' to the neuron on pos 'j' in comp 'x + 1'
    // Actually, here we are only set the sizes of vectors.
    Network::matrix.resize(Network::tplate.size() - 1);
    for (int comp = 0; comp < Network::tplate.size() - 1; comp++) {
        Network::matrix[comp].resize(Network::tplate[comp]);
        for (int from = 0; from < Network::tplate[comp]; from++) {
            Network::matrix[comp][from].resize(Network::tplate[comp + 1]);
        }
    }

    // Creating the neuron matrix.
    Network::neurons.resize(Network::tplate.size());
    for (int comp = 0; comp < Network::tplate.size(); comp++) {
        Network::neurons[comp].resize(Network::tplate[comp]);
        for (int pos = 0; pos < Network::tplate[comp]; pos++) {
            Neural::Neuron* tmp = new Neural::Neuron(comp, pos);
            Network::neurons[comp][pos] = tmp;
        }
    }
}

double Neural::Network::toRange(double n)  // This function puts 'n' to range from 0 to 1, so it can be used as an input for the network
{
    return n / (Network::nmax - Network::nmin);
}
double Neural::Network::fromRange(double n)  // And this function gets 'n' back
{
    return n * (Network::nmax - Network::nmin);
}



double Neural::Network::sum(Neural::Neuron* ne)  // Computing the weighted sum for the neuron 'ne'
{
    double sm = 0;
    for (auto pos = ne->inc.begin(); pos != ne->inc.end(); pos++) {  // Cycling through incoming neurons
        sm += Network::matrix[ne->comp - 1][*pos][ne->pos] * Network::neurons[ne->comp - 1][*pos]->value;
    }
    return sm;
}
double Neural::Network::sig(Neural::Neuron* ne)  // Sigma activator
{
    return (1 / (1 + exp(-(Network::sum(ne)))));
}
double Neural::Network::der(Neural::Neuron* ne)  // Derivative for that sigma activator
{
    return (Network::sig(ne)) * (1 - Network::sig(ne));
}



void Neural::Network::recount_mistake(Neural::Neuron* &ne)  // Recounting mistake for the neuron 'ne'
{
    double new_mist = 0;
    for (auto pos = ne->outc.begin(); pos != ne->outc.end(); pos++) {
        new_mist += Network::neurons[ne->comp + 1][*pos]->mistake * Network::matrix[ne->comp][ne->pos][*pos];
    }
    ne->mistake = new_mist;
}
void Neural::Network::recount_edges(Neural::Neuron* ne)  // Recounting all incoming edges for the neuron 'ne'
{
    for (auto pos = ne->inc.begin(); pos != ne->inc.end(); pos++) {
        Network::matrix[ne->comp - 1][*pos][ne->pos] += Network::co * ne->mistake * Network::der(ne) * Network::neurons[ne->comp - 1][*pos]->value;
    }
}

void Neural::Network::educate(string filename, bool show_process, int rep)  // Educating the network
{
    // Getting tasks from file
    ifstream fin;
    fin.open(filename);
    vector<string> tasks;
    string tmp_task;
    while (!fin.eof()) {
        getline(fin, tmp_task);
        tasks.push_back(tmp_task);
    }
    fin.close();


    /* Used only if show_process == true */
    int all_count = tasks.size() * rep;
    int prc = 0;
    int cur_cnt = 0;
    int stime = time(0);


    for (int rp = 0; rp < rep; rp++) {  // Educating the network several (rep) times
        for (auto task = tasks.begin(); task != tasks.end(); task++) {  // Cycling through tasks
            /* Displaying the job, that is already done, and the time that is left */
            if (show_process) {
                cur_cnt++;
                if ((int)((cur_cnt * 1.0) / all_count * 100) > prc) {
                    prc++;
                    int s_all = (int)((100 - prc) * 1.0 * ((time(0) - stime) * 1.0 / prc));
                    if (prc < 100)
                        printf("% 3d%%, Time left: %02dh:%02dm:%02ds \n", prc, s_all / 3600, (s_all / 60) % 60, s_all % 60);
                }

            }

            /* Sorting input and output data */
            stringstream vars(*task);  // Input and output variables are all in one line. Input variables are the first template[0] ones, and output = the rest (actually, it is template[-1])
            vector<double> inp;  // Input values
            vector<double> out;  // Desirable output values
            int tmp;
            for (int i = 0; i < Network::tplate[0]; i++) {  // Adding input variables
                vars >> tmp;
                inp.push_back(Network::toRange(tmp));
            }
            for (int i = 0; i < Network::tplate[Network::tplate.size() - 1]; i++) {
                vars >> tmp;
                out.push_back(Network::toRange(tmp));
            }

            /* Changing start values */
            for (int pos = 0; pos < Network::tplate[0]; pos++) {
                Network::neurons[0][pos]->value = inp[pos];
            }

            /* Counting values */
            for (int comp = 1; comp < Network::tplate.size(); comp++) {
                for (int pos = 0; pos < Network::tplate[comp]; pos++) {
                    Network::neurons[comp][pos]->value = Network::sig(Network::neurons[comp][pos]);
                }
            }

            /* Counting mistakes for the last neurons */
            for (int pos = 0; pos < Network::tplate[Network::tplate.size() - 1]; pos++) {
                Network::neurons[Network::tplate.size() - 1][pos]->mistake = out[pos] - Network::neurons[Network::tplate.size() - 1][pos]->value;
            }

            /* Recounting mistakes */
            for (int comp = Network::tplate.size() - 2; comp >= 0; comp--) {
                for (int pos = 0; pos < Network::tplate[comp]; pos++) {
                    Network::recount_mistake(Network::neurons[comp][pos]);
                }
            }

            /* Recounting edges */
            for (int comp = 1; comp < Network::tplate.size(); comp++) {
                for (int pos = 0; pos < Network::tplate[comp]; pos++) {
                    Network::recount_edges(Network::neurons[comp][pos]);
                }
            }

        }
    }
    printf("Done! Time used: %02dh:%02dm:%02ds \n", (time(0) - stime) / 3600, ((time(0) - stime) / 60) % 60, (time(0) - stime) % 60);
}

vector<double> Neural::Network::check(string inp_)
{
    /* Converting input variables from string to vector */
    stringstream ss(inp_);
    vector<double> inp;
    for (double n; ss >> n;) {
        inp.push_back(Network::toRange(n));
    }

    /* Changing start values */
    for (int pos = 0; pos < Network::tplate[0]; pos++) {
        Network::neurons[0][pos]->value = inp[pos];
    }

    /* Counting values */
    for (int comp = 1; comp < Network::tplate.size(); comp++) {
        for (int pos = 0; pos < Network::tplate[comp]; pos++) {
            Network::neurons[comp][pos]->value = Network::sig(Network::neurons[comp][pos]);
        }
    }

    /* Returning output */
    vector<double> out;
    for (int pos = 0; pos < Network::tplate[Network::tplate.size() - 1]; pos++) {
        out.push_back(Network::fromRange(Network::neurons[Network::tplate.size() - 1][pos]->value));
    }
    return out;

}

void Neural::Network::create_synapse(int comp, int from, int to, double weight)
{
    Network::neurons.at(comp).at(from)->outc.push_back(to);     // Adding output synapse to 'from' neuron
    Network::neurons.at(comp + 1).at(to)->inc.push_back(from);  // And input synapse to 'to' neuron
    Network::matrix.at(comp).at(from).at(to) = weight;  // Creating the weight of the synapse between these neurons. It should be random in range from -0.99 to +0.99
}

double Neural::Network::get_weight(int comp, int from, int to)
{
    return Network::matrix.at(comp).at(from).at(to);
}

Neural::Neuron* Neural::Network::get_neuron(int comp, int pos)
{
    return Network::neurons[comp][pos];
}

void Neural::Network::save(string filename)
{
    ofstream fout(filename, ios::out);
    fout << Network::tplate_ << "\n";
    fout << Network::syn_prc << " " << Network::nmin << " " << Network::nmax << " " << Network::co << "\n";
    for (int comp = 0; comp < Network::tplate.size() - 1; comp++) {  // Printing the matrix of weights
        for (int from = 0; from < Network::tplate[comp]; from++) {
            for (int to = 0; to < Network::tplate[comp + 1]; to++) {
                fout << Network::matrix[comp][from][to] << " ";
            }
        }
        fout << "\n";
    }
    for (int comp = 0; comp < Network::tplate.size(); comp++) {  // Printing the matrix of neurons
        for (int pos = 0; pos < Network::tplate[comp]; pos++) {
            fout << Network::get_neuron(comp, pos)->neuron_to_string() << "\n";
        }
    }
    fout.close();
    clog << "Saved to " + filename << "\n";
}
void Neural::Network::load(string filename)
{
    ifstream fin(filename, ios::in);
    getline(fin, Network::tplate_);
    fin >> Network::syn_prc;
    fin >> Network::nmin;
    fin >> Network::nmax;
    fin >> Network::co;
    Network::init();
    for (int comp = 0; comp < Network::tplate.size() - 1; comp++) {  // Getting the matrix of weights
        for (int from = 0; from < Network::tplate[comp]; from++) {
            for (int to = 0; to < Network::tplate[comp + 1]; to++) {
                fin >> Network::matrix[comp][from][to];
            }
        }
    }

    string tmp_string;
    getline(fin, tmp_string);  // Duct tape. After getting the matrix we are still staying on the line, where weights are defined. So we need to go one line lower.
    for (int comp = 0; comp < Network::tplate.size(); comp++) {  // Getting the matrix of neurons
        for (int pos = 0; pos < Network::tplate[comp]; pos++) {
            getline(fin, tmp_string);
            Neural::Neuron* tmp_neuron = new Neural::Neuron(tmp_string);
            Network::neurons[comp][pos] = tmp_neuron;
        }
    }
    fin.close();
    clog << "Loaded from " + filename << "\n";
}
