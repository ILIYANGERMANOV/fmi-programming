/*
 * Warning: Java and Android conventions used!
 */
#include <iostream>

using namespace std;

#define NUMBER_MIN_VALUE 0
#define NUMBER_MAX_VALUE 3000

/*
 * Да се напише програма, която прочита от клавиатурата цяло положително число,
 * не по-голямо от 3000, и извежда на екрана представянето му в римски цифри.
 * Ако числото е извън границите, да се изведе текстът "Invalid number!".
 */

//Input handling must be separated in another file
class InvalidNumberException {
public:
    void printErrorMessage() {
        cout << "Invalid number!" << endl;
    }
};

class IntegerInputValidator {
    int mMinValue;
    int mMaxValue;
public:
    IntegerInputValidator(int minValue, int maxValue) {
        mMinValue = minValue;
        mMaxValue = maxValue;
    }

    bool isValidInput(int number) {
        return number > mMinValue && number <= mMaxValue;
    }
};

class NumberReader {
    IntegerInputValidator mInputValidator;
public:
    NumberReader(IntegerInputValidator inputValidator)
            : mInputValidator(inputValidator) {}

    int readNumberFromStandardInput() {
        int number;
        cin >> number;
        if (!mInputValidator.isValidInput(number)) {
            throw InvalidNumberException();
        }
        return number;
    }
};
//Input handling must be separated in another file

//Domain layer: used "Chain of responsibility design pattern" (can be done easily with switch statement, but I wanted
//to test my C++ OOP skills)
class ConversionFailedException {
};

class RomanianNumeral {
    string mSymbol;
    int mDecimalValue;
    RomanianNumeral *mSuccessor;
public:
    RomanianNumeral(string symbol, int decimalValue) {
        mSymbol = symbol;
        mDecimalValue = decimalValue;
        mSuccessor = 0;
    }

    void setSuccessor(RomanianNumeral *successor) {
        mSuccessor = successor;
    }

    string startTransformChain(int &decimalNumber) {
        if (decimalNumber >= mDecimalValue) {
            decimalNumber -= mDecimalValue;
            return mSymbol;
        } else if (mSuccessor) {
            return mSuccessor->startTransformChain(decimalNumber);
        }
        throw ConversionFailedException();
    }
};

class SupportedRomanianNumerals {
    static const int SUPPORTED_VALUES_LENGTH = 13;

    RomanianNumeral **mSupportedNumerals;
public:
    SupportedRomanianNumerals() {
        const int VALUES[] =
                {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};
        const string NUMERALS[] =
                {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};

        mSupportedNumerals = new RomanianNumeral *[SUPPORTED_VALUES_LENGTH];

        //I know I should not use loops, but if this initialization without loops
        //would be overkill
        for (int i = 0; i < SUPPORTED_VALUES_LENGTH; ++i) {
            RomanianNumeral *currentNumeral = new RomanianNumeral(NUMERALS[i], VALUES[i]);
            if (i > 0) {
                currentNumeral->setSuccessor(mSupportedNumerals[i - 1]);
            }
            mSupportedNumerals[i] = currentNumeral;
        }
    }

    const RomanianNumeral getLargestNumeral() {
        return *mSupportedNumerals[SUPPORTED_VALUES_LENGTH - 1];
    }

    ~SupportedRomanianNumerals() {
        for (int i = 0; i < SUPPORTED_VALUES_LENGTH; ++i) {
            delete mSupportedNumerals[i];
        }
        delete[] mSupportedNumerals;
    }
};

class RomanianNumber {
    string mRomanianNumber;

    void initRomanianNumber(RomanianNumeral largerSupportedNumeral, int decimalNumber) {
        try {
            //!NOTE: RomanianNumeral#startTransformChain(decimalNumber) has side effect:
            //reduces the decimalNumber by romanian numeral value if the romanian value is larger than the decimalNumber
            //WARN: THIS IS TERRIBLE DESIGN PRACTISE but not letting me use loops isn't cool, too :/
            mRomanianNumber += largerSupportedNumeral.startTransformChain(decimalNumber);
            if (decimalNumber != 0) {
                initRomanianNumber(largerSupportedNumeral, decimalNumber);
            }
        } catch (ConversionFailedException ex) {
            cout << "Something terrible happened :/" << endl;
        }
    }

public:
    RomanianNumber(int decimalNumber) {
        mRomanianNumber = "";
        SupportedRomanianNumerals romanianNumerals = SupportedRomanianNumerals();
        initRomanianNumber(romanianNumerals.getLargestNumeral(), decimalNumber);
    }

    void print() {
        cout << mRomanianNumber << endl;
    }
};
//Domain layer

int main() {
    IntegerInputValidator inputValidator =
            IntegerInputValidator(NUMBER_MIN_VALUE, NUMBER_MAX_VALUE);
    NumberReader numberReader = NumberReader(inputValidator);

    try {
        int number = numberReader.readNumberFromStandardInput();
        RomanianNumber romanianNumber = RomanianNumber(number);
        romanianNumber.print();
    } catch (InvalidNumberException ex) {
        ex.printErrorMessage();
    }

    return 0;
}