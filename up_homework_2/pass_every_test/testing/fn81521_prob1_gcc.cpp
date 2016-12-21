/**
 *  
 * Solution to homework task 
 * Introduction to programming course 
 * Faculty of Mathematics and Informatics of Sofia University 
 * Winter semester 2016/2017 
 * 
 * @author Iliyan Germanov 
 * @idnumber 81521 
 * @task 1 
 * @compiler GCC 
 * 
 */
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>

#define TASK_NUMBER "1"
#define STATE_FILE "state" TASK_NUMBER
#define TEST_DIR_FALLBACK "tests/"

void initStateFile();

using namespace std;

inline bool fileExists(const std::string &name) {
    ifstream f(name.c_str());
    return f.good();
}

string getStateFilePath() {
    if (fileExists(STATE_FILE)) {
        return STATE_FILE;
    } else {
        return "../" + string(STATE_FILE);
    }
}

void writeToStateFile(int value) {
    ofstream stateFile(getStateFilePath().c_str());
    stateFile << value;
    stateFile.close();
}

void initStateFile() {
    if (!fileExists(getStateFilePath())) {
        writeToStateFile(0);
    }
}

int readStateFile() {
    ifstream stateFile(getStateFilePath().c_str());
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
        if (remove(fileToDeleteName.c_str()) != 0) {
            fileToDeleteName = "../" + fileToDeleteName;
            remove(fileToDeleteName.c_str());
        }
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
        adjustAnswersFilePath();
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

    void adjustAnswersFilePath() {
        if (!fileExists(mAnswerFilePath)) {
            mAnswerFilePath = string(TEST_DIR_FALLBACK) + mAnswerFilePath;
            if (!fileExists(mAnswerFilePath)) {
                mAnswerFilePath = "../../" + mAnswerFilePath;
            }
        }
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
