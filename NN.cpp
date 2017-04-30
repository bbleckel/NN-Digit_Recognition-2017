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

void NeuralNetwork::initializeWeights() {
    weights.clear();
    for(int i = 0; i < outputDim; i++) {
        vector<double> tempWeights;
        tempWeights.push_back(1); // bias node
        
        // size - 1: bias node already added
        for(int i = 0; i < inputNodes.size() - 1; i++) {
            double randNum = (((double) rand() / RAND_MAX) * 0.3) - 0.15; //initialize random weights between -0.15 and 0.15
            //        double randNum = (((double) rand() / RAND_MAX) * 2) - 1; //initialize random weights between -1 and 1
//            tempWeights.push_back(0);
            tempWeights.push_back(randNum);
        }
        weights.push_back(tempWeights);
    }
}

//create the vector of input nodes, each initialized to the value of the first image
void NeuralNetwork::initializeInputNodes(DigitMap map) {
    inputNodes.clear();

    inputNode biasNode = inputNode(1);
    inputNodes.push_back(biasNode);

    for(int i = 0; i < map.map.size(); i++) {
        for(int j = 0; j < map.map[i].size(); j++) {
            // this node has value corresponding to the value in the map
            inputNode node = inputNode(map.map[i][j]);
            inputNodes.push_back(node);
        }
    }
}

//initialize the output node(s) based on the outputDim
void NeuralNetwork::initializeOutputNodes() {
    outputNodes.clear();
    int initValue; // whatever we're initializing the values to
    if (outputDim == 10) {
        for (int i = 0; i < outputDim; i++) {
            // ADDED 0 TEMPORARILY
            outputNode node = outputNode(i);
            outputNodes.push_back(node);
        }
    } else { //outputDim = 1
        outputNode node = outputNode(0);
        outputNodes.push_back(node);
    }
}

void NeuralNetwork::printArrayAs2D(vector<double> list) {
    for(int i = 0; i < list.size(); i++) {
        if(i % trainingMaps[0].map.size() == 0) {
            cout << endl;
        }
//        int row; // corresponds to y coord.
//        int col; // corresponds to x coord.
//        row = floor(i / trainingMaps[imageIndex].map.size());
//        col = i - row * trainingMaps[imageIndex].map.size();
        cout << list[i] << " ";
    }
}


void NeuralNetwork::updateWeights(int imageIndex) {
    for(int j = 0; j < outputDim; j++) {
        double sum = activationSum(j);
        double output = g(sum);
//        cout << "Sum = " << sum << ", output = " << output << endl;
        outputNodes[j].value = output;
        //    double output = g(sum);
        double deriv = g_prime(sum);
        double error = trainingMaps[imageIndex].value - output;
        
        // update bias node (first in weights)
        double biasWeight = weights[j][0];
        double biasUpdate = learningRate * error * deriv;
        weights[j][0] += biasUpdate;
        
        for(int i = 1; i < weights[j].size(); i++) {
            //        cout << "At " << i << endl;
            int row; // corresponds to y coord.
            int col; // corresponds to x coord.
            row = floor(i / trainingMaps[imageIndex].map.size());
            col = i - row * trainingMaps[imageIndex].map.size();
            
            //        cout << "(row, col) " << row << ", " << col << endl;
            //        if(trainingMaps[imageIndex].map[col][row] == 1) {
            //            cout << "Initial weight = " << weights[j][i] << ", sum = " << sum << ", g = " << g(sum) << endl;
            //        }
            //        cout << "Position here is " << trainingMaps[imageIndex].map[col][row] << endl;
            double update = learningRate * error * deriv * trainingMaps[imageIndex].map[col][row];
            
            
            update += weights[j][i];
            weights[j][i] = update;
            //        if(trainingMaps[imageIndex].map[col][row] == 1) {
            //            cout << "New weight = " << weights[j][i] << endl;;
            //        }
        }
    }
}

void NeuralNetwork::test() {
    for (int i = 0; i < testMaps.size(); i++) {

    }
}

//train the network
void NeuralNetwork::train() {

    initializeInputNodes(trainingMaps[0]); //create vector of input nodes
    initializeOutputNodes(); //create vector of output nodes
    initializeWeights();
//    for(int i = 0; i < weights.size(); i++) {
//        printArrayAs2D(weights[i]);
//    }

    for (int e = 0; e < epochs; e++) {
        cout << "Epoch " << e + 1 << endl;
        correctCount = 0;
        totalCount = 0;
        for (int i = 0; i < trainingMaps.size(); i++) {

//        for (int i = 0; i < 4; i++) {
//            cout << "Training epoch " << e << ", map " << i << endl;
            initializeInputNodes(trainingMaps[i]); //create vector of input nodes

            //update weights
            updateWeights(i);
            
            double max = 0;
            int result = -1;
            for(int p = 0; p < outputNodes.size(); p++) {
                cout << "Value of node " << p << " is " << outputNodes[p].value << endl;
                if(outputNodes[p].value > max) {
                    max = outputNodes[p].value;
                    result = p;
                }
            }
            cout << "Max is " << result << endl;
            if(result == trainingMaps[i].value) {
                correctCount++;
            }
            totalCount++;
        
        }
        cout << "Correct classifications: " << correctCount << endl;
        cout << "Total classifications: " << totalCount << endl;
        cout << "Ratio: " << correctCount / (double) totalCount << endl;
    }
}

double NeuralNetwork::activationSum(int index) {
    double sum = 0;

    // sum all inputs and weights
    for(int i = 0; i < inputNodes.size(); i++) {
        sum += inputNodes[i].value * weights[index][i];
    }

    return sum;
}

double NeuralNetwork::g(double x) {
//    cout << "g for " << x << endl;
    if(x > 200) {
        // avoid nan
//        cout << "g returning 1" << endl;
        return 1;
    }

    // activation function
    double b = 0.5 - x;
//    cout << "b = " << b << endl;
    double e = exp(b);
//    cout << "e = " << e << endl;

    double r = 1 + e;
//    cout << "r = " << r << endl;

    double result = pow(r, -1);
//    cout << "Returning " << result << endl;
    return result;
}

double NeuralNetwork::g_prime(double x) {
    if(x > 200) {
//        cout << "deriv returning 1 " << endl;
        // avoid nan
        return 0;
    }
    // derivative of activation function
//    cout << "for " << x << endl;
    double e = exp(x);
//    cout << "e = " << e << endl;
    double numerator = sqrt(exp(1)) * e;
//    cout << "num = " << numerator << endl;

    double denominator = pow(sqrt(exp(1)) + e, 2);
//    cout << "denom = " << denominator << endl;

    double result = numerator / denominator;
//    cout << "result = " << result << endl;


    return result;
}
