#include <iostream>
#include <stack>
#include <vector>

using namespace std;

//1 - 1
//121 - 3
//1213121 - 7
//121312141213121 - 15
//1213121412131215121312141213121 - 31 => 2*prev + 1
//63
//127

//1213121

void fill(vector<int> source, vector<int> &target) {
    while (!source.empty()) {
        int val = source.back();
        target.push_back(val);
        source.pop_back();
    }
}

void solve(vector<int> &a, vector<int> &b, int i, int n, int final) {
    if (i == n) {
        fill(a, b);
        b.push_back(n);
        fill(a, b);
        if (i == final)
            return;
        a.clear();
        fill(b, a);
        b.clear();
        solve(a, b, i + 1, n + 1, final);
        return;
    }
    a.push_back(i);
    solve(a, b, i + 1, n, final);
}

void printProfessorXRow(int n) {
    if (n == 1) {
        cout << '1' << endl;
        return;
    }
    vector<int> a = vector<int>();
    vector<int> b = vector<int>();
    solve(a, b, 1, 2, n);
    while (!b.empty()) {
        cout << b.back();
        b.pop_back();
    }
    cout << endl;
}

int main() {
    int n;
    cin >> n;
    if (n > 20) {
        cout << "Invalid input" << endl;
        return -1;
    }
    printProfessorXRow(n);
    return 0;
}