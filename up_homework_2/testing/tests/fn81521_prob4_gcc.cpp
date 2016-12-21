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
    bool result = true;
    int *firstNumDigits = generateDigitsCountArr(firstNumber);
    int *secondNumDigits = generateDigitsCountArr(secondNumber);
    int countHolder1, countHolder2;
    for (int i = 0; i < 10; ++i) {
        countHolder1 = firstNumDigits[i];
        countHolder2 = secondNumDigits[i];
        if ((countHolder1 && !countHolder2) || (!countHolder1 && countHolder2)) {
            result = false;
            break;
        };
    }
    delete[] firstNumDigits;
    delete[] secondNumDigits;
    return result;
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