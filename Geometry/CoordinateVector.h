#include <bits/stdc++.h>

using namespace std;

class CoordinateVector{
    public:
        double x, y;

        CoordinateVector(double a, double b) {
            x = a, y = b;
        }

        CoordinateVector(Point a, Point b) {
            x = b.x - a.x, y = b.y - a.y;
        }

        CoordinateVector scale(double s) {
            return CoordinateVector( x * s, y * s);
        }

        double dot(CoordinateVector v) { return (x * v.x + y * v.y); }

        double cross(CoordinateVector v) { return x * v.y - y * v.x; }

        double norm2() { return x * x + y * y; }

        CoordinateVector reverse() { return CoordinateVector(-x, -y); }

        CoordinateVector normalize() { 
            double d = sqrt(norm2());
            return scale(1 / d);
        }
};