/**
 *  
 * Solution to homework task 
 * Introduction to programming course 
 * Faculty of Mathematics and Informatics of Sofia University 
 * Winter semester 2016/2017 
 * 
 * @author Iliyan Germanov 
 * @idnumber 81521 
 * @task 3 
 * @compiler GCC 
 * 
 */
#include <iostream>
#include <map>

using namespace std;

#define MAX_INPUT_VALUE 4000000000

//TODO: investigate bugs with big numbers

bool validateInput(unsigned int number) {
    return number > 0 && number < MAX_INPUT_VALUE;
}

class FirstNumberAppearsInSecondCount {
    unsigned int mFirstNumber, mSecondNumber;
public:
    FirstNumberAppearsInSecondCount(unsigned int a, unsigned int b) {
        mFirstNumber = a;
        mSecondNumber = b;
    }

    void printValue() {
        if (mFirstNumber > mSecondNumber) {
            cout << '0' << endl;
        } else {
            cout << countAppearsTimes() << endl;
        }
    }

private:
    int countAppearsTimes() {
        int appearsCount = 0;
        int firstNumLength = getNumberLength(mFirstNumber);
        int secondNumLength = getNumberLength(mSecondNumber);
        int *secondNumArr = convertNumberToArray(mSecondNumber, secondNumLength);

        for (int i = 0; i <= secondNumLength - firstNumLength; ++i) {
            int extractedNumber = getNumberFromArr(secondNumArr, i, firstNumLength);
            if (extractedNumber == mFirstNumber) {
                appearsCount++;
            }
        }

        delete[] secondNumArr;
        return appearsCount;
    }

    int getNumberFromArr(int *arr, int position, int numLen) {
        int number = 0, factor = 1;
        for (int i = position; i < position + numLen; ++i) {
            number += arr[i] * factor;
            factor *= 10;
        }
        return number;
    }

    int getNumberLength(int number) {
        int length = 1;
        while ((number /= 10) != 0) length++;
        return length;
    }

    int *convertNumberToArray(unsigned int number, int length) {
        int *array = new int[length];
        int counter = 0;
        while (number != 0) {
            array[counter++] = number % 10;
            number /= 10;
        }
        return array;
    }
};

int main() {
    unsigned int a, b;
    cin >> a;
    cin >> b;
    if (!validateInput(a) || !validateInput(b)) {
        cout << "Invalid input!" << endl;
        return -1;
    }
    FirstNumberAppearsInSecondCount count = FirstNumberAppearsInSecondCount(a, b);
    count.printValue();
    return 0;
}
