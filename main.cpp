#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <algorithm>
#include "NN.h"

using namespace std;

int type;
string fileName;


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

vector<DigitMap> readFile(string fileName) {
    string line;
    ifstream inputFile;
    inputFile.open(fileName, ios::in);
    
    vector<DigitMap> maps;
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
    return maps;
}

int main (int argc, char** argv) {
    srand(time(NULL));
    if(argc != 2) {
        // incorrect input
        printInfo();
        exit(1);
    } else {
        vector<DigitMap> maps;

        string fileName = argv[1];
        maps = readFile(fileName);
        
        cout << "Successfully read file:\n" << maps.size() << " maps, dimension " << maps[0].map[0].size() << "x" << maps[0].map[0].size() << endl;
        
        NeuralNetwork n = NeuralNetwork(maps, 10, 0.01, 1);
        n.train();
    }
}
