#include <iostream>
#include <algorithm>

/*
* Дадена е декартова координатна система. Всеки правоъгълник в нея може да се определи с четири цели числа:
 * координатите на долния си ляв ъгъл, височината и ширината си. Да се напише програма,
 * която прочита от клавиатурата данните за два правоъгълника
 * (на два отделни реда, като числата на всеки ред са разделени с интервал) и извежда на екрана лицето на общата им част.
 * Ако правоъгълниците нямат обща част, приемаме лицето за нула.
 */

using namespace std;

class Point {
    int mX;
    int mY;
public:
    int getX() const {
        return mX;
    }

    void setX(int mX) {
        Point::mX = mX;
    }

    int getY() const {
        return mY;
    }

    void setY(int mY) {
        Point::mY = mY;
    }
};

class Rectangle {
    Point mBottomLeftPoint;
    Point mTopRightPoint;

    void readRectangleFromStdIn() {
        int x, y, width, height;
        cin >> x;
        cin >> y;
        cin >> height;
        cin >> width;
        mBottomLeftPoint.setX(x);
        mBottomLeftPoint.setY(y);

        mTopRightPoint.setY(y + height);
        mTopRightPoint.setX(x + width);
    }

public:
    Rectangle()
            : mBottomLeftPoint(Point()), mTopRightPoint(Point()) {
        readRectangleFromStdIn();
    }

    Point getBottomLeft() {
        return mBottomLeftPoint;
    }

    Point getTopRight() {
        return mTopRightPoint;
    }

};

int calculateOverlappingArea(Rectangle rect1, Rectangle rect2) {
    int xIntersection = min(rect1.getTopRight().getX(), rect2.getTopRight().getX())
             - max(rect1.getBottomLeft().getX(), rect2.getBottomLeft().getX());
    int yIntersection = min(rect1.getTopRight().getY(), rect2.getTopRight().getY())
             - max(rect1.getBottomLeft().getY(), rect2.getBottomLeft().getY());
    return xIntersection * yIntersection;
}

int main() {
    Rectangle rectangle1 = Rectangle();
    Rectangle rectangle2 = Rectangle();
    cout << calculateOverlappingArea(rectangle1, rectangle2) << endl;
    return 0;
}