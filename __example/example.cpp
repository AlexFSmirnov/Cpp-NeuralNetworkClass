#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include "NeuralNetwork.h"

using namespace std;

//In this example I am going to show you how to work with my neural network

int main(int argc, char *argv[]) {
    //This line is creating the neural network. There are 5 parameters, that you can change:
    //-template. In this string you choose, how many neurons will be in each component.  Required.
    //-syn_prc. By changing this parameter you can change the amount of synapses in your network - from default 100% (each with each) to 1% (each neuron has one input and one output). So, if the value is small, the network works faster, but the mistake is bigger.  Default - 100
    //-nmin. The minimum value, that the network will get/give (only positive).  Default - 0
    //-nmax. The maximum value, that the network will get/give (only positive).  Default - 1
    //-co. Learning coefficient. I don't know what this is used for :P  Default = 0.7
    Neural::Network* nw = new Neural::Network("1 10 10 1", 80, 0, 3000, 0.7);

    //Now we need to educate the network. There are 3 parameters, that you can change:
    //-filename. This is the name of the file (should be in the current directory).  Required.
    //-show_process. If true, this will show you the process of education (percentage, time left, etc.).  Default - false
    //-rep. Repetitions. The number of times, that the network is going to educate on the given file.   More repetitions - better result.  Default - 1
    //
    //In the education file one line is one task. First template[0] numbers are the input numbers, and the rest template[-1] numbers are the output (desired answer) numbers.
    nw->educate("education.txt", true, 300);

    //So, now we've got the educated network. Let's check something.
    //In this example the network was educated to multiple numbers in range(1, 1000) by 3. Let's check.
    //Method 'check' receives a string with template[0] values of input signals for the input neurons. This values should be in range(nmin, nmax)
    string a;
    cin >> a;
    cout << nw->check(a)[0] << endl;
    //This method returns a vector<double> of the output neuron's values. But because we've got just one output neuron, we can print the first (and the last) value in the returned array.
    //As you can see, the returned value isn't very accurate. This network works with binary values the best, but, if you want big numbers, you still can increase the amount of repetitions.

    //So, the network is educated, and we don't want to lose it. So let's save it.
    //Save method has only one parameter - filename
    nw->save("network.net");

    //And after saving we should delete the network
    delete nw;


    //We saved the network, and now we can load it.
    //In order to do that, you need to create the network with two parameters:
    //-filename. The name of file, from which we want to load the network
    //-load. This is a boolean parameter, the value of which doesn't mean. Just set it to true or false, and the network will understand, that it need to load from file.
    Neural::Network* nw2 = new Neural::Network("network.net", true);
    //Also you can load already created network manually - nw.load("filename");

    //And now let's check our second network
    cin >> a;
    cout << nw2->check(a)[0] << endl;

    //Working? Hope so.

    delete nw2;


    //P.S.
    //There are some already educated networks in the _educated_networks folder. Try them, if you want.



    return 0;
}
