// header 들 선언
#include <iostream>
#include <cmath>
#include <vector>
#include <limits>

using namespace std;

// PI, EPSILON 정의하기
const double PI = acos(0.0)*2.0; // 이게 C++ 버전과 상관 없이 안전하게 얻는 방법인듯...?
const double EPSILON = numeric_limits<double>::min();

class vec2;
typedef vector<vec2> polygon; // polygon의 꼭지점은 시계방향 또는 반시계방향 순서로 주어진다고 가정한다

/* 
- 2d vector용 class/struct 정의하기
- ==,<,+,-,* 가 정의되어야 함
- 2d vector의 길이를 리턴하는 함수가 정의되어야 함
- normalize된 벡터를 리턴하는 함수가 정의되어야 함
- x축의 양의 방향으로 부터 이 벡터까지 반시계 방항으로 잰 각도를 리턴하는 함수가 정의되어야 함
- 이 instance가 A라고 했을때:
    A . B (dot product) 를 리턴하는 함수가 정의되어야 함
    A x B (cross product) 를 리턴하는 함수가 정의되어야 함
    A 를 B에 project했을때 나오는 벡터를 리턴하는 함수가 정의되어야 함
*/
class vec2{
public:
    double x, y;

    vec2(double _x = 0, double _y = 0) : x(_x), y(_y) {};

    bool  operator==(vec2 rhs) { return x==rhs.x && y==rhs.y; };
    vec2& operator+=(vec2 rhs) { x+=rhs.x; y+=rhs.y; return *this; }
    vec2& operator-=(vec2 rhs) { x-=rhs.x; y-=rhs.y; return *this; }
    bool  operator<(vec2 rhs)  { return (x != rhs.x) ? x < rhs.x : y < rhs.y; }
    vec2  operator+(vec2 rhs)  { return vec2(x+rhs.x, y+rhs.y); }
    vec2  operator-(vec2 rhs)  { return vec2(x-rhs.x, y-rhs.y); }
    vec2  operator*(double rhs){ return vec2(rhs*x, rhs*y); }

    double angle() { return fmod(2*PI + atan2(y,x),2*PI);}
    double length()  { return hypot(x,y); }
    vec2 normalize() { double l = length(); return vec2(x/l, y/l); }

    double dot(vec2 rhs) { return x*rhs.x+y*rhs.y; }
    double cross(vec2 rhs) { return x*rhs.y-y*rhs.x; }
    vec2 project(vec2 rhs) { vec2 rn = rhs.normalize(); return rn * dot(rn); }

    // 원점에서 벡터 b가 벡터 a의 반시계 방향이면 양수, 시계방향이면 음수, 평행이면 0을 반환
    static double ccw(vec2 a, vec2 b) { return a.cross(b); }
    // 점 p를 기준으로 벡터 b가 벡터 a의 반시계 방향이면 양수, 시계방향이면 음수, 평행이면 0을 반환
    static double ccw(vec2 p, vec2 a, vec2 b) { return ccw(a-p, b-p); }
    static bool line_intersection(vec2 la, vec2 lb, vec2 ma, vec2 mb, vec2& is); 
    static bool inside_rectangle(vec2 p, vec2 a, vec2 b);
    static bool segment_overlaps(vec2 la, vec2 lb, vec2 ma, vec2 mb, vec2& olre);
    static bool segment_intersection(vec2 la, vec2 lb, vec2 ma, vec2 mb, vec2& is);
    static bool segment_intersection(vec2 la, vec2 lb, vec2 ma, vec2 mb);
    static vec2 perpendicular_foot(vec2 p, vec2 a, vec2 b);
    static double point_to_line(vec2 p, vec2 a, vec2 b);
    static double area(polygon& poly);
    static bool inside_polygon(vec2 p, polygon& poly);
    static polygon cut_polygon(polygon& poly, vec2 a, vec2 b);
private:
};

// a,b 를 포함하는 무한대 길이의 직선과 c,d를 포함하는 무한대 길이 직선의 교점을 x에 반환한다. 두 선이 평행하면 (겹치는 경우 포함) false, 아니면 true를 반환한다
bool vec2::line_intersection(vec2 la, vec2 lb, vec2 ma, vec2 mb, vec2& is){
    // change form
    vec2 a = la; vec2 k = lb-la; // line 1 = a + pk where p is some scalar
    vec2 b = ma; vec2 l = mb-ma; // line 2 = b + ql where q is some scalar
    // try to find p. if we solve this, the solution becomes ((b-a)xl)/(kxl)
    double det = k.cross(l);
    if(fabs(det) < EPSILON) // this means that la-lb and ma-mb are at parallel
        return false;
    double p = (b-a).cross(l)/det;
    is = a + (k*p);
    return true;
}

