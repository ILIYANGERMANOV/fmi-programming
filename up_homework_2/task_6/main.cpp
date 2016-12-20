#include <iostream>
#include <cmath>

using namespace std;

/**
 * Algorithm borrowed from Victor Mukherjee's answer in StackOverflow
 *
 * http://stackoverflow.com/questions/12983731/algorithm-for-calculating-binomial-coefficient
 *
 * @param n
 * @param k
 * @return binomial value of n over k (n!/(n!*(n-k)!)
 */
long binomial(int n, int k) {
    double sum = 0;
    for (long i = 0; i < k; i++) {
        sum += log10(n - i);
        sum -= log10(i + 1);
    }
    return (long) pow(10, sum);;
}

void printFactors(int n) {
    bool isFirstPrint = true;
    for (int k = 0; k <= n; ++k) {
        if (!isFirstPrint) {
            cout << ' ';
        } else {
            isFirstPrint = false;
        }
        cout << binomial(n, k);
    }
    cout << endl;
}

int main() {
    int n;
    cin >> n;
    printFactors(n);
    return 0;
}