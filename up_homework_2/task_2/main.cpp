#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

using namespace std;

/*
 * Простите числа p и q наричаме числа близнаци, ако q = p + 2. Например 5 и 7 са числа близнаци.
 * Да се на пише програма, която прочита от стандартния вход цяло положително число n (n < 100000)
 * и извежда на стандартния изход първите n двойки числа близнаци —
 * всяка двойка на отделен ред, самите числа разделени с интервал. Припомняме, че 1 не е просто число.
 */

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
        int middleHolder;
        for (int i = 1; i <= mN - 1; ++i) {
            //twin primes formula: (6*n - 1, 6*n + 1) works for everything except (3,5)
            middleHolder = 6 * i;
            cout << middleHolder - 1 << ' ' << middleHolder + 1 << endl;
        }
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