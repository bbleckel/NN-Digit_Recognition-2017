#include "NN.h"

using namespace std;

NeuralNetwork::NeuralNetwork(vector<vector<int> > trainingImages, vector<int> trainingKeys, int epochs double learningRate, int outputDim) {
    this.trainingImages = trainingImages;
    this.trainingKeys = trainingKeys;
    this.epochs = epochs;
    this.learningRate = learningRate;
    this.outputDim = outputDim;

    train();
}

//create the vector of input nodes, each initialized to the value of the first image
void NeuralNetwork::initializeInputNodes() {
    for (int i = 0; i < image[0].size; i++) {
        inputNode node = inputNode(image[0][i]);
        for (int i = 0; i < outputDim; i++) {
            double randNum = (((double)rand()/RAND_MAX)*2) - 1; //initialize random weights between -1 and 1
            node.weights.push_back(randNum);
        }

        inputNodes.push_back(node);
    }

    //add bias node -- THIS NEEDS TO BE CHANGED I THINK, TO SOMEHOW WORK WITH ACTIVATION ALWAYS HAPPENING ON BIAS NODE
    inputNode node = inputNode(1);
    for (int i = 0; i < outputDim; i++) {
        double num = 1; //initialize to 1
        node.weights.push_back(num);
    }
}

//initialize the output node(s) based on the outputDim and the value for the first image
void NeuralNetwork::initializeOutputNodes() {
    if (outputDim == 10) {
        for (int i = 0; i < outputDim; i++) {
            outputNode node;
            if (i == key[0]) {
                node = outputNode(1.0);
            } else {
                node = outputNode(0.0);
            }

            outputNodes.push_back(node);
        }
    } else {
        outputNode node = outputNode((double)key[0]/10);
    }
}

void NeuralNetwork::updateWeights(int imageIndex) {

}

inputNode::inputNode(int value) {
    this.value = value;
}

inputNode::~inputNode(){
    // destructor
}


outputNode::outputNode(double value) {
    this.value = value;
    this.expectedValue = value;
}

outputNode::~outputNode() {
    // destructor
}

void NeuralNetwork::test() {
    
}

//train the network
void NeuralNetwork::train() {
    initializeInputNodes(); //create vector of input nodes
    initializeOutputNodes(); //create vector of output nodes

    for (int e = 0; e < epochs; e++) {
        for (int i = 0; i < trainingImages.size(); i++) {
            //update weights
            updateWeights(i);
        }
    }
}
