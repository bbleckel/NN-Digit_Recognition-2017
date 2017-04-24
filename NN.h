#ifndef NN_H
#define NN_H

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <math.h>

using namespace std;

class inputNode {
public:
private:
};

class outputNode {
public:
private:
};

class NeuralNetwork {
public:
    NeuralNetwork();
    ~NeuralNetwork();

    void initializeInputs();
    void initializeOutputs();
private:
    vector<inputNode> inputNodes;
    vector<outputNode> outputNodes;
};

#endif
