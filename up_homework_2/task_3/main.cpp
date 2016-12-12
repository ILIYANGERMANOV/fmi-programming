#include <iostream>
#include <map>

using namespace std;

#define MAX_INPUT_VALUE 4000000000

//TODO: investigate bugs with big numbers

bool validateInput(int number) {
    return number > 0 && number < MAX_INPUT_VALUE;
}

class FirstNumberAppearsInSecondCount {
    int mFirstNumber, mSecondNumber;
public:
    FirstNumberAppearsInSecondCount(int a, int b) {
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
        map<int, int> countMap;
        int firstNumLength = getNumberLength(mFirstNumber);
        int secondNumLength = getNumberLength(mSecondNumber);
        int *secondNumArr = convertNumberToArray(mSecondNumber, secondNumLength);

        for (int i = 0; i <= secondNumLength - firstNumLength; ++i) {
            int extractedNumber = getNumberFromArr(secondNumArr, i, firstNumLength);
            if (countMap.find(extractedNumber) == countMap.end()) {
                countMap[extractedNumber] = 1;
                continue;
            }
            countMap[extractedNumber]++;
        }
        int appearsCount = countMap.find(mFirstNumber) != countMap.end() ? countMap[mFirstNumber] : 0;

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

    int *convertNumberToArray(int number, int length) {
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
    int a, b;
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
