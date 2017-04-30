#ifndef NN_H
#define NN_H

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

class DigitMap {
public:
    DigitMap(int value, vector<vector<int> > map);
    ~DigitMap();

    int value; // the number contained within "map"
    vector<vector<int> > map;
};


class inputNode {
public:
    inputNode(int value);
    ~inputNode();

    int value;
};

class outputNode {
public:
    outputNode(double value, double expected);
    ~outputNode();
    vector<double> weights;
    double value;
    double expectedValue; //doesn't change

};

class NeuralNetwork {
public:
    NeuralNetwork(vector<DigitMap> trainingMaps, vector<DigitMap> testMaps, int epochs, double learningRate, int outputDim);
    ~NeuralNetwork();

    void train();
    void test();

    void initializeInputNodes(DigitMap map);
    void initializeOutputNodes(int answer);
    void initializeOutput(double answerVal);
    void initializeWeights();

    void updateWeights(int imageIndex);
private:
    vector<inputNode> inputNodes;
    vector<outputNode> outputNodes;

    vector<vector<double> > weights;
    vector<double> outputVect;
    vector<double> correctOutputVect;

    int epochs;

    vector<DigitMap> trainingMaps;
    vector<DigitMap> testMaps;

    double activationSum(int index);
    void printArrayAs2D(vector<double> list);

    double g(double x);
    double g_prime(double x);

    double learningRate;
    int outputDim;
    int correctCount;
    int totalCount;
};

#endif
