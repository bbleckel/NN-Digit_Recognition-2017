#include "NN.h"

using namespace std;

DigitMap::DigitMap(int value, vector<vector<int> > map) {
    this->value = value;
    this->map = map;
}

DigitMap::~DigitMap() {

}

inputNode::inputNode(int value) {
    this->value = value;
}

inputNode::~inputNode(){
    // destructor
}


outputNode::outputNode(double value) {
    this->value = value;
    this->expectedValue = value;
}

outputNode::~outputNode() {
    // destructor
}

NeuralNetwork::NeuralNetwork(vector<DigitMap> trainingMaps, int epochs, double learningRate, int outputDim) {
    cout << "Perceptron created!" << endl;

    this->trainingMaps = trainingMaps;
    this->epochs = epochs;
    this->learningRate = learningRate;
    this->outputDim = outputDim;
    correctCount = 0;
    totalCount = 0;
}

NeuralNetwork::~NeuralNetwork() {

}

//create the vector of input nodes, each initialized to the value of the first image
void NeuralNetwork::initializeInputNodes(DigitMap map) {
    inputNodes.clear();
    weights.clear();

    inputNode biasNode = inputNode(1);
    inputNodes.push_back(biasNode);
    weights.push_back(1);

    for(int i = 0; i < map.map.size(); i++) {
        for(int j = 0; j < map.map[i].size(); j++) {
            // this node has value corresponding to the value in the map
            inputNode node = inputNode(map.map[i][j]);
            inputNodes.push_back(node);
        }
    }

    // size - 1: bias node already added
    for(int i = 0; i < inputNodes.size() - 1; i++) {
        double randNum = (((double) rand() / RAND_MAX) * 2) - 1; //initialize random weights between -1 and 1
        weights.push_back(randNum);
    }
}

//initialize the output node(s) based on the outputDim
void NeuralNetwork::initializeOutputNodes() {
    outputNodes.clear();
    int initValue; // whatever we're initializing the values to
    if (outputDim == 10) {
        for (int i = 0; i < outputDim; i++) {
            outputNode node = outputNode();
            outputNodes.push_back(node);
        }
    } else { //outputDim = 1
        outputNode node = outputNode();
        outputNodes.push_back(node);
    }
//    if (outputDim == 10) {
//        for (int i = 0; i < outputDim; i++) {
//            outputNode node;
//            if (i == key[0]) {
//                node = outputNode(1.0);
//            } else {
//                node = outputNode(0.0);
//            }
//
//            outputNodes.push_back(node);
//        }
//    } else {
//        outputNode node = outputNode((double)key[0]/10);
//    }
}

void NeuralNetwork::updateWeights(int imageIndex) {
    double sum = activationSum();
    double output = floor(g(sum) * 10);
//    cout << sum << endl;
    if(output == trainingMaps[imageIndex].value) {
        correctCount++;
    }
    totalCount++;
//    cout << "Result is " << output << ", real is " << trainingMaps[imageIndex].value << endl;

//    cout << "derivative is " << g_prime(sum) << " versus " << g(sum) << endl;

    for(int i = 0; i < weights.size(); i++) {
//        cout << "At " << i << endl;
        int row; // corresponds to y coord.
        int col; // corresponds to x coord.
        row = floor(i / trainingMaps[imageIndex].map.size());
        col = i - row * trainingMaps[imageIndex].map.size();

//        cout << "(row, col) " << row << ", " << col << endl;

//        cout << "Initial weight = " << weights[i] << endl;
        double error = pow(trainingMaps[imageIndex].value - output, 2);
//        double error = trainingMaps[imageIndex].value - output;

//        cout << "Position here is " << trainingMaps[imageIndex].map[col][row] << endl;
        double update = learningRate * error * g_prime(sum) * trainingMaps[imageIndex].map[col][row]; // times value?

//        cout << "e = " << error << ", update = " << update << endl;

        update += weights[i];
        weights[i] += update;
//        cout << "New weight = " << weights[i] << endl;;
    }

}

void NeuralNetwork::test() {

}

//train the network
void NeuralNetwork::train() {

//    initializeInputNodes(); //create vector of input nodes
    initializeOutputNodes(); //create vector of output nodes

    for (int e = 0; e < epochs; e++) {
        cout << "Epoch " << e << endl;
        correctCount = 0;
        totalCount = 0;
        for (int i = 0; i < trainingMaps.size(); i++) {

//        for (int i = 0; i < 10; i++) {
//            cout << "Training epoch " << e << ", map " << i << endl;
            initializeInputNodes(trainingMaps[i]); //create vector of input nodes
            //update weights
            updateWeights(i);

        }
        cout << "Correct classifications: " << correctCount << endl;
        cout << "Total classifications: " << totalCount << endl;
        cout << "Ratio: " << correctCount / (double) totalCount << endl;
    }
}

double NeuralNetwork::activationSum() {
    double sum = 0;

    // sum all inputs and weights
    for(int i = 0; i < inputNodes.size(); i++) {
        sum += inputNodes[i].value * weights[i];
    }

    return sum;
}

double NeuralNetwork::g(double x) {
    // activation function
    double b = 0.5 - x;
    double e = exp(b);
    double r = 1 + e;
    double result = pow(r, -1);

    return result;
}

double NeuralNetwork::g_prime(double x) {
    // derivative of activation function
    double e = exp(x);
    double numerator = sqrt(exp(1)) * e;
    double denominator = pow(sqrt(exp(1)) + e, 2);
    double result = numerator / denominator;

    return result;
}
