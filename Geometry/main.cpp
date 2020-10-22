#include <bits/stdc++.h>
#define PI 3.141592653589793238

using namespace std;
class Point;
class CoordinateVector;
class Line;
class Polygon;
class Rectangle;
class LineSegment;

class Point {
    public:
        static const double EPS = 1e-9;
        double x, y;

        Point(double a ,double b);
        Point();

        int compareTo(Point p);

        double dist(Point p);

        static double sq(double x);

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
        static bool ccw(Point p, Point q, Point r);

        static bool collinear(Point p, Point q, Point r);

        // angle AOB 
        static double angle(Point a, Point o, Point b);
        
        static double distToLine(Point p, Point a, Point b); //distance between point p and a line defined by points a, b (a != b)
            
        // Another way: find closest point and calculate the distance between it and p

        static double distToLineSegment(Point p, Point a, Point b);
        // Another way: find closest point and calculate the distance between it and p

        //comparator
        static bool comp(Point& a , Point&b){
            return a.compareTo(b)<1;
        }
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
        static const double INF = 1e9 , EPS = 1e-9;
        double a, b, c;

        Line(Point p, Point q);

        Line(Point p, double m);

        bool parallel(Line l);

        bool same(Line l);

        Point intersect(Line l);

        Point closest_point(Point p);
};

class Polygon{
    // Cases to handle: collinear points, polygons with n < 3

	static const double EPS = 1e-9;
	
	vector<Point> g; 			//first point = last point, counter-clockwise representation
	
	Polygon( vector<Point> o);

    double perimeter();
    double area();
    bool isConvex();
    bool inside(Point p);
    Polygon cutPolygon(Point a, Point b);
    static Polygon convexHull(vector<Point> points);
    Point centroid();
};

class Rectangle {

	static const double EPS = 1e-9;
	
	Point ll, ur;

	Rectangle(Point a, Point b);

	double area();
    
	bool contains(Point p);

	Rectangle intersect(Rectangle r);

};
class LineSegment {
	Point p, q;
	LineSegment(Point a, Point b);
	bool intersect(LineSegment ls);
};

