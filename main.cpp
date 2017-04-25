#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <algorithm>
#include "PSO.h"

using namespace std;

vector<vector<int>> maps;
vector<int> solutions;


void printInfo() {
	cout << endl;
	cout << "Usage:\nFor Digit Recognition with a Neural Network:\n./main trainingFile testFile type inputNodes outputNodes epochs learningRate" << endl;
	cout << "    trainingFile   = name of training file from which to read (string):" << endl;
	cout << "    testFile       = name of test file from which to read (string)" << endl;
    cout << "    type           = 32x32 bitmap or 8x8 down-sampled image (32 or 8, int)" << endl;
    cout << "    inputNodes     = number of input nodes (int)" << endl;
	cout << "    outputNodes    = number of output nodes (int)" << endl;
	cout << "    epochs         = number of epochs (iterations) to perform (int)" << endl;
    cout << "    learningRate   = learning rate for network (double)" << endl;
	cout << endl;
}



int main (int argc, char** argv) {
    string trainingFile;
    string testFile;
    int type;
    int inputNodes;
    int outputNodes;
    int epochs;
    double learningRate;

    vector<vector<int>> trainingMaps;
    vector<int> trainingSolutions;

    vector<vector<int>> testMaps;
    vector<int> testSolutions;

    if (argc != 8) {
        // incorrect number of arguments
        printInfo();
    } else {

        trainingFile = argv[1];
        testFile = argv[2];
        type = argv[3];
        inputNodes = argv[4];
        outputNodes = argv[5];
        epochs = argv[6];
        learningRate = argv[7];

    }

    cout << "YOUR INPUT VALUES:" << endl;
    cout << "   trainingFile  =  " << trainingFile << endl;
    cout << "   testFile      =  " << testFile << endl;
    cout << "   type          =  " << type << endl;
    cout << "   inputNodes    =  " << inputNodes << endl;
    cout << "   outputNodes   =  " << outputNodes << endl;
    cout << "   epochs        =  " << epochs << endl;
    cout << "   learningRate  =  " << learningRate << endl;

    readFile(trainingFile, type);
    trainingMaps = maps;
    trainingSolutions = solutions;
    maps.clear();
    solutions.clear();
    readFile(testFile, type);
    testMaps = maps;
    testSolutions = solutions;


}


void readFile(string fileName, int theType) {
    string line;
    ifstream inputFile;
    inputFile.open(fileName, ios::in);
    int type = theType;

    if(!inputFile.is_open()) {
        cerr << "ERROR: Could not open file" << endl;
        exit(1);
    } else if (type == 8) {

    } else {    //type == 32
        for (int i = 0; i < 3; i++) {
            getline(inputFile, line);
        }
        int fileIndex = 0;
        while(getline(inputFile, line)) {
            if(line[0] == ' ') {
                solutions.push_back((int)line[1]);
                fileIndex++;
            } else {
                vector<int> thisMap;
                for(int i = 0; i < 32; i++) {
                    thisMap.push_back((int)line[i]);
                }
                maps.push_back(thisMap);
            }
        }
    }
}
