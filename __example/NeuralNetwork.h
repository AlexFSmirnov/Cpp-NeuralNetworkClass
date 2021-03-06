#include <vector>
#include <string>


#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

namespace Neural
{
    class Neuron
    {
        public:
            Neuron(int comp_, int pos_);  // Created manually
            Neuron(std::string line);  // Loaded from a string

            int comp, pos;
            double value, mistake;
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
            /* Construactor and destructor */
            Network(std::string tplate_="0", int syn_prc=100, int nmin=0, int nmax=1, double co=0.7);  // Creating manually
            Network(std::string filename, bool load);  // Loaded from file
            virtual ~Network();

            void init();

            /* Main methods */
            double toRange(double n);
            double fromRange(double n);

            double sum(Neuron* ne);
            double sig(Neuron* ne);
            double der(Neuron* ne);

            void recount_mistake(Neuron* &ne);
            void recount_edges(Neuron* ne);

            void educate(std::string filename, bool show_process=false, int rep=1);
            std::vector<double> check(std::string inp_);

            /* Misc */
            void create_synapse(int comp, int from, int to, double weight);
            double get_weight(int comp, int from, int to);
            Neuron* get_neuron(int comp, int pos);
            void save(std::string filename);
            void load(std::string filename);



        protected:
        private:
            typedef std::vector<std::vector<std::vector<double>>> w_matrix;
            typedef std::vector<std::vector<Neuron*>> n_matrix;

            std::string tplate_;
            std::vector<int> tplate;
            int syn_prc, nmin, nmax;
            double co;
            w_matrix matrix;
            n_matrix neurons;
    };
}

#endif // NEURALNETWORK_H
