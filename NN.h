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
    outputNode(double value);
    ~outputNode();
private:
    double value;
    double expectedValue; //doesn't change

};

class NeuralNetwork {
public:
    NeuralNetwork(vector<vector<int> > trainingImages, vector<int> trainingKeys, double learningRate, int outputDim);
    ~NeuralNetwork();

    void train();
    void test();

    void initializeInputNodes();
    void initializeOutputNodes();

    void updateWeights(int imageIndex);
private:
    vector<inputNode> inputNodes;
    vector<outputNode> outputNodes;

    int epochs;

    vector<vector<int> > trainingImages;
    vector<int> trainingKeys;
    double learningRate;
    int outputDim;
};

#endif
