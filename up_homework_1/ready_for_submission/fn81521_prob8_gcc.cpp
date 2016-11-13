#include <iostream>

using namespace std;

/*
 * Разполагаме с банкноти от 50, 20, 10, 5, 2 и 1 лева.
 * Дадена сума може да бъде представена по много различни начини от банкнотите.
 */

//Chain of responsibility pattern
class Bill {
    int mValue;
    int mUsedCount;
    Bill *mSuccessor;
public:
    Bill(int value) {
        mValue = value;
        mUsedCount = 0;
        mSuccessor = 0;
    }

    Bill &setSuccessor(Bill *successor) {
        mSuccessor = successor;
        return *successor;
    }

    void presentSum(int &sum) {
        if (sum >= mValue) {
            sum -= mValue;
            mUsedCount++;
        } else if (mSuccessor) {
            mSuccessor->presentSum(sum);
        }
    }

    void printUsage(bool &isFirst) {
        if (mUsedCount > 0) {
            if (isFirst) {
                isFirst = false;
            } else {
                cout << " + ";
            }
            cout << mUsedCount << '*' << mValue;
        }
    }
};

void presentSum(Bill& largestBill, int sum) {
    if (sum <= 0) return;
    largestBill.presentSum(sum);
    presentSum(largestBill, sum);
}

int main() {
    int sum;
    cin >> sum;
    Bill leva50 = Bill(50);
    Bill leva20 = Bill(20);
    Bill leva10 = Bill(10);
    Bill leva5 = Bill(5);
    Bill leva2 = Bill(2);
    Bill leva1 = Bill(1);


    leva50.setSuccessor(&leva20)
            .setSuccessor(&leva10)
            .setSuccessor(&leva5)
            .setSuccessor(&leva2)
            .setSuccessor(&leva1);

    presentSum(leva50, sum);

    bool isFirst = true;
    cout << sum << " = ";
    leva50.printUsage(isFirst);
    leva20.printUsage(isFirst);
    leva10.printUsage(isFirst);
    leva5.printUsage(isFirst);
    leva2.printUsage(isFirst);
    leva1.printUsage(isFirst);
    cout << endl;

    return 0;
}