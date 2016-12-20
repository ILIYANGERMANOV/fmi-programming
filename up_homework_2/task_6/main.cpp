#include <iostream>

using namespace std;

// Optimized algorithm borrowed from https://github.com/meyerd/binomial
//
//unsigned long long binomialCoefficient(unsigned long long n, unsigned long long k) {
//    // symmetry
//    if (k > n - k) {
//        k = n - k;
//    }
//    if (k > n / 2) {
//        k = n - k;
//    }
//
//    unsigned long long counter = 1;
//    unsigned long long result = 1;
//    for (; counter <= k; counter++) {
//        result *= n--;
//        result /= counter;
//    }
//
//    return result;
//}

unsigned long long dropDownProduct(int n, int k) {
    unsigned long long result = 1;
    for (int i = 0; i < k; ++i) {
        result *= (n - i);
    }
    return result;
}

unsigned long long factorial(int n) {
    unsigned long long result = 1;
    while (n > 0) {
        result *= n;
        n--;
    }
    return result;
}

//Mine algorithm
int binomialCoefficient(int n, int k) {
    if (n == k) return 1;
    if (n == k - 1) return n;
    if (k == 0) return 1;
    int nMinusK = n - k;
    if (k < nMinusK) {
        return (int) (dropDownProduct(n, n - nMinusK) / factorial(k));
    } else {
        return (int) (dropDownProduct(n, n - k) / factorial(nMinusK));
    }
}

void printFactors(int n) {
    bool isFirstPrint = true;
    for (int k = 0; k <= n; ++k) {
        if (!isFirstPrint) {
            cout << ' ';
        } else {
            isFirstPrint = false;
        }
        cout << binomialCoefficient(n, k);
    }
    cout << endl;
}

int main() {
    int n;
    cin >> n;
    printFactors(n);
    return 0;
}