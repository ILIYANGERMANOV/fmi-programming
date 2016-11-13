#include <iostream>
#include <cmath>

using namespace std;

#define SQR(x) ((x)*(x))

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

class YinAndYan {
    Circle mGlobalCircle;
    Circle mInnerGoodCircle;
    Circle mInnerBadCircle;
    Circle mBadCircle;
    Circle mGoodCircle;
public:
    YinAndYan()
            : mGlobalCircle(Circle(Point(0, 0), 6)),
              mGoodCircle(Circle(Point(0, 3), 3)),
              mBadCircle(Circle(Point(0, -3), 3)),
              mInnerGoodCircle(Circle(Point(0, -3), 1)),
              mInnerBadCircle(Circle(Point(0, 3), 1)) {}

    void printPointKarma(Point point) {
        //TODO: Optimize with lazy loading
        Position globalCirclePosition = mGlobalCircle.determinePointPosition(point);
        Position innerBadCirclePosition = mInnerBadCircle.determinePointPosition(point);
        Position innerGoodCirclePosition = mInnerGoodCircle.determinePointPosition(point);
        Position badCirclePosition = mBadCircle.determinePointPosition(point);
        Position goodCirclePosition = mGoodCircle.determinePointPosition(point);
        double pointX = point.getX();
        if (isNeutralPoint(pointX, globalCirclePosition, innerBadCirclePosition, innerGoodCirclePosition,
                           badCirclePosition, goodCirclePosition)) {
            printNeutral();
        } else if (isGoodPoint(pointX, globalCirclePosition, innerBadCirclePosition, innerGoodCirclePosition,
                               badCirclePosition, goodCirclePosition)) {
            printGood();
        } else {
            printEvil();
        }
    }

private:
    bool isNeutralPoint(double pointX, Position global, Position innerBad, Position innerGood,
                        Position bad, Position good) {
        return !isPositionInCircle(global)
               || isPositionOnBorder(innerBad)
               || isPositionOnBorder(innerGood)
               || (isPositionOnBorder(bad) && pointX <= 0)
               || (isPositionOnBorder(good) && pointX >= 0);
    }

    bool isGoodPoint(double pointX, Position global, Position innerBad, Position innerGood,
                     Position bad, Position good) {
        return isPositionInCircle(innerGood)
               || (isPositionInCircle(good) && isPointOutsideCircle(innerBad))
               //TODO: consider removing condition for global circle
               || (isPositionInCircle(global) && pointX < 0 &&
                   !isPositionInCircle(bad) && isPointOutsideCircle(innerBad));
    }

    bool isPositionInCircle(Position position) {
        return position == IN_CIRCLE;
    }

    bool isPositionOnBorder(Position position) {
        return position == ON_BORDER;
    }

    bool isPointOutsideCircle(Position position) {
        return position == OUTSIDE_CIRCLE;
    }

    void printNeutral() {
        cout << "Neutral" << endl;
    }

    void printGood() {
        cout << "Good" << endl;
    }

    void printEvil() {
        cout << "Evil" << endl;
    }
};

int main() {
    double x, y;
    cin >> x;
    cin >> y;
    Point targetPoint = Point(x, y);
    YinAndYan yinAndYan = YinAndYan();
    yinAndYan.printPointKarma(targetPoint);
    return 0;
}