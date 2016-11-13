/**
 *  
 * Solution to homework task 
 * Introduction to programming course 
 * Faculty of Mathematics and Informatics of Sofia University 
 * Winter semester 2016/2017 
 * 
 * @author Iliyan Germanov 
 * @idnumber 81521 
 * @task 2 
 * @compiler GCC 
 * 
 */
#include <iostream>

using namespace std;

/*
 * Да се напише програма, която прочита цяло положително число с 10 цифри — ЕГН на български гражданин.
 * Програмата трябва да провери дали даденият ЕГН е валиден и ако да —
 * да изведе на екрана разделени с интервал датата на раждане (във формат ДД.ММ.ГГГГ)
 * и пола на съответния човек (главна латинска буква M или F).
 * Ако въведените данни не са валидно ЕГН, да се изведе текста "Bad input data!".
 */
#define CITIZEN_NUMBER_LENGTH 10

//TODO: Refactor and optimize
class InvalidCitizenNumberException {
public:
    void printError() {
        cout << "Bad input data!" << endl;
    }
};

class UniqueCitizenNumber {
    int mCitizenNumber[CITIZEN_NUMBER_LENGTH];

    int mYear, mMonth, mDate;

    void buildCitizenNumberArray(long citizenNumber, int *arr) {
        if (citizenNumber <= 0) return;
        static int index = CITIZEN_NUMBER_LENGTH;
        arr[--index] = (int) (citizenNumber % 10);
        buildCitizenNumberArray(citizenNumber / 10, arr);
    }

    bool validateCitizenNumberLength(long citizenNumber) {
        return citizenNumber >= 1000000000 && citizenNumber < 10000000000;
    }

public:
    UniqueCitizenNumber(long citizenNumber) {
        if (!validateCitizenNumberLength(citizenNumber)) {
            throw InvalidCitizenNumberException();
        }
        buildCitizenNumberArray(citizenNumber, mCitizenNumber);
        mYear = mCitizenNumber[0] * 10 + mCitizenNumber[1];
        mMonth = mCitizenNumber[2] * 10 + mCitizenNumber[3];
        mDate = mCitizenNumber[4] * 10 + mCitizenNumber[5];
        if (mMonth > 40) {
            mYear += 2000;
        } else if (mMonth > 20) {
            mYear += 1800;
        } else {
            mYear += 1900;
        }
    }

    //97 02 07 2332
    void printInfo() {
        if (!validateCitizenNumber()) throw InvalidCitizenNumberException();
        printFormattedValue(mDate);
        printFormattedValue(mMonth);
        cout << mYear;
        printGender();
        cout << endl;
    }

    void printFormattedValue(int value) {
        if (value < 10) {
            cout << '0';
        }
        cout << value;
        cout << '.';
    }

    void printGender() {
        cout << ' ';
        if (mCitizenNumber[8] % 2 == 0) {
            cout << 'M';
        } else {
            cout << 'F';
        }
    }

    bool validateCitizenNumber() {
        if (!validateCitizenNumberMonth()) return false;
        int transformedMonth = transformMonth();
        if (!validateDate(transformedMonth)) return false;
        if (!validateControlNumber()) return false;
        mMonth = transformedMonth;
        return true;
    }

    bool validateControlNumber() {
        int sum = 0;
        sum += mCitizenNumber[0] * 2;
        sum += mCitizenNumber[1] * 4;
        sum += mCitizenNumber[2] * 8;
        sum += mCitizenNumber[3] * 5;
        sum += mCitizenNumber[4] * 10;
        sum += mCitizenNumber[5] * 9;
        sum += mCitizenNumber[6] * 7;
        sum += mCitizenNumber[7] * 3;
        sum += mCitizenNumber[8] * 6;
        int sumReminder = sum % 11;
        int controlNumber = sumReminder < 10 ? sumReminder : 0;
        return controlNumber == mCitizenNumber[9];
    }

    int transformMonth() {
        if (mMonth > 40) {
            return mMonth - 40;
        } else if (mMonth > 20) {
            return mMonth - 20;
        } else {
            return mMonth;
        }
    }

    bool validateDate(int month) {
        if (mDate <= 0)
            return false;
        int MONTHS_DAYS[] = {
                31, -1, 31, 30,
                31, 30, 31, 31,
                30, 31, 30, 31
        };

        int monthArrayIndex = month - 1;
        int maxMonthDays = MONTHS_DAYS[monthArrayIndex];
        if (maxMonthDays == -1) {
            int februaryDays = mYear % 4 == 0 ? 29 : 28;
            return mDate <= februaryDays;
        } else {
            return mDate <= maxMonthDays;
        }
    }

    bool validateCitizenNumberMonth() {
        return validateMonth(mMonth) || validateMonth(mMonth - 20) || validateMonth(mMonth - 40);
    }

    bool validateMonth(int month) {
        return month > 0 && month <= 12;
    }

    void print() {
        for (int i = 0; i < CITIZEN_NUMBER_LENGTH; ++i) {
            cout << mCitizenNumber[i];
        }
        cout << endl;
    }
};


int main() {
    try {
        long citizenNumberInput;
        cin >> citizenNumberInput;
        UniqueCitizenNumber uniqueCitizenNumber = UniqueCitizenNumber(citizenNumberInput);
//        uniqueCitizenNumber.print();
        uniqueCitizenNumber.printInfo();
    } catch (InvalidCitizenNumberException ex) {
        ex.printError();
    }

    return 0;
}