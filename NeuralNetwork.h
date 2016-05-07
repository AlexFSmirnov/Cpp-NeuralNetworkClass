#include <vector>
#include <string>


#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

namespace Neural
{
    class Neuron
    {
        public:
            Neuron(int comp_, int pos_);  // Creating with values
            Neuron(std::string line);  // Reading from file
            virtual ~Neuron();

            int comp, pos;
            float value, mistake;
            std::vector<int> inc;
            std::vector<int> outc;


            std::string neuron_to_string();
            void string_to_neuron(std::string line);

        protected:
        private:
    };

    class Network
    {
        public:
            Network(std::string tplate_="0", int syn_prc=100, float co=0.7, int nmin=0, int nmax=0);
            virtual ~Network();

            void create_synapse(int comp, int from, int to, float weight);

            float get_weight(int comp, int from, int to);
            Neuron* get_neuron(int comp, int pos);

        protected:
        private:
            typedef std::vector<std::vector<std::vector<int>>> w_matrix;
            typedef std::vector<std::vector<Neuron*>> n_matrix;

            std::vector<int> tplate;
            int syn_prc, nmin, nmax;
            float co;
            w_matrix matrix;
            n_matrix neurons;
    };
}

#endif // NEURALNETWORK_H
