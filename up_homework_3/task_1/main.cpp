#include <iostream>
#include <list>

using namespace std;

//121
//1213121
void buildProfessorXRowInList(list<int> &l, int i, int n) {
    l.push_back(i);
    l.insert(l.end(), l.begin(), --l.end());
    if (i == n) return;
    buildProfessorXRowInList(l, i + 1, n);
}

void printList(list<int> l) {
    for (list<int>::iterator it = l.begin(); it != l.end(); ++it) {
        cout << *it;
    }
    cout << endl;
}

void printProfessorXRow(int n) {
    if (n == 1) {
        cout << '1' << endl;
        return;
    } else if (n == 2) {
        cout << "121" << endl;
        return;
    }
    list<int> l = list<int>();
    l.push_back(121);
    buildProfessorXRowInList(l, 3, n);
    printList(l);
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