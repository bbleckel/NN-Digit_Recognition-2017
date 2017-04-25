#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <algorithm>
#include "NN.h"

using namespace std;

vector<DigitMap> maps;
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

void readFile(string fileName, int theType) {
    string line;
    ifstream inputFile;
    inputFile.open(fileName, ios::in);
    int type = theType;

    vector<vector<int> > map;
    vector<int> solutions;


    if(!inputFile.is_open()) {
        cerr << "ERROR: Could not open file" << endl;
        exit(1);
    } else if (type == 8) {

    } else {    //type == 32
        // skip first three lines of file
        for (int i = 0; i < 3; i++) {
            getline(inputFile, line);
        }
        int fileIndex = 0;
        while(getline(inputFile, line)) {
            if(line[0] == ' ') {
                // if first line is space, next number is the digit corresponding to the map
                solutions.push_back((int) (line[1] - '0'));
                fileIndex++;

                // end the previous map
                maps.push_back(DigitMap(solutions.back(), map));
                map.clear();

            } else {
                vector<int> currLine;
                for(int i = 0; i < 32; i++) {
                    currLine.push_back((int) (line[i] - '0'));
                }
                map.push_back(currLine);
            }
        }
    }

//    for(int i = 0; i < solutions.size(); i++) {
//        cout << solutions[i] << endl;
//    }
//    cout << solutions.size() << endl;
    for(int i = 0; i < maps[0].map.size(); i++) {
        for(int j = 0; j < maps[0].map[i].size(); j++) {
            cout << maps[0].map[i][j];
        }
        cout << "\n";
    }

}

int main (int argc, char** argv) {
    string trainingFile;
    string testFile;
    int type;
    int inputNodes;
    int outputNodes;
    int epochs;
    double learningRate;

    vector<DigitMap> trainingMaps;
    vector<int> trainingSolutions;

    vector<DigitMap> testMaps;
    vector<int> testSolutions;

    if (argc != 2) {
        // incorrect number of arguments
        printInfo();
        exit(1);
    } else {

        trainingFile = argv[1];
        testFile = argv[2];
        type = atoi(argv[3]);
        inputNodes = atoi(argv[4]);
        outputNodes = atoi(argv[5]);
        epochs = atoi(argv[6]);
        learningRate = atof(argv[7]);

    }

    cout << "YOUR INPUT VALUES:" << endl;
    cout << "   trainingFile  =  " << trainingFile << endl;
    cout << "   testFile      =  " << testFile << endl;
    cout << "   type          =  " << type << endl;
    cout << "   inputNodes    =  " << inputNodes << endl;
    cout << "   outputNodes   =  " << outputNodes << endl;
    cout << "   epochs        =  " << epochs << endl;
    cout << "   learningRate  =  " << learningRate << endl;


    // for training
    readFile(trainingFile, type);
    trainingMaps = maps;
    trainingSolutions = solutions;

    // clear globals
    maps.clear();
    solutions.clear();


    // for testing
    // readFile(testFile, type);
    // testMaps = maps;
    // testSolutions = solutions;


}