Point::Point(double a ,double b){
    x = a; 
    y = b;
}
Point::Point(){
    x = 0; 
    y = 0;
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

Polygon::Polygon( vector<Point> o) { g = o; }

double Polygon::perimeter() {
    double sum = 0.0;
    for(int i = 0; i < g.size() - 1; ++i)
        sum += g[i].dist(g[i+1]);
    return sum;
}
double Polygon::area(){ 		//clockwise/anti-clockwise check, for convex/concave polygons
    double ar = 0.0;
    for(int i = 0; i < g.size() - 1; ++i)
        ar += g[i].x * g[i+1].y - g[i].y * g[i+1].x;
    return abs(ar) / 2.0;			//negative value in case of clockwise
}
bool Polygon::isConvex(){
    if(g.size() <= 3) // point or line
        return false;
    bool ccw = Point::ccw(g[g.size() - 2], g[0], g[1]);		//edit ccw check to accept collinear points
    for(int i = 1; i < g.size() - 1; ++i)
        if(Point::ccw(g[i-1], g[i], g[i+1]) != ccw)
            return false;
    return true;
}
bool Polygon::inside(Point p){	//for convex/concave polygons - winding number algorithm 
    double sum = 0.0;
    for(int i = 0; i < g.size() - 1; ++i)
    {
        double angle = Point::angle(g[i], p, g[i+1]);
        if((abs(angle) < EPS || abs(angle - PI) < EPS) && p.between(g[i], g[i+1]))
            return true;
        if(Point::ccw(p, g[i], g[i+1]))
            sum += angle;
        else
            sum -= angle;
    }

    return abs(2 * PI - abs(sum)) < EPS;		//abs makes it work for clockwise
}
/*
    * Another way if the polygon is convex
    * 1. Triangulate the poylgon through p
    * 2. Check if sum areas == poygon area
    * 3. Handle empty polygon
    */
Polygon Polygon::cutPolygon(Point a, Point b)	//returns the left part of the polygon, swap a & b for the right part
{
    vector<Point> ans((g.size()<<1)) ;
    Line l(a, b);
    CoordinateVector v(a, b);
    
    int size = 0;
    for(int i = 0; i < g.size(); ++i){
        double left1 = v.cross(CoordinateVector(a, g[i]));
        double left2 = i == g.size() - 1 ? 0 : v.cross( CoordinateVector(a, g[i+1]));

        if(left1 + EPS > 0)	
            ans[size++] = g[i];
        if(left1 * left2 + EPS < 0)
            ans[size++] = l.intersect(Line(g[i], g[i+1]));
    }
    
    if(size != 0 && ans[0].x != ans[size-1].x &&ans[0].y != ans[size-1].y )	//necessary in case g[0] is not in the new polygon
        ans[size++] = ans[0];
    
    vector<Point> ret;
    for(int i = 0 ; i<size;i++){
        ret.push_back(ans[i]);
    }
    return Polygon(ret);
}

Polygon Polygon::convexHull(vector<Point> points){	//all points are unique, remove duplicates, edit ccw to accept collinear points
    int n = points.size();
    sort(points.begin(),points.end() , Point::comp);
    vector<Point> ans((n<<1)) ;
    int size = 0, start = 0;

    for(int i = 0; i < n; i++){
        Point p = points[i];
        while(size - start >= 2 && !Point::ccw(ans[size-2], ans[size-1], p))	--size;
        ans[size++] = p;
    }
    start = --size;

    for(int i = n-1 ; i >= 0 ; i--)
    {
        Point p = points[i];
        while(size - start >= 2 && !Point::ccw(ans[size-2], ans[size-1], p))	--size;
        ans[size++] = p; 
    }
    //			if(size < 0) size = 0			for empty set of points
    vector<Point> ret;
    for(int i = 0 ; i<size;i++){
        ret.push_back(ans[i]);
    }
    return Polygon(ret);
    // return new Polygon(Arrays.copyOf(ans, size));			
}
Point Polygon::centroid(){		//center of mass
    double cx = 0.0, cy = 0.0;
    for(int i = 0; i < g.size() - 1; i++)
    {
        double x1 = g[i].x, y1 = g[i].y;
        double x2 = g[i+1].x, y2 = g[i+1].y;

        double f = x1 * y2 - x2 * y1;
        cx += (x1 + x2) * f;
        cy += (y1 + y2) * f;
    }
    double area = this->area();		//remove abs
    cx /= 6.0 * area;
    cy /= 6.0 * area;
    return Point(cx, cy);
}



Rectangle::Rectangle(Point a, Point b) { ll = a; ur = b; }

double Rectangle::area() { return (ur.x - ll.x) * (ur.y - ll.y); }

bool Rectangle::contains(Point p){
    return p.x <= ur.x + EPS && p.x + EPS >= ll.x && p.y <= ur.y + EPS && p.y + EPS >= ll.y;
}

Rectangle Rectangle::intersect(Rectangle r){
    Point ll(max(this->ll.x, r.ll.x), max(this->ll.y, r.ll.y));
    Point ur(min(this->ur.x, r.ur.x), min(this->ur.y, r.ur.y));
    if(abs(ur.x - ll.x) > EPS && abs(ur.y - ll.y) > EPS && this->contains(ll) && this->contains(ur) && r.contains(ll) && r.contains(ur))
        return Rectangle(ll, ur);
    // THIS SHOULD BE RETURN NULL !! TAKE THIS FUNCTION TO YOUR MAIN
    // return NULL;
    return Rectangle(ll, ur);;
}
	
LineSegment::LineSegment(Point a, Point b) { p = a; q = b; }
	

bool LineSegment::intersect(LineSegment ls){
    Line l1(p, q);
    Line l2(ls.p, ls.q);
    if(l1.parallel(l2)){
        if(l1.same(l2))
            return p.between(ls.p, ls.q) || q.between(ls.p, ls.q) || ls.p.between(p, q) || ls.q.between(p, q);
        return false;
    }
    Point c = l1.intersect(l2);
    return c.between(p, q) && c.between(ls.p, ls.q);
}

class Geometry {

	static const double INF = 1e9, EPS = 1e-9;		// better use 1e-11 for large coordinates and 1e-15 if infinite precision is required
	
	static double degToRad(double d) { return d * PI / 180.0; }

	static double radToDeg(double r) { return r * 180.0 / PI; }
	
	static double round(double x) {	return round(x * 1000) / 1000.0; }  //use it because of -0.000
	
	//Volume of Tetrahedron WXYZ, sides order: WX, WY, WZ, XY, XZ, YZ
	static double vTetra(vector<double> sides)
	{
		vector<double> coff(3);
		for(int i = 0; i < 3; i++)
			coff[i] = sides[(i+1)%3] * sides[(i+1)%3] + sides[(i+2)%3] * sides[(i+2)%3] - sides[5 - i] * sides[5 - i];

		double root = 4 * sides[0] * sides[0] * sides[1] * sides[1] * sides[2] * sides[2];
		for(int i = 0; i < 3; i++)
			root -= coff[i] * coff[i] * sides[i] * sides[i];
		root += coff[0] * coff[1] * coff[2];

		return 1 / 12.0 * sqrt(root);
	}
};

int main(){
    vector<Point>v(5);
    v[0].x = 0, v[0].y = 5; 
    v[1].x = 3, v[1].y = 4; 
    v[2].x = 3, v[2].y = 3; 
    v[3].x = 2, v[3].y = 2; 
    v[4].x = 3, v[4].y = 5; 
    sort(v.begin(),v.end() , Point::comp);
    
    for(int i = 0 ; i< 5 ; i++){
        cout<<v[i].x<<" "<<v[i].y<<endl;
    }
}