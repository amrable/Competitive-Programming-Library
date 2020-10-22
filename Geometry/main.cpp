#include <bits/stdc++.h>

using namespace std;
class Point;
class CoordinateVector;
class Line;
class Point {
    public:
        const double EPS = 1e-9;
        double x, y;

        Point(double a ,double b);

        int compareTo(Point p);

        double dist(Point p);

        double sq(double x);

        Point rotate(double angle);

        Point rotate(double angle , Point p);

        Point translate(CoordinateVector v) ;

        Point reflectionPoint(Line l); 	//reflection point of p on line l

        bool between(Point p, Point q);

        //returns true if it is on the line defined by a and b
        bool onLine(Point a, Point b) ;
        
        bool onSegment(Point a, Point b) ;

        //returns true if it is on the ray whose start point is a and passes through b
        bool onRay(Point a, Point b) ;

        // returns true if it is on the left side of Line pq
        // add EPS to LHS if on-line points are accepted
        bool ccw(Point p, Point q, Point r);

        bool collinear(Point p, Point q, Point r);

        // angle AOB 
        double angle(Point a, Point o, Point b);
        
        double distToLine(Point p, Point a, Point b); //distance between point p and a line defined by points a, b (a != b)
            
        // Another way: find closest point and calculate the distance between it and p

        double distToLineSegment(Point p, Point a, Point b);
        // Another way: find closest point and calculate the distance between it and p

};

class CoordinateVector{
    public:
        double x, y;

        CoordinateVector(double a, double b);

        CoordinateVector(Point a, Point b);

        CoordinateVector scale(double s);

        double dot(CoordinateVector v);

        double cross(CoordinateVector v);

        double norm2();

        CoordinateVector reverse();

        CoordinateVector normalize();
};

class Line{
    public:
        const double INF = 1e9 , EPS = 1e-9;
        double a, b, c;

        Line(Point p, Point q);

        Line(Point p, double m);

        bool parallel(Line l);

        bool same(Line l);

        Point intersect(Line l);

        Point closest_point(Point p);
};

Point::Point(double a ,double b){
    x = a; 
    y = b;
}

int Point::compareTo(Point p){
    if(abs(x - p.x) > EPS)return x>p.x ? 1 : -1;
    if(abs(y - p.y) > EPS)return y>p.y ? 1 : -1;
    return 0;
}

double Point::dist(Point p){
    return sqrt( sq(x-p.x) + sq(y - p.y) );
} 

double Point::sq(double x){ return x * x; }

Point Point::rotate(double angle){
    double c = cos(angle) , s = sin(angle);
    return Point( x * c - y * s , x * s + y * c );
}

Point Point::rotate(double angle , Point p){
    CoordinateVector v(p, Point(0, 0));
    return translate(v).rotate(angle).translate(v.reverse());
}

Point Point::translate(CoordinateVector v) { return Point(x + v.x , y + v.y); }

Point Point::reflectionPoint(Line l){ 	//reflection point of p on line l
    Point p1(this->x, this->y);
    Point p2 = l.closest_point(p1);
    CoordinateVector v(p1, p2);
    return this->translate(v).translate(v);
}

bool Point::between(Point p, Point q){
    return x < max(p.x, q.x) + EPS && x + EPS > min(p.x, q.x)
        && y < max(p.y, q.y) + EPS && y + EPS > min(p.y, q.y);
}

//returns true if it is on the line defined by a and b
bool Point::onLine(Point a, Point b) {
    if(a.compareTo(b) == 0) return compareTo(a) == 0;
    Point p(this->x, this->y);
    return abs(CoordinateVector(a, b).cross( CoordinateVector(a, p) )) < EPS;
}

bool Point::onSegment(Point a, Point b) {
    if(a.compareTo(b) == 0) return compareTo(a) == 0;
    return onRay(a, b) && onRay(b, a);
}

//returns true if it is on the ray whose start point is a and passes through b
bool Point::onRay(Point a, Point b) {
    if(a.compareTo(b) == 0) return compareTo(a) == 0;
    Point p(this->x, this->y);

    CoordinateVector x(a, b);
    CoordinateVector y(a, p);
    CoordinateVector n = x.normalize();
    CoordinateVector m = y.normalize();

    return n.x == m.x && n.y == m.y;	//implement equals()
}

