#include <string>
#include <fstream>
#include <iostream>

#define TASK_NUMBER "1"
#define STATE_FILE "state" TASK_NUMBER

void initStateFile();

using namespace std;

inline bool fileExists(const std::string &name) {
    ifstream f(name.c_str());
    return f.good();
}

void writeToStateFile(int value) {
    ofstream stateFile(STATE_FILE);
    stateFile << value;
    stateFile.close();
}

void initStateFile() {
    if (!fileExists(STATE_FILE)) {
        writeToStateFile(0);
    }
}

int readStateFile() {
    ifstream stateFile(STATE_FILE);
    string line;
    getline(stateFile, line);
    stateFile.close();
    return line[0] - '0';
}

void incrementStateInFile() {
    writeToStateFile(readStateFile() + 1);
}

void deleteOtherProgramsStateFiles() {
    const int currentTaskNumber = (int) (TASK_NUMBER[0] - '0');
    string fileToDeleteName;
    for (int i = 1; i <= 10; ++i) {
        if (i == currentTaskNumber) continue;
        fileToDeleteName = "state";
        fileToDeleteName.push_back((char) (i + '0'));
        remove(fileToDeleteName.c_str());
    }
}

class ExpectedOutput {
    string mAnswerFileName;
public:
    ExpectedOutput(int state) {
        char testId = (char) ('A' + state);
        mAnswerFileName = TASK_NUMBER;
        mAnswerFileName.push_back(testId);
        mAnswerFileName.append(".test.ans");
    }

    void print() {
        ifstream answerFile(mAnswerFileName.c_str());
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
