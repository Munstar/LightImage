#include <iostream>
#include "modules/core/include/core.hpp"

using namespace std;
using namespace li;

int main() {

    Point2D32S p1 = Point2D32S();
    Point2D32S p2 = Point2D32S(2,7);
    Point2D32S p3 = Point2D32S();

    p1.x=3;
    p1.y=4;

    p3 = p1 + p2;



    cout << "p3("<<p3.x<<","<<p3.y<<")"<< endl;
    return 0;
}