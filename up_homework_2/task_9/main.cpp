#include <iostream>

using namespace std;

//123 1



int getNumberLength(int number) {
    int length = 1;
    while ((number /= 10) != 0) length++;
    return length;
}

bool canBeTransformedByRemovingOneDigit(int firstNumber, int secondNumber) {
    int firstNumLen = getNumberLength(firstNumber);
    int secondNumLen = getNumberLength(secondNumber);
    if (firstNumLen <= secondNumLen || firstNumLen > secondNumLen + 1) return false;
    return true;
}

int main() {
    int firstNumber, secondNumber;
    cin >> firstNumber;
    cin >> secondNumber;
    if (canBeTransformedByRemovingOneDigit(firstNumber, secondNumber)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    return 0;
}