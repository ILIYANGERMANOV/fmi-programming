/**
 *  
 * Solution to homework task 
 * Introduction to programming course 
 * Faculty of Mathematics and Informatics of Sofia University 
 * Winter semester 2016/2017 
 * 
 * @author Iliyan Germanov 
 * @idnumber 81521 
 * @task 9 
 * @compiler GCC 
 * 
 */
#include <iostream>

using namespace std;

int convertToDomain(int value) {
    return value % 16;
}


//THIS IS BAD PRACTISE (getter has side effect)
bool dividerNotZero(int divider) {
    if (divider == 0) {
        cout << "Division by zero!" << endl;
        return false;
    }
    return true;
}

int main() {
    char operation;
    int a, b;
    cin >> a;
    cin >> operation;
    cin >> b;
    a = convertToDomain(a);
    b = convertToDomain(b);


    int result;
    switch (operation) {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            if (!dividerNotZero(b)) {
                return 0;
            }
            result = a / b;
            break;
        case '%':
            if (!dividerNotZero(b)) {
                return 0;
            }
            result = a % b;
            break;
        default:
            cout << "Invalid input";
            return -1;
    }
    cout << result % 16 << endl;

    return 0;
}