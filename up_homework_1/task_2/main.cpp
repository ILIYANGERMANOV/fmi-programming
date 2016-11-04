#include <iostream>

using namespace std;

/*
 * Да се напише програма, която прочита цяло положително число с 10 цифри — ЕГН на български гражданин.
 * Програмата трябва да провери дали даденият ЕГН е валиден и ако да —
 * да изведе на екрана разделени с интервал датата на раждане (във формат ДД.ММ.ГГГГ)
 * и пола на съответния човек (главна латинска буква M или F).
 * Ако въведените данни не са валидно ЕГН, да се изведе текста "Bad input data!".
 */

class InvalidCitizenNumberException {
public:
    void print() {
        cout << "Bad input data!" << endl;
    }
};

bool validateCitizenNumber(long citizenNumber) {
    //TODO: validate citizen number
    return false;
}

long readUniqueCitizenNumberFromStdIN() {
    long uniqueCitizenNumber;
    cin >> uniqueCitizenNumber;
    if (!validateCitizenNumber(uniqueCitizenNumber)) {
        throw InvalidCitizenNumberException();
    }
    return uniqueCitizenNumber;
}

int main() {
    try {
        long uniqueCitizenNumber = readUniqueCitizenNumberFromStdIN();
        cout << uniqueCitizenNumber << endl;
    } catch (InvalidCitizenNumberException ex) {
        ex.print();
    }

    return 0;
}