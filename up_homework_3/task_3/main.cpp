#include <iostream>
#include <string>

using namespace std;

void printRotatedWord(string word, unsigned long rotation) {
    unsigned long wordLength = word.length();
    if (wordLength == 0)
        return;
    rotation = rotation % wordLength;
    unsigned long secondPartLen = wordLength - rotation;
    for (unsigned long i = wordLength - rotation; i < wordLength; ++i) {
        cout << word[i];
    }
    for (int i = 0; i < secondPartLen; ++i) {
        cout << word[i];
    }
}

bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isWordMember(char prev, char current, char next) {
    return isLetter(current) ||
           (current == '-' && isLetter(prev) && isLetter(next));
}

bool isDelimiter(string message, int i) {
    char prev = i > 0 ? message[i - 1] : '\0';
    return !isWordMember(prev, message[i], message[i + 1]);
}

void printSolution(string message, unsigned long rotation) {
    unsigned int wordBegin = 0, wordLength = 0;
    char currentSymbol;
    for (unsigned int i = 0; i < message.length(); ++i) {
        currentSymbol = message[i];
        if (isDelimiter(message, i)) {
            if (i > 0 && isDelimiter(message, i - 1)) {
                cout << currentSymbol;
                wordBegin++;
                continue;
            }
            printRotatedWord(message.substr(wordBegin, wordLength), rotation);
            cout << currentSymbol;
            wordBegin = i + 1;
            wordLength = 0;
        } else {
            wordLength++;
        }
    }
    if (wordLength != 0) {
        printRotatedWord(message.substr(wordBegin, wordLength), rotation);
    }
    cout << endl;
}

int main() {
    string message;
    unsigned int rotation;
    getline(cin, message);
    cin >> rotation;
    printSolution(message, rotation);
    return 0;
}