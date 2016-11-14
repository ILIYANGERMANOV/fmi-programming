#include <iostream>
#include <cmath>

#define SQR(x) ((x)*(x))

using namespace std;

class Point {
    double mX;
    double mY;
public:
    Point() {
        mX = -1;
        mY = -1;
    }

    Point(double x, double y) {
        mX = x;
        mY = y;
    }

    double calculateDistance(Point otherPoint) {
        return sqrt(SQR(mX - otherPoint.getX()) + SQR(mY - otherPoint.getY()));
    }

    double getX() {
        return mX;
    }

    double getY() {
        return mY;
    }
};

enum Position {
    IN_CIRCLE,
    ON_BORDER,
    OUTSIDE_CIRCLE
};

class Circle {
    Point mCenter;
    double mRadius;
public:
    Circle(Point center, double radius) {
        mCenter = center;
        mRadius = radius;
    }

    Position determinePointPosition(Point point) {
        double distance = mCenter.calculateDistance(point);
        if (distance < mRadius) {
            return IN_CIRCLE;
        } else if (distance == mRadius) {
            return ON_BORDER;
        } else {
            return OUTSIDE_CIRCLE;
        }
    }
};

class Darts {
    Circle mWhiteArea;
    Circle mGreenArea;
    Circle mRedArea;
public:
    Darts() : mWhiteArea(Circle(Point(0, 0), 1)),
              mGreenArea(Circle(Point(0, 0), 3)),
              mRedArea(Circle(Point(0, 0), 8)) {}

    void printScore(Point targetPoint) {
        int score = 0;
        if (isPositionInCircle(mWhiteArea.determinePointPosition(targetPoint))) {
            score = 60;
        } else if (isPositionInCircle(mGreenArea.determinePointPosition(targetPoint))) {
            score = 20;
        } else if (isPositionInCircle(mRedArea.determinePointPosition(targetPoint))) {
            score = 10;
        }
        cout << score << endl;
    }

private:
    bool isPositionInCircle(Position position) {
        return position == IN_CIRCLE;
    }
};

int main() {
    double targetX, targetY;
    double deviationX, deviationY;
    cin >> targetX;
    cin >> targetY;
    cin >> deviationX;
    cin >> deviationY;
    Darts darts = Darts();
    darts.printScore(Point(targetX + deviationX, targetY + deviationY));
    return 0;
}