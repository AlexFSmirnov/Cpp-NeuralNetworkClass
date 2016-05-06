#include <vector>


#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

namespace Neural
{
    class Neuron
    {
        public:
            int comp, pos;
            float value, mistake;
            std::vector<int> inc;
            std::vector<int> outc;

            Neuron(float value, int comp, int pos, float mistake, std::vector<int> inc, std::vector<int> outc);
            Neuron();
            virtual ~Neuron();

            void print_to_file();
            void get_from_file();

        protected:
        private:
    };

    class Network
    {
        public:
            Network();
            virtual ~Network();
        protected:
        private:
    };
}

#endif // NEURALNETWORK_H
