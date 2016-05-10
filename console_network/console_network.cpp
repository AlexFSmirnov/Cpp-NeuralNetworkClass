#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include "NeuralNetwork.h"

using namespace std;


/** Help.
  * This is a file, using which you can educate, save, load and use
  * a neural network right from a console.
  *
  * In order to do this run this file using these arguments:
  * GENERAL---------------------------------------------------
  * -h           Shows this message
  *
  * NETWORK-CREATION------------------------------------------
  * -t "string"  The template for the network
  * -sp "int"    Synapse percent               (default = 100)
  * -nn "int"    Minimal input/output value    (default =   0)
  * -nx "int"    Maximal input/output value    (default =   1)
  * -co "float"  Learning coefficient          (default = 0.7)
  *
  * EDUCATION-------------------------------------------------
  * -e "file"    File with tasks for education
  * -sh "bool"   Show process                (default =  true)
  * -r "int"     Repetitions                 (default =     1)
  *
  * SOLVING---------------------------------------------------
  * -i "file"    Input file with task(s) to solve
  * -ss "bool"   Show process                (default = false)
  * -o "file"    Output file for answer(s)
  *
  * SAVING/LOADING--------------------------------------------
  * -s "file"    Will save the network to file after education
  * -l "file"    Will load the network from the file
  */


int main(int argc, char *argv[]) {
    string help_message = " Help.\n This is a file, using which you can educate, save, load and use\n a neural network right from a console.\n\n In order to do this run this file using these arguments:\n GENERAL---------------------------------------------------\n -h           Shows this message\n\n NETWORK-CREATION------------------------------------------\n -t \"string\"  The template for the network\n -sp \"int\"    Synapse percent               (default = 100)\n -nn \"int\"    Minimal input/output value    (default =   0)\n -nx \"int\"    Maximal input/output value    (default =   1)\n -co \"float\"  Learning coefficient          (default = 0.7)\n\n EDUCATION-------------------------------------------------\n -e \"file\"    File with tasks for education\n -sh \"bool\"   Show process                (default = false)\n -r \"int\"     Repetitions                 (default =     1)\n\n SOLVING---------------------------------------------------\n -i \"file\"    Input file with task(s) to solve\n -ss \"bool\"   Show process                (default =  true)\n -o \"file\"    Output file for answer(s)\n\n SAVING/LOADING--------------------------------------------\n -s \"file\"    Will save the network to file after education\n -l \"file\"    Will load the network from the file\n";
    string tplate = "0 0";
    int syn_prc = 100;
    int nmin = 0;
    int nmax = 1;
    float co = 0.7;

    string ed_file = "none";
    bool show_process = true;
    int rep = 1;

    string inp_file = "none";
    bool show_solivng_process = false;
    string out_file = "none";

    string save_file = "none";
    string load_file = "none";


    for (int arg = 0; arg < argc; arg++) {
        if (argv[arg] == (string)"-h") {
            cout << help_message;
            exit(0);
        } else if (argv[arg] == (string)"-t") {
            tplate = argv[++arg];
        } else if (argv[arg] == (string)"-sp") {
            syn_prc = atoi(argv[++arg]);
        } else if (argv[arg] == (string)"-nn") {
            nmin = atoi(argv[++arg]);
        } else if (argv[arg] == (string)"-nx") {
            nmax = atoi(argv[++arg]);
        } else if (argv[arg] == (string)"-co") {
            co = atof(argv[++arg]);
        } else if (argv[arg] == (string)"-e") {
            ed_file = argv[++arg];
        } else if (argv[arg] == (string)"-sh") {
            string tmp = argv[++arg];
            if (tmp == (string)"true" || tmp == (string)"1")
                show_process = true;
        } else if (argv[arg] == (string)"-r") {
            rep = atoi(argv[++arg]);
        } else if (argv[arg] == (string)"-i") {
            inp_file = argv[++arg];
        } else if (argv[arg] == (string)"-ss") {
            string tmp = argv[++arg];
            if (tmp == (string)"true" || tmp == (string)"1")
                show_solivng_process = true;
        } else if (argv[arg] == (string)"-o") {
            out_file = argv[++arg];
        } else if (argv[arg] == (string)"-s") {
            save_file = argv[++arg];
        } else if (argv[arg] == (string)"-l") {
            load_file = argv[++arg];
        }
    }

    if (tplate == "0 0" && load_file == "none") {
        cout << "Please, define the template for the network or the file to load the network from. *Use -h for help*\n";
        exit(0);
    }


    Neural::Network* nw = new Neural::Network(tplate, syn_prc, nmin, nmax, co);

    if (load_file != "none")
        nw->load(load_file);

    if (ed_file != "none")
        nw->educate(ed_file, show_process, rep);

    if (save_file != "none")
        nw->save(save_file);

    if (inp_file != "none") {
        ofstream fout;
        if (out_file != "none")
            fout.open(out_file, ios::out);
        ifstream fin(inp_file, ios::in);
        string task;
        vector<double> ans;

        int cnt = 0;
        while(!fin.eof()) {
            getline(fin, task);
            ans = nw->check(task);
            if (out_file == "none")
                cout << task << " -> ";
            for (auto i = ans.begin(); i != ans.end(); i++)
                (out_file == "none") ? cout << *i << " " : fout << *i << " ";
            (out_file == "none") ? cout << endl : fout << endl;

            if (show_solivng_process)
                cout << "Solved task #" << ++cnt << "\n";
        }
        if (out_file != "none")
            cout << "Finished!\n";
    }
    delete nw;

    return 0;
}
