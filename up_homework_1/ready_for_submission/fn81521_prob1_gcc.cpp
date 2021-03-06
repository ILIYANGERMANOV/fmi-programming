/**
 *  
 * Solution to homework task 
 * Introduction to programming course 
 * Faculty of Mathematics and Informatics of Sofia University 
 * Winter semester 2016/2017 
 * 
 * @author Iliyan Germanov 
 * @idnumber 81521 
 * @task 1 
 * @compiler GCC 
 * 
 */
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

class RomananNumeral {
    string mSymbol;
    int mDecimalValue;
    RomananNumeral *mSuccessor;
public:
    RomananNumeral(string symbol, int decimalValue) {
        mSymbol = symbol;
        mDecimalValue = decimalValue;
        mSuccessor = 0;
    }

    void setSuccessor(RomananNumeral *successor) {
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

class SupportedRomanNumerals {
    static const int SUPPORTED_VALUES_LENGTH = 13;

    RomananNumeral **mSupportedNumerals;

    void initSupportedNumeralsRecursively(const int *values, const string *numerals, int index) {
        if (index >= SUPPORTED_VALUES_LENGTH)
            return;
        RomananNumeral *currentNumeral = new RomananNumeral(numerals[index], values[index]);
        if (index > 0) {
            currentNumeral->setSuccessor(mSupportedNumerals[index - 1]);
        }
        mSupportedNumerals[index] = currentNumeral;
        initSupportedNumeralsRecursively(values, numerals, index + 1);
    }

public:
    SupportedRomanNumerals() {
        const int VALUES[] =
                {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};
        const string NUMERALS[] =
                {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};

        mSupportedNumerals = new RomananNumeral *[SUPPORTED_VALUES_LENGTH];

        initSupportedNumeralsRecursively(VALUES, NUMERALS, 0);
    }

    const RomananNumeral getLargestNumeral() {
        return *mSupportedNumerals[SUPPORTED_VALUES_LENGTH - 1];
    }

    ~SupportedRomanNumerals() {
        for (int i = 0; i < SUPPORTED_VALUES_LENGTH; ++i) {
            delete mSupportedNumerals[i];
        }
        delete[] mSupportedNumerals;
    }
};

class RomanNumber {
    string mRomanNumber;

    void initRomanNumber(RomananNumeral largestSupportedNumeral, int decimalNumber) {
        try {
            //!NOTE: RomanNumeral#startTransformChain(decimalNumber) has side effect:
            //reduces the decimalNumber by roman numeral value if the roman value is larger than the decimalNumber
            //WARN: THIS IS TERRIBLE DESIGN PRACTISE but not letting me use loops isn't cool, too :/
            mRomanNumber += largestSupportedNumeral.startTransformChain(decimalNumber);
            if (decimalNumber != 0) {
                initRomanNumber(largestSupportedNumeral, decimalNumber);
            }
        } catch (ConversionFailedException ex) {
            cout << "Something terrible happened :/" << endl;
        }
    }

public:
    RomanNumber(int decimalNumber) {
        mRomanNumber = "";
        SupportedRomanNumerals romanNumerals = SupportedRomanNumerals();
        initRomanNumber(romanNumerals.getLargestNumeral(), decimalNumber);
    }

    void print() {
        cout << mRomanNumber << endl;
    }
};
//Domain layer

int main() {
    IntegerInputValidator inputValidator =
            IntegerInputValidator(NUMBER_MIN_VALUE, NUMBER_MAX_VALUE);
    NumberReader numberReader = NumberReader(inputValidator);

    try {
        int number = numberReader.readNumberFromStandardInput();
        RomanNumber romanNumber = RomanNumber(number);
        romanNumber.print();
    } catch (InvalidNumberException ex) {
        ex.printErrorMessage();
    }

    return 0;
}