// (a,b)와 (c,d)가 평행한 두 선분일 때 (무한대 길이 아님! 각 점이 양 끝) 이들이 겹치는지 확인한다
bool vec2::segment_overlaps(vec2 la, vec2 lb, vec2 ma, vec2 mb, vec2& olre){
    if(la.x > lb.x) swap(la,lb);
    if(ma.x > mb.x) swap(ma,mb);

    if(ccw(la,lb,ma) != 0 ||
        lb.x < ma.x ||
        mb.x < la.x
    ) return false;

    olre = (la.x < ma.x) ? ma : la;
    return true;
}

// (a,b) 선분과 (c,d) 선분의 교점을 p에 반환한다. 
// 교점이 여러개일 경우 (=두 선분이 평행하고 겹칠경우) 아무 점이나 반환한다. 
// 두 선분이 교차하지 않을 경우 false를 반환한다
bool vec2::segment_intersection(vec2 la, vec2 lb, vec2 ma, vec2 mb, vec2& is){
    if(!line_intersection(la,lb,ma,mb,is)){
        return segment_overlaps(la,lb,ma,mb,is);
    }
    return inside_rectangle(is,la,lb) && inside_rectangle(is,ma,mb);
}

// 두 선분이 서로 접촉하는지 여부 만을 반환한다
bool vec2::segment_intersection(vec2 la, vec2 lb, vec2 ma, vec2 mb){
    double ccw1 = ccw(la,lb,ma)*ccw(la,lb,mb);
    double ccw2 = ccw(ma,mb,la)*ccw(ma,mb,lb);
    if(ccw1 == 0 && ccw2 == 0){
        return !(min(ma.x,mb.x) > max(la.x,lb.x) || min(la.x,lb.x) > max(ma.x,mb.x));
    }
    return ccw1 <= 0 && ccw2 <= 0;
}

// p가 (a,b)를 감싸면서 각 변이 x,y축에 평행한 최소 사각형 내부에 있는지 확인한다.
// 원래는 a,b,p는 일직선 상에 있다고 가정한다고 했는데 굳이 그런 가정을 넣을 필요가 있을까?
// 난 책 구현보다 이게 낫다고 생각함...
bool vec2::inside_rectangle(vec2 p, vec2 a, vec2 b){
    return p.x >= min(a.x,b.x) && p.x <= max(a.x,b.x) && 
           p.y >= min(a.y,b.y) && p.y <= max(a.y,b.y);
}

// 점 p에서 a,b가 만드는 길이 무한대 직선에 내린 수선의 발을 구한다
vec2 vec2::perpendicular_foot(vec2 p, vec2 a, vec2 b){
    return a + (p-a).project(b-a);
}

// 점 p와 (a,b) 직선 사이의 거리를 구한다
double vec2::point_to_line(vec2 p, vec2 a, vec2 b){
    return (p - perpendicular_foot(p,a,b)).length();
}

// 주어진 단순다각형 poly의 넓이를 구한다.
// poly는 꼭지점의 위치 벡터의 집합으로 주어지며 시계 방향 또는 반시계 방향으로 주어진다
double vec2::area(polygon& poly){
    double area_sum;
    for(int i=0; i<poly.size(); ++i){
        int j = (i+1)%poly.size();
        area_sum += (poly[i].x * poly[j].y) - (poly[i].y * poly[j].x);
    }
    return fabs(area_sum/2.0);
}

// 점 q가 다각형 p 안에 포함되어 있을 경우 참, 아닌 경우 거짓을 반환한다. 
// q가 다각형의 경계 위에 있는 경우의 반환 값은 정의되어 있지 않다
// poly는 꼭지점의 위치 벡터의 집합으로 주어지며 시계 방향 또는 반시계 방향으로 주어진다
bool vec2::inside_polygon(vec2 p, polygon& poly){
    int cross_cnt = 0;
    for(int i=0; i<poly.size(); ++i){
        int j = (i+1) % poly.size();
        if((poly[i].y > p.y) != (poly[j].y > p.y)){
            double atX = poly[i].x + (poly[j].x-poly[i].x)*((p.y-poly[i].y)/(poly[j].y-poly[i].y));
            if(atX > p.x)
                cross_cnt++;
        }
    }
    return (cross_cnt & 1);
}

// 반평면과 단순 다각형의 교집합을 구한다. 
// a->b를 포함하는 직선으로 다각형 p를 자른 뒤, a->b 의 왼쪽에 있는 부분들을 반환한다
// poly는 꼭지점의 위치 벡터의 집합으로 주어지며 시계 방향 또는 반시계 방향으로 주어진다
polygon vec2::cut_polygon(polygon& poly, vec2 a, vec2 b){
    polygon result;
    vec2 cross;
    vector<bool> inside(poly.size(),false);

    for(int i=0; i<poly.size(); ++i)
        if(ccw(poly[i],a,b) > 0)
            inside[i] = true;

    for(int i=0; i<poly.size(); ++i){
        int j = (i+1) % poly.size();
        if(inside[i])
            result.push_back(poly[i]);
        if(inside[i] != inside[j]){
            line_intersection(a,b,poly[i],poly[j],cross);
            result.push_back(cross);
        }
    }
    return result;
}

int main(int argc, char** argv){
}