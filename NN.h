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
    inputNode(int value);
    ~inputNode();


private:
    int value;
    vector<double> weights;
};

class outputNode {
public:
    outputNode(double value, double expectedValue);
    ~outputNode();
private:
    double value;
    double expectedValue;

};

class network {
public:
    NeuralNetwork();
    ~NeuralNetwork();
private:
};
#endif
