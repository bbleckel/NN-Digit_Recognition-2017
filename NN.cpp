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

NeuralNetwork::NeuralNetwork(vector<DigitMap> trainingMaps, vector<DigitMap> testMaps, int epochs, double learningRate, int outputDim) {
    cout << "Perceptron created!" << endl;

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
    weights.push_back(1); // bias node

    // size - 1: bias node already added
    for(int i = 0; i < inputNodes.size() - 1; i++) {
<<<<<<< HEAD
        double randNum = (((double) rand() / RAND_MAX) * 0.3) - 0.15; //initialize random weights between -0.15 and 0.15
        //double randNum = (((double) rand() / RAND_MAX) * 2) - 1; //initialize random weights between -1 and 1
=======
        double randNum = (((double) rand() / RAND_MAX) * 0.5) - 0.25; //initialize random weights between -0.15 and 0.15
//        double randNum = (((double) rand() / RAND_MAX) * 2) - 1; //initialize random weights between -1 and 1
>>>>>>> origin/master
        weights.push_back(randNum);
    }

    cout << "Initialized: " << weights.size() << " versus " << inputNodes.size() << endl;
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

void NeuralNetwork::initializeOutput(double answerVal) {
    outputVect.clear();
    correctOutputVect.clear();
    if (outputDim == 10) {
        for(int i = 0; i < outputDim; i++) {
            int expected;
            if (outputDim == answerVal) {
                expected = 1;
            } else {
                expected = 0;
            }
            correctOutputVect.push_back(expected);
            outputVect.push_back(0);
        }

    } else { // outputDim = 1
        double expected = answerVal / 10;
        correctOutputVect.push_back(expected);
        outputVect.push_back(0.0);
    }
}


//initialize the output node(s) based on the outputDim
void NeuralNetwork::initializeOutputNodes() {
    // outputNodes.clear();
    // int initValue; // whatever we're initializing the values to
    // if (outputDim == 10) {
    //     for (int i = 0; i < outputDim; i++) {
    //         outputNode node = outputNode();
    //         outputNodes.push_back(node);
    //     }
    // } else { // outputDim = 1
    //     outputNode node = outputNode();
    //     outputNodes.push_back(node);
    // }
   // if (outputDim == 10) {
   //     for (int i = 0; i < outputDim; i++) {
   //         outputNode node;
   //         if (i == key[0]) {
   //             node = outputNode(1.0);
   //         } else {
   //             node = outputNode(0.0);
   //         }
   //
   //         outputNodes.push_back(node);
   //     }
   // } else {
   //     outputNode node = outputNode((double)key[0]/10);
   // }
    // } else { //outputDim = 1
    //     outputNode node = outputNode();
    //     outputNodes.push_back(node);
    // }
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

void NeuralNetwork::printArrayAs2D(vector<double> list) {
    for(int i = 0; i < list.size(); i++) {
        if(i % trainingMaps[0].map.size() == 0) {
            cout << endl;
        }
    //    int row; // corresponds to y coord.
    //    int col; // corresponds to x coord.
    //    row = floor(i / trainingMaps[imageIndex].map.size());
    //    col = i - row * trainingMaps[imageIndex].map.size();
        cout << list[i] << " ";
    }
}


void NeuralNetwork::updateWeights(int imageIndex) {
    double sum = activationSum();
    double output = floor(g(sum) * 10);
    // double output = g(sum);
    double deriv = g_prime(sum);
    if(output == trainingMaps[imageIndex].value) {
        correctCount++;
    }
    totalCount++;

    for(int i = 0; i < weights.size(); i++) {
    //    cout << "At " << i << endl;
        int row; // corresponds to y coord.
        int col; // corresponds to x coord.
        row = floor(i / trainingMaps[imageIndex].map.size());
        col = i - row * trainingMaps[imageIndex].map.size();

    //    cout << "(row, col) " << row << ", " << col << endl;

    //    cout << "Initial weight = " << weights[i] << endl;
        double error = trainingMaps[imageIndex].value - output;
    //    cout << "Position here is " << trainingMaps[imageIndex].map[col][row] << endl;
        double update = learningRate * error * deriv * trainingMaps[imageIndex].map[col][row];


        update += weights[i];
        weights[i] = update;
    //    cout << "New weight = " << weights[i] << endl;;
    }

}

void NeuralNetwork::test() {
    cout << "Testing: ..." << endl;
    int correctTestCount = 0;
    vector<int> digitsClassified(10, 0);
    vector<int> totalDigits(10, 0);

    for (int i = 0; i < testMaps.size(); i++) {
        initializeInputNodes(testMaps[i]);

        double sum = activationSum();
        double output = floor(g(sum) * 10);

        if (output == testMaps[i].value) {
            digitsClassified[testMaps[i].value]++;
            correctTestCount++;
        }
        totalDigits[testMaps[i].value]++;
    }

    cout << endl << "Tested " << testMaps.size() << " images on the Network." << endl;
    cout << "Correctly classified " << correctTestCount << " (";
    cout << ((double)correctTestCount/(double)testMaps.size())*100.0 << "\%)." << endl << endl;

    cout << "Table of correctly classified digits vs total digit count:" << endl;
    for (int i = 0; i < digitsClassified.size(); i++) {
        cout << "--------|--------\t-------" << endl;
        cout << i << "\t|\t" << digitsClassified[i] << "\t| " << totalDigits[i] << " |" << endl;
    }
    cout << "--------|--------\t-------" << endl;
}

//train the network
void NeuralNetwork::train() {

    initializeInputNodes(trainingMaps[0]); //create vector of input nodes
    initializeOutputNodes(); //create vector of output nodes
    initializeWeights();
    // printArrayAs2D(weights);

    for (int e = 0; e < epochs; e++) {
        cout << "Epoch " << e + 1 << endl;
        correctCount = 0;
        totalCount = 0;
        for (int i = 0; i < trainingMaps.size(); i++) {

    //    for (int i = 0; i < 4; i++) {
        //    cout << "Training epoch " << e << ", map " << i << endl;
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
    // cout << "g for " << x << endl;
    if(x > 200) {
        // avoid nan
        // cout << "g returning 1" << endl;
        return 1;
    }

    // activation function
    double b = 0.5 - x;
    // cout << "b = " << b << endl;
    double e = exp(b);
    // cout << "e = " << e << endl;

    double r = 1 + e;
    // cout << "r = " << r << endl;

    double result = pow(r, -1);

    return result;
}

double NeuralNetwork::g_prime(double x) {
    if(x > 200) {
        // cout << "deriv returning 1 " << endl;
        // avoid nan
        return 0;
    }
    // derivative of activation function
   // cout << "for " << x << endl;
    double e = exp(x);
   // cout << "e = " << e << endl;
    double numerator = sqrt(exp(1)) * e;
   // cout << "num = " << numerator << endl;

    double denominator = pow(sqrt(exp(1)) + e, 2);
   // cout << "denom = " << denominator << endl;

    double result = numerator / denominator;
   // cout << "result = " << result << endl;


    return result;
}
