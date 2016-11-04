/**
 * WARNING: Java and Android conventions used!
 */
#include <iostream>

/*
 * Да се напише програма, която по дадени координати на цар и друга фигура
върху шахматна дъска определя дали царят е в шах от съответната фигура.


Координатите на шахматната дъска са във вида - “X Y”, където:
X е малка латинска буква от ‘a’ до ‘h’, означаваща поредна колона на шахматната дъска, отляво надясно
Y е цифра от 1 до 8, означаващо пореден ред на шахматната дъска, отдолу нагоре


Фигурата може да бъде: дама, офицер, кон или топ. Символите, съответстващи на валидните фигури са:
‘Q’ — дама (Queen)
‘B’ — офицер (Bishop)
‘N’ — кон (kNight)
‘R’ — топ (Rook)


(Удобно описание на шахматната нотация можете да намерите тук.)


От клавиатурата последователно се въвеждат:
Символ за тип на атакуващата фигура
Координатите на атакуващата фигура
Координатите на царя


Ако царят е в шах, програмата извежда надпис "Yes" на конзолния ред, а в противен случай извежда "No".

 */

using namespace std;

class BadInputException {
public:
    void printError() {
        cout << "Bad input" << endl;
    }
};


class Matrix {
    int mMatrix[8][8];
public:
    Matrix() {

    }

    void setAttackedPosition(int x, int y) {

    }
};

class Figure {
protected:
    int mX;
    int mY;
public:
    Figure() {
        mX = -1;
        mY = -1;
    }

    Figure(int x, int y) {
        mX = x;
        mY = y;
    }

    void setX(int x) {
        mX = x;
    }

    void setY(int y) {
        mY = y;
    }
};

class Attacker : public Figure {
public:
    Attacker() : Figure() {}

    Attacker(int x, int y) : Figure(x, y) {}

    virtual void attack(Matrix) = 0;
};

class Queen : public Attacker {
public:
    Queen() : Attacker() {}

    Queen(int x, int y) : Attacker(x, y) {}

    void attack(Matrix matrix) {
        cout << "Queen attack" << endl;
    }
};

class Bishop : public Attacker {
public:
    Bishop() : Attacker() {}

    Bishop(int x, int y) : Attacker(x, y) {}

    void attack(Matrix matrix) {
        cout << "Bishop attack" << endl;
    }
};

class Knight : public Attacker {
public:
    Knight() : Attacker() {}


    Knight(int x, int y) : Attacker(x, y) {}

    void attack(Matrix matrix) {
        cout << "Knight attack" << endl;
    }
};

class Rook : public Attacker {
public:
    Rook() : Attacker() {}

    Rook(int x, int y) : Attacker(x, y) {}

    void attack(Matrix matrix) {
        cout << "Rook attack" << endl;
    }
};

class ChessBoard {
    Attacker *mAttacker;
    Figure mKing;

    void initAttackerType() {
        char attackerSymbol;
        cin >> attackerSymbol;
        switch (attackerSymbol) {
            case 'Q':
                mAttacker = new Queen();
                break;
            case 'B':
                mAttacker = new Bishop();
                break;
            case 'N':
                mAttacker = new Knight();
                break;
            case 'R':
                mAttacker = new Rook();
                break;
            default:
                throw BadInputException();
        }
    }

    int readX() {
        int position;
        cin >> position;
        return position;
    }

    int readY() {
        char symbol;
        cin >> symbol;
        int position = (int) (symbol - 'a');
        if(position < 0 || position > 8) throw BadInputException();
        return position;
    }

    void initAttackerPosition() {
        mAttacker->setX(readX());
        mAttacker->setX(readY());
    }

    void initKingPosition() {
        mKing.setX(readX());
        mKing.setY(readY());
    }

public:
    void initBoard() {
        initAttackerType();
        initAttackerPosition();
        initKingPosition();
    }

    ~ChessBoard() {
        delete mAttacker;
    }
};


int main() {
    try {
        ChessBoard chessBoard = ChessBoard();
        chessBoard.initBoard();
    } catch (BadInputException ex) {
        ex.printError();
    }
    return 0;
}