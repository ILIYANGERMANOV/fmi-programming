#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <stdio.h>
#include <cmath>

using namespace std;

#define MAX_N_VALUE 100000

class TwinPrimesGenerator {
    int mN;
public:
    TwinPrimesGenerator(int n) {
        if (n <= 0 || n > MAX_N_VALUE) {
            stringstream sStream;
            sStream << "N must be in (0, " << MAX_N_VALUE << ')';
            throw invalid_argument(sStream.str());
        }
        mN = n;
    }

    void generateAndPrint() {
        cout << "3 5" << endl;
        int middleHolder, counter = 1;
        int printedTwinPrimes = 1, firstTwin, secondTwin;
        while (printedTwinPrimes < mN) {
            middleHolder = 6 * counter;
            firstTwin = middleHolder - 1;
            secondTwin = middleHolder + 1;
            if (isPrimeNumber(firstTwin) && isPrimeNumber(secondTwin)) {
                printf("%d %d\n", firstTwin, secondTwin);
                printedTwinPrimes++;
            }
            counter++;
        }
    }

private:
    bool isPrimeNumber(int number) {
        int largesPossibleDivider = (int) sqrt(number);
        for (int divider = 2; divider <= largesPossibleDivider; ++divider) {
            if (number % divider == 0) return false;
        }
        return true;
    }
};

int main() {
    int n;
    cin >> n;
    try {
        TwinPrimesGenerator twinPrimesGenerator = TwinPrimesGenerator(n);
        twinPrimesGenerator.generateAndPrint();
    } catch (invalid_argument e) {
        cout << e.what() << endl;
    }
    return 0;
}