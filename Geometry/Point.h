#include <bits/stdc++.h>
// #include "Vector.h"

using namespace std;

class Point {
    public:
        const double EPS = 1e-9;
        double x, y;

        Point(double a ,double b){
            x = a; 
            y = b;
        }

        int compareTo(Point p){
            if(abs(x - p.x) > EPS)return x>p.x ? 1 : -1;
            if(abs(y - p.y) > EPS)return y>p.y ? 1 : -1;
            return 0;
        }

        double dist(Point p){
            return sqrt( sq(x-p.x) + sq(y - p.y) );
        } 

        double sq(double x){ return x * x; }

        Point rotate(double angle){
            double c = cos(angle) , s = sin(angle);
            return Point( x * c - y * s , x * s + y * c );
        }

        // Rotate around point P : TBD
        // Point rotate(double angle , Point P){

        // }

        bool between(Point p, Point q){
            return x < max(p.x, q.x) + EPS && x + EPS > min(p.x, q.x)
				&& y < max(p.y, q.y) + EPS && y + EPS > min(p.y, q.y);
        }

};