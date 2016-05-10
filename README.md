# Cpp-NeuralNetworkClass
Neural Network class for C++, almost the same as the python one.
There are two different ways to work with this network:
- [Use it in your code](https://github.com/AlexFSmirnov/Cpp-NeuralNetworkClass#using-in-the-code)
- [Use it from the console](https://github.com/AlexFSmirnov/Cpp-NeuralNetworkClass#using-from-the-console)

##Using in the code
You should use this variant in more complex networks. Just include a class and do whatever you want.

### Including the class
In order to work with this class, in your code you need to include it:
```cpp
#include "NeuralNetwork.h"
```

### Creating the network
This line is creating the neural network.
```python
Neural::Network* nw = new Neural::Network("1 10 10 1", 80, 0, 3000, 0.7);
```
There are 4 parameters, that you can change:
- **template**. In this string you choose, how many neurons will be in each component.  **Required**
- **syn_prc**. By changing this parameter you can change the amount of synapses in your network - from default 100% (each with each) to 1% (each neuron has one input and one output). So, if the value is small, the network works faster, but the mistake is bigger.  **Default - 100**
- **nmin**. The minimum value, that the network will get/give (only positive).  **Default - 0**
- **nmax**. The maximum value, that the network will get/give (only positive).  **Default - 1**
- **co**. Learning coefficient. I don't know what this is used for :P  **Default = 0.7**

### Educating the network
If you want your network to do something, you need to educate it. And ***educate*** method does that.
```cpp
nw->educate("education.txt", true, 300);
```
There are 3 parameters, that you can change:
- **filename**. This is the name of the file (should be in the current directory).  **Required**
- **show_process**. If true, this will show you the process of education (percentage, time left, etc.).  **Default - False**
- **rep**. Repetitions. The number of times, that the network is going to educate on the given file.  **Default - 1**

In the education file one line is one task. First *template[0]* numbers are the input numbers, and the rest *template[-1]* numbers are the output (desired answer) numbers.

### Using the network
So, now we've got the educated network. Let's check something.
In this example the network was educated to multiple numbers in range(1, 1000) by 3. Let's check.
Function ***check*** receives a string with ***template[0]*** values of input signals for the input neurons. This values should be in range(nmin, nmax).
```cpp
nw->check("100");
```
This method returns **vector\<double\>**

### Saving the network to file
So, the network is educated, and we don't want to lose it. So let's save it.
In save method there is only one parameter - **filename**.
```cpp
nw->save("network.net");
```

### Loading the network from file
We saved the network, and now we can load it.
In order to do that, you need to create the network with two parameters:
-filename. The name of file, from which we want to load the network
-load. This is a boolean parameter, the value of which doesn't mean. Just set it to true or false, and the network will understand, that it need to load from file.
```cpp
Neural::Network* nw2 = new Neural::Network("network.net", true);
```
*Also you can load already created network manually - nw.load("filename");*

And now *nw2* is a copy of *nw1*, and it will work absolutely the same.

### Deleting the network
It is very easy
```cpp
delete nw;
```
> PS. A working example of this network you can find in the *'example'* folder.

## Using from the console
You should use this variant if your network is very simple, or you need to use it  as a part of the other programm.
There is a file in console_network folder, which you can run with several arguments and operate the network.
You can create the network, educate it, save and load and so on right from the console.
So, the arguments:
- GENERAL
  - **-h** Shows the help message
- NETWORK CREATION
  - -**t** *"string"*  The template for the network
  - -**sp** *"int"*    Synapse percent               
  - -**nn** *"int"*    Minimal input/output value    
  - -**nx** *"int"*    Maximal input/output value    
  - -**co** *"float"*  Learning coefficient          
- EDUCATION
  - -**e** *"file"*    File with tasks for education
  - -**sh** *"bool"*   Show process of education             
  - -**r** *"int"*     Repetitions                 
- SOLVING
  - -**i** *"file"*    Input file with task(s) to solve
  - -**ss** *"bool"*   Show process of solving              
  - -**o** *"file"*    Output file for answer(s)
- SAVING/LOADING
  - -**s** *"file"*    Will save the network to file after education
  - -**l** *"file"*    Will load the network from the file
The default values are shown in the help message.

I'll give you just a few examples of usage:

This line will create the network with template "1 10 1", educate it with the tasks from the "edu.txt" for 10 times and then save it to "network.net"
```bash
console_network.exe -t "1 10 1" -e "edu.txt" -r 10 -s "network.net"
```

This line will load the network from "network.net", solve the tasks from "input.txt" and print the answers to the console
```bash
console_network.exe -l "network.net" -i "input.txt"
```

This is quite interesting. This line will load the file from "network.net", educate it even more with tasks from "edu.txt" and then save it back to "network.txt". As a result we get even more educated network.
```bash
console_network.exe -l "network.net" -e "edu.txt" -r 10 -s "network.net"
```

>P.S. It doesn't mean in which order you write the arguments
