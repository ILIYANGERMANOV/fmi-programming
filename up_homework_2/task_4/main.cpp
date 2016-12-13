#include <iostream>

using namespace std;

void setZeros(int *arr, int len) {
    for (int i = 0; i < len; ++i) {
        arr[i] = 0;
    }
}

int *generateDigitsCountArr(int number) {
    int *digitsCountArr = new int[10];
    setZeros(digitsCountArr, 10);
    while (number != 0) {
        digitsCountArr[number % 10]++;
        number /= 10;
    }
    return digitsCountArr;
}

bool hasCommonSet(int firstNumber, int secondNumber) {
    bool hasCommonSetResult = true;
    int *firstNumDigits = generateDigitsCountArr(firstNumber);
    int *secondNumDigits = generateDigitsCountArr(secondNumber);
    int digitCountHolder1, digitCountHolder2;
    for (int i = 0; i < 10; ++i) {
        digitCountHolder1 = firstNumDigits[i];
        digitCountHolder2 = secondNumDigits[i];
        if ((digitCountHolder1 && !digitCountHolder2) || (!digitCountHolder1 && digitCountHolder2)) {
            hasCommonSetResult = false;
            break;
        };
    }
    delete[] firstNumDigits;
    delete[] secondNumDigits;
    return hasCommonSetResult;
}

int abs(int number) {
    return number >= 0 ? number : -number;
}

int main() {
    int firstNumber, secondNumber;
    cin >> firstNumber;
    cin >> secondNumber;
    if (hasCommonSet(abs(firstNumber), abs(secondNumber))) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    return 0;
}