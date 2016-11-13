/**
*  
* Solution to homework task 
* Introduction to programming course 
* Faculty of Mathematics and Informatics of Sofia University 
* Winter semester 2016/2017 
* 
* @author Iliyan Germanov 
* @idnumber 81521 
* @task 4 
* @compiler GCC 
* 
*/
/**
 * WARNING: Java and Android conventions used!
 */

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

#include <iostream>
#include <cmath>

using namespace std;

#define CHESS_SIZE 8

class BadInputException {
public:
    void printError() {
        cout << "Bad input" << endl;
    }
};

class AttackStrategy {
protected:
    int mAttackerX;
    int mAttackerY;
public:
    AttackStrategy(int attackerX, int attackerY) :
            mAttackerX(attackerX), mAttackerY(attackerY) {}

    virtual bool isPositionAffected(int targetX, int targetY) = 0;
};

class HorizontalAttackStrategy : public AttackStrategy {
public:
    HorizontalAttackStrategy(int attackerX, int attackerY) : AttackStrategy(attackerX, attackerY) {}

    bool isPositionAffected(int targetX, int targetY) {
        return mAttackerX == targetX || mAttackerY == targetY;
    }
};


class DiagonalAttackStrategy : public AttackStrategy {
public:
    DiagonalAttackStrategy(int attackerX, int attackerY) : AttackStrategy(attackerX, attackerY) {}

    bool isPositionAffected(int targetX, int targetY) {
        return abs(mAttackerX - targetX) == abs(mAttackerY - targetY);
    }
};

class Figure {
protected:
    int mX;
    int mY;
public:
    int getX() {
        return mX;
    }

    void setX(int x) {
        mX = x;
    }

    int getY() {
        return mY;
    }

    void setY(int y) {
        mY = y;
    }
};

class Attacker : public Figure {
public:
    virtual bool isTargetAttacked(int targetX, int targetY) = 0;
};

class Queen : public Attacker {
public:
    bool isTargetAttacked(int targetX, int targetY) {
        return DiagonalAttackStrategy(mX, mY).isPositionAffected(targetX, targetY)
               || HorizontalAttackStrategy(mX, mY).isPositionAffected(targetX, targetY);
    }
};

class Bishop : public Attacker {
public:
    bool isTargetAttacked(int targetX, int targetY) {
        return DiagonalAttackStrategy(mX, mY).isPositionAffected(targetX, targetY);
    }
};

class Knight : public Attacker {
public:
    bool isTargetAttacked(int targetX, int targetY) {
        int xDelta = abs(mX - targetX);
        int yDelta = abs(mY - targetY);
        return (xDelta == 2 && yDelta == 1)
               || (xDelta == 1 && yDelta == 2);
    }
};

class Rook : public Attacker {
public:
    bool isTargetAttacked(int targetX, int targetY) {
        return HorizontalAttackStrategy(mX, mY).isPositionAffected(targetX, targetY);
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

    void initAttackerPosition() {
        mAttacker->setX(readX());
        mAttacker->setY(readY());
    }

    void initKingPosition() {
        mKing.setX(readX());
        mKing.setY(readY());
    }

    int readX() {
        char symbol;
        cin >> symbol;
        int position = (int) (symbol - 'a');
        if (isInvalidAxisPosition(position)) throw BadInputException();
        return position;
    }

    int readY() {
        int position;
        cin >> position;
        if (isInvalidAxisPosition(position)) throw BadInputException();
        return position;
    }

    bool isInvalidAxisPosition(int position) {
        return position < 0 || position > CHESS_SIZE;
    }

public:
    void initBoard() {
        initAttackerType();
        initAttackerPosition();
        initKingPosition();
    }

    bool isKingAttacked() {
        return mAttacker->isTargetAttacked(mKing.getX(), mKing.getY());
    }

    ~ChessBoard() {
        delete mAttacker;
    }
};


int main() {
    try {
        ChessBoard chessBoard = ChessBoard();
        chessBoard.initBoard();
        if (chessBoard.isKingAttacked()) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    } catch (BadInputException ex) {
        ex.printError();
    }
    return 0;
}