// returns true if it is on the left side of Line pq
// add EPS to LHS if on-line points are accepted
bool Point::ccw(Point p, Point q, Point r) {
    return CoordinateVector(p, q).cross( CoordinateVector(p, r)) > 0;
}
bool Point::collinear(Point p, Point q, Point r) {
    return abs( CoordinateVector(p, q).cross( CoordinateVector(p, r))) < EPS;
}
double Point::angle(Point a, Point o, Point b){  // angle AOB 
    CoordinateVector oa(o, a);
    CoordinateVector ob(o, b);
    return acos(oa.dot(ob) / sqrt(oa.norm2() * ob.norm2()));
}

double Point::distToLine(Point p, Point a, Point b){ //distance between point p and a line defined by points a, b (a != b)
    if(a.compareTo(b) == 0) return p.dist(a);
    // formula: c = a + u * ab
    CoordinateVector ap(a, p);
    CoordinateVector ab(a, b);
    double u = ap.dot(ab) / ab.norm2();
    Point c = a.translate(ab.scale(u)); 
    return p.dist(c);
}
// Another way: find closest point and calculate the distance between it and p

double Point::distToLineSegment(Point p, Point a, Point b){ 
    CoordinateVector ap(a, p);
    CoordinateVector ab(a, b);
    double u = ap.dot(ab) / ab.norm2();
    if (u < 0.0) return p.dist(a);
    if (u > 1.0) return p.dist(b);        
    return distToLine(p, a, b); 
}
// Another way: find closest point and calculate the distance between it and p



CoordinateVector::CoordinateVector(double a, double b) {
    x = a, y = b;
}

CoordinateVector::CoordinateVector(Point a, Point b) {
    x = b.x - a.x, y = b.y - a.y;
}

CoordinateVector CoordinateVector::scale(double s) {
    return CoordinateVector( x * s, y * s);
}

double CoordinateVector::dot(CoordinateVector v) { return (x * v.x + y * v.y); }

double CoordinateVector::cross(CoordinateVector v) { return x * v.y - y * v.x; }

double CoordinateVector::norm2() { return x * x + y * y; }

CoordinateVector CoordinateVector::reverse() { return CoordinateVector(-x, -y); }

CoordinateVector CoordinateVector::normalize() { 
    double d = sqrt(norm2());
    return scale(1 / d);
}

Line::Line(Point p, Point q){
    if(abs(p.x - q.x) < EPS) {	a = 1; b = 0; c = -p.x;	}
    else
    {
        a = (p.y - q.y) / (q.x - p.x);
        b = 1.0;
        c = -(a * p.x + p.y);
    }         
}
Line::Line(Point p, double m) { 
    a = -m; b = 1; c =  -(a * p.x + p.y); 
} 
bool Line::parallel(Line l) { return abs(a - l.a) < EPS && abs(b - l.b) < EPS; }
	
bool Line::same(Line l) { return parallel(l) && abs(c - l.c) < EPS; }
	
Point Line::intersect(Line l){
    // CHECK FOR NOT BEING PARALLEL BEFORE CALLING THIS FUNCTION
    // if(parallel(l))
    //     return NULL;
    double x = (b * l.c - c * l.b) / (a * l.b - b * l.a);
    double y;
    if(abs(b) < EPS)
            y = -l.a * x - l.c;
    else
        y = -a * x - c;
    
    return Point(x, y);
}
	
Point Line::closest_point(Point p)
{
    if(abs(b) < EPS) return Point(-c, p.y);
    if(abs(a) < EPS) return Point(p.x, -c);
    return intersect(Line(p, 1 / a));
}
	


	
int main(){
    // Point p1(1,0);
    // Point p2 = p1.rotate(-3.14/2);
    // cout<<p1.x<<" "<<p1.y<<endl;
    // cout<<p2.x<<" "<<p2.y<<endl;
    // CoordinateVector cv(1 , 1);
    // CoordinateVector cv2 = cv.scale(3);
    // cout<<cv.x<<" "<<cv.y<<endl;
    // cout<<cv2.x<<" "<<cv2.y;
}