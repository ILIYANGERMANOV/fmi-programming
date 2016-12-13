/**
 *  
 * Solution to homework task 
 * Introduction to programming course 
 * Faculty of Mathematics and Informatics of Sofia University 
 * Winter semester 2016/2017 
 * 
 * @author Iliyan Germanov 
 * @idnumber 81521 
 * @task 7 
 * @compiler GCC 
 * 
 */
#include <iostream>

using namespace std;

#define MAX_INPUT_VALUE 1000001

bool validateInput(int n, int m, int y) {
    if (n <= 0 || n >= MAX_INPUT_VALUE) return false;
    if (m <= 1 || m >= MAX_INPUT_VALUE) return false;
    if (y <= 0 || y >= m) return false;
    return true;
}

int mPow(int a, int n) {
    while (n > 1) {
        a *= a;
        n--;
    }
    return a;
}

int calculateNumber(int x, int n, int m) {
    return mPow(x, n) % m;
}

void printSpaces(bool &isFirstPrinted) {
    if (isFirstPrinted) {
        isFirstPrinted = false;
    } else {
        cout << ' ';
    }
}

int main() {
    int n, m, y;
    cin >> n;
    cin >> m;
    cin >> y;
    if (!validateInput(n, m, y)) {
        cout << "Invalid input!" << endl;
        return -1;
    }
    int calculatedNumber;
    bool isFirstPrint = true;
    bool isAnyNumberPrinted = false;
    for (int i = 1; i < m; ++i) {
        calculatedNumber = calculateNumber(i, n, m);
        if (calculatedNumber == y) {
            printSpaces(isFirstPrint);
            cout << calculatedNumber;
            isAnyNumberPrinted = true;
        }
    }
    if (!isAnyNumberPrinted) {
        cout << "-1";
    }
    cout << endl;
    return 0;
}
