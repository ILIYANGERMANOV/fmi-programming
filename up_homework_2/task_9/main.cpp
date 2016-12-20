#include <iostream>

using namespace std;

int getNumberLength(int number) {
    int length = 1;
    while ((number /= 10) != 0) length++;
    return length;
}

int getValueWithoutDigit(int number, int digitIndex) {
    int result = 0;
    int base = 1;
    for (int i = 0; i <= digitIndex; ++i, number /= 10) {
        if (i == digitIndex) {
            number /= 10;
            break;
        }
        result += (number % 10) * base;
        base *= 10;
    }
    return result + number * base;
}

bool bruteForce(unsigned int firstNum, int firstNumLen, unsigned int secondNum) {
    for (int i = 0; i < firstNumLen; ++i) {
        if (getValueWithoutDigit(firstNum, i) == secondNum) return true;
    }
    return false;
}

bool canBeTransformedByRemovingOneDigit(unsigned int firstNum, unsigned int secondNum) {
    int firstNumLen = getNumberLength(firstNum);
    int secondNumLen = getNumberLength(secondNum);
    if (firstNumLen <= secondNumLen || firstNumLen > secondNumLen + 1) return false;
    return bruteForce(firstNum, firstNumLen, secondNum);
}

int main() {
    unsigned int firstNumber, secondNumber;
    cin >> firstNumber;
    cin >> secondNumber;
    if (canBeTransformedByRemovingOneDigit(firstNumber, secondNumber)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    return 0;
}