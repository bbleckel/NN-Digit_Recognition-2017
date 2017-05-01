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


outputNode::outputNode(double value, double expected) {
    this->value = value;
    this->expectedValue = expected;
}

outputNode::~outputNode() {
    // destructor
}

NeuralNetwork::NeuralNetwork(vector<DigitMap> trainingMaps, vector<DigitMap> testMaps, int epochs, double learningRate, int outputDim) {
    // cout << "Perceptron created!" << endl;

    this->trainingMaps = trainingMaps;
    this->testMaps = testMaps;
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
void NeuralNetwork::initializeOutputNodes(int answer) {
    outputNodes.clear();
    if (outputDim == 10) {
        for (int i = 0; i < outputDim; i++) {
            if(i == answer) {
                outputNode node = outputNode(i, 1);
                outputNodes.push_back(node);
            } else {
                outputNode node = outputNode(i, 0);
                outputNodes.push_back(node);
            }
        }
    } else { //outputDim = 1

        double correctOut = ((double)answer / 10.0);
        outputNode node = outputNode(0, correctOut);

        outputNodes.push_back(node);
    }
}

void NeuralNetwork::printArrayAs2D(vector<double> list) {
    for(int i = 0; i < list.size(); i++) {
        if(i % trainingMaps[0].map.size() == 0) {
            cout << endl;
        }
        cout << list[i] << " ";
    }
}

void NeuralNetwork::updateWeights(int imageIndex) {
    for(int j = 0; j < outputDim; j++) {
        double sum = activationSum(j);
        double output = g(sum);
        outputNodes[j].value = output;
        double deriv = g_prime(sum);
        double error = outputNodes[j].expectedValue - output;

        // update bias node (first in weights)
        double biasWeight = weights[j][0];
        double biasUpdate = learningRate * error * deriv;
        weights[j][0] += biasUpdate;

        for(int i = 1; i < weights[j].size(); i++) {
            double update = learningRate * error * deriv * inputNodes[i].value;

            update += weights[j][i];
            weights[j][i] = update;
        }
    }
}

double NeuralNetwork::test() {
    int correctTestCount = 0;
    vector<int> digitsClassified(10, 0);
    vector<int> totalDigits(10, 0);

    if(outputDim == 10) {
        for (int i = 0; i < testMaps.size(); i++) {
            initializeInputNodes(testMaps[i]);
            double max = INT_MIN;
            int digitClass = -1;
            for (int n = 0; n < outputDim; n++) {
                double sum = activationSum(n);
                double output = g(sum);

                if (output > max) {
                    max = output;
                    digitClass = n;
                }
            }

            if (digitClass == testMaps[i].value) {
                digitsClassified[testMaps[i].value]++;
                correctTestCount++;
            }
            totalDigits[testMaps[i].value]++;
        }
    } else { // outputDim = 1
               for (int i = 0; i < testMaps.size(); i++) {
                   initializeInputNodes(testMaps[i]);

                   double sum = activationSum(0);
                   double output = floor(g(sum) * 10);

                   if (output == testMaps[i].value) {
                       digitsClassified[testMaps[i].value]++;
                       correctTestCount++;
                   }
                   totalDigits[testMaps[i].value]++;
               }
    }

    cout << endl << "Tested " << testMaps.size() << " images on the Network." << endl;
    cout << "Correctly classified " << correctTestCount << " (";
    cout << ((double)correctTestCount/(double)testMaps.size())*100.0 << "\%)." << endl << endl;

    cout << "Table of correctly classified digits vs total digit count:" << endl;
    for (int i = 0; i < digitsClassified.size(); i++) {
        cout << "--------|--------\t------------------" << endl;
        cout << i << "\t|\t" << digitsClassified[i] << "\t| " << totalDigits[i];
        cout << " | " << ((double)digitsClassified[i]/(double)totalDigits[i])*100;
        cout << "\% |" << endl;
    }
    cout << "--------|--------\t------------------" << endl;

    return ((double)correctTestCount/(double)testMaps.size())*100.0;
}

//train the network
vector<double> NeuralNetwork::train() {
    initializeOutputNodes(-1); //create vector of output nodes
    initializeInputNodes(trainingMaps[0]); //create vector of input nodes
    initializeWeights();

   vector<double> correctPercVect;

    for (int e = 0; e < epochs; e++) {
        // cout << "Epoch " << e + 1 << endl;
        correctCount = 0;
        totalCount = 0;
        for (int i = 0; i < trainingMaps.size(); i++) {

            initializeOutputNodes(trainingMaps[i].value); //create vector of output nodes
            initializeInputNodes(trainingMaps[i]); //create vector of input nodes

            //update weights
            updateWeights(i);

            double max = 0;
            int result = -1;
            if (outputDim == 10) {
                for(int p = 0; p < outputNodes.size(); p++) {
                    if(outputNodes[p].value > max) {
                        max = outputNodes[p].value;
                        result = p;
                    }
                }
            } else { // outputDim = 1
                double val = outputNodes[0].value * 10.0;
                result = floor(val);
            }
            if(result == trainingMaps[i].value) {
                correctCount++;
            }
            totalCount++;

        }
        cout << "Correct classifications: " << correctCount << endl;
        cout << "Total classifications: " << totalCount << endl;
        cout << "Ratio: " << correctCount / (double) totalCount << endl;

        correctPercVect.push_back((correctCount / (double) totalCount)*100);
    }

    return correctPercVect;
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
    // activation function
    double b = 0.5 - x;
    // double b = 0 - x;
    double e = exp(b);
    double r = 1 + e;
    double result = pow(r, -1);

    return result;
}

double NeuralNetwork::g_prime(double x) {
    // derivative of activation function
    double e = exp(x);
    double numerator = sqrt(exp(1)) * e;
    // double numerator = e;
    double denominator = pow(sqrt(exp(1)) + e, 2);
    // double denominator = pow(e + 1, 2);
    double result = numerator / denominator;

    return result;
}
