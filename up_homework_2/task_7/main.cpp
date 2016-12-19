#include <iostream>

using namespace std;

//TODO: Fix issues so it can work properly

#define MAX_INPUT_VALUE 1000001

bool validateInput(int n, int m, int y) {
    if (n <= 0 || n >= MAX_INPUT_VALUE) return false;
    if (m <= 1 || m >= MAX_INPUT_VALUE) return false;
    if (y <= 0 || y >= m) return false;
    return true;
}

int calculateNumber(int a, int n, int m) {
    int result = 1;
    while (n > 0) {
        result *= a;
        result %= m;
        --n;
    }
    return result % m;
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
    for (int x = 1; x <= m - 1; ++x) {
        calculatedNumber = calculateNumber(x, n, m);
        if (calculatedNumber == y) {
            printSpaces(isFirstPrint);
            cout << x;
            isAnyNumberPrinted = true;
        }
    }
    if (!isAnyNumberPrinted) {
        cout << "-1";
    }
    cout << endl;
    return 0;
}
