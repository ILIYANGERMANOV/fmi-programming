/**
 *  
 * Solution to homework task 
 * Introduction to programming course 
 * Faculty of Mathematics and Informatics of Sofia University 
 * Winter semester 2016/2017 
 * 
 * @author Iliyan Germanov 
 * @idnumber 81521 
 * @task 4 
 * @compiler GCC 
 * 
 */
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/param.h>

#define TASK_NUMBER "4"
#define STATE_FILE "state" TASK_NUMBER
#define TEST_DIR_FALLBACK "tests/"

void initStateFile();

using namespace std;

inline bool fileExists(const std::string &name) {
    ifstream f(name.c_str());
    return f.good();
}

static int maxTries = 5;

string tryToGetPath(string initialPath) {
//    cout << initialPath << endl;
    if (fileExists(initialPath) || maxTries == 0) {
        return initialPath;
    }
    maxTries--;
    return tryToGetPath("../" + initialPath);
}

void writeToStateFile(int value) {
    ofstream stateFile(tryToGetPath(STATE_FILE).c_str());
    stateFile << value;
    stateFile.close();
}

void initStateFile() {
    maxTries = 2;
    if (!fileExists(tryToGetPath(STATE_FILE))) {
        writeToStateFile(0);
    }
}

int readStateFile() {
    maxTries = 5;
    ifstream stateFile(tryToGetPath(STATE_FILE).c_str());
    string line;
    getline(stateFile, line);
    stateFile.close();
    return atoi(line.c_str());
}

void incrementStateInFile() {
    writeToStateFile(readStateFile() + 1);
}

void deleteOtherProgramsStateFiles() {
    const int currentTaskNumber = atoi(TASK_NUMBER);
    string fileToDeleteName;
    for (int i = 1; i <= 10; ++i) {
        if (i == currentTaskNumber) continue;
        fileToDeleteName = "state";
        stringstream sStream;
        sStream << i;
        fileToDeleteName += sStream.str();
        maxTries = 5;
        string fileToDeletePath = tryToGetPath(fileToDeleteName);
        remove(fileToDeletePath.c_str());
    }
}

class ExpectedOutput {
    string mAnswerFilePath;
public:
    ExpectedOutput(int state) {
        char testId = (char) ('A' + state);
        mAnswerFilePath = TASK_NUMBER;
        mAnswerFilePath.push_back(testId);
        mAnswerFilePath.append(".test.ans");
    }

    void print() {
        maxTries = 5;
//        cout << "Now" << endl;
        mAnswerFilePath = tryToGetPath(TEST_DIR_FALLBACK + mAnswerFilePath);
        ifstream answerFile(mAnswerFilePath.c_str());
        string line;
        if (answerFile.is_open()) {
            while (getline(answerFile, line)) {
                cout << line << '\n';
            }
            answerFile.close();
        }
        answerFile.close();
    }


};

int main(int argc, char *argv[]) {
    initStateFile();
    ExpectedOutput expectedOutput = ExpectedOutput(readStateFile());
    expectedOutput.print();
    incrementStateInFile();
    deleteOtherProgramsStateFiles();
    return 0;
}
