#include <cmath>
#include <limits>
#include <utility>
#include <vector>
#include <iostream>

const double PI = 2.0 * acos(0.0);
const double EPSILON = std::numeric_limits<double>::min();

struct vector2{
	double x,y;
	explicit vector2(double _x=0, double _y=0) : x(_x), y(_y) {}

	bool operator==(const vector2& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
	bool operator<(const vector2& rhs) const {
		return x != rhs.x ? x < rhs.x : y < rhs.y;
	}
	vector2 operator+(const vector2& rhs) const {
		return vector2(x+rhs.x, y+rhs.y);
	}
	vector2 operator-(const vector2& rhs) const {
		return vector2(x-rhs.x, y-rhs.y);
	}
	vector2 operator*(double rhs) const {
		return vector2(rhs*x, rhs*y);
	}
	double norm() const {
		return hypot(x,y);
	}
	vector2 normalize() const {
		double cur_norm = norm();
		return vector2(x/cur_norm, y/cur_norm);
	}
	double polar() const { // x축의 양의 방향으로 부터 이 벡터까지 반시계 방항으로 잰 각도
		return fmod(atan2(y,x)+2*PI,2*PI);
	}
	// dot product
	// - 두 벡터 사이의 내각을 얻는데 유용하다
	// - 두 벡터가 직각인지 여부를 알 수 있음
	double dot(const vector2& rhs) const { 
		return x*rhs.x + y*rhs.y;
	}
	// cross product
	// 2d에서 cross product는 두 벡터가 만드는 평행사변형의 넓이를 줌 (절대값)
	// cross > 0 : rhs는 반시계 방향 180도 안에 있음
	// cross < 0 : rhs는 시계방향 180도 안에 있음
	double cross(const vector2& rhs) const {
		return x*rhs.y - rhs.x*y;
	}
	vector2 project(const vector2& rhs) const {
		vector2 r = rhs.normalize();
		return r*r.dot(*this);
	}
};

// a가 b에 비해 p에 얼마나 가까운가?
double howMuchClose(vector2 p, vector2 a, vector2 b){
	return (b-p).norm() - (a-p).norm();
}

// 원점에서 벡터 b가 벡터 a의 반시계 방향이면 양수, 시계방향이면 음수, 평행이면 0을 반환
double ccw(vector2 a, vector2 b){
	return a.cross(b);
}

// 점 p를 기준으로 벡터 b가 벡터 a의 반시계 방향이면 양수, 시계방향이면 음수, 평행이면 0을 반환
double ccw(vector2 p, vector2 a, vector2 b){
	return ccw(a-p, b-p);
}


// a,b 를 포함하는 무한대 길이의 직선과 c,d를 포함하는 무한대 길이 직선의 교점을 x에 반환한다
// 두 선이 평행하면 (겹치는 경우 포함) false, 아니면 true를 반환한다
// 저 식의 원리는 같은 폴더의 line_intersection_explanation.jpg 참조할 것
bool lineIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& x){
	double det = (b-a).cross(d-c);
	if(fabs(det) < EPSILON) return false;
	x = a + (b-a) * ((c-a).cross(d-c) / det);
	return true;
}


// (a,b)와 (c,d)가 평행한 두 선분일 때 (무한대 길이 아님! 각 점이 양 끝) 이들이 겹치는지 확인한다
bool parallelSegments(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p){
	if(b < a) std::swap(a,b);
	if(d < c) std::swap(c,d);

	if(ccw(a,b,c) != 0 // 평행하지 않음
		|| b < c // a-b , c-d 인데 b와 c가 겹칠 수 없다
		|| d < a // c-d , a-b 인데 d와 a가 겹칠 수 없다
	) return false;

	// 확실히 겹침. 둘 중에 오른쪽에 오는걸 리턴한다
	p = (a<c) ? c : a;
	return true;
}

// p가 (a,b)를 감싸면서 각 변이 x,y축에 평행한 최소 사각형 내부에 있는지 확인한다
// a,b,p는 일직선 상에 있다고 가정한다
bool inBoundingRectangle(vector2 p, vector2 a, vector2 b){
	if(b<a) std::swap(a,b);
	return p == a || p == b || (a<p && p<b);
}

// (a,b) 선분과 (c,d) 선분의 교점을 p에 반환한다
// 교점이 여러개일 경우 (=두 선분이 평행하고 겹칠경우) 아무 점이나 반환한다
// 두 선분이 교차하지 않을 경우 false를 반환한다
bool segmentIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p){
	if(!lineIntersection(a,b,c,d,p))
		return parallelSegments(a,b,c,d,p);
	return inBoundingRectangle(p,a,b) && inBoundingRectangle(p,c,d);
}

// 두 선분이 서로 접촉하는지 여부를 반환한다
// 자세한건 segment_intersects_explanation.jpg 를 참조한다
bool segmentIntersects(vector2 a, vector2 b, vector2 c, vector2 d){
	double ab = ccw(a, b, c) * ccw(a, b, d);
	double cd = ccw(c, d, a) * ccw(c, d, b);
	if(ab == 0 && cd == 0){
		if(b < a) std::swap(a,b);
		if(d < c) std::swap(c,d);
		return !(b < c || d < a);
	}
	// < 0 이 아니라 <= 0 인 이유는 한쪽 선분 끝이 다른 선분 위에 놓일수도 있어서임
	return ab <= 0 && cd <= 0; 
}

// 점 p에서 a,b가 만드는 길이 무한대 직선에 내린 수선의 발을 구한다
vector2 perpendicularFoot(vector2 p, vector2 a, vector2 b){
	return a + (p-a).project(b-a);
}

// 점 p와 (a,b) 직선 사이의 거리를 구한다
double pointToLine(vector2 p, vector2 a, vector2 b){
	return (p-perpendicularFoot(p,a,b)).norm();
}

// 주어진 단순다각형 p의 넓이를 구한다
// p는 꼭지점의 위치 벡터의 집합으로 주어진다
double area(const std::vector<vector2>& p){
	double ret = 0;
	for(int i=0; i<p.size(); ++i){
		int j = (i+1) % p.size();
		ret += p[i].x*p[j].y - p[j].x*p[i].y; // cross product
	}
	return fabs(ret)/2.0;
}

// 점 q가 다각형 p 안에 포함되어 있을 경우 참, 아닌 경우 거짓을 반환한다
// q가 다각형의 경계 위에 있는 경우의 반환 값은 정의되어 있지 않다
bool isInside(vector2 q, const std::vector<vector2>& p){
	int crosses = 0;
	for(int i=0; i<p.size(); ++i){
		int j = (i+1) % p.size();
		// 이 조건은 선분의 한쪽 끝은 q보다 **위에** 있고 다른 한쪽 끝은 q보다 아래이거나 같을때만 된다
		// 즉 선분의 양쪽 끝이 q에서 x에 평행한 반직선과 완전히 겹치거나
		// 한쪽 끝은 걸치지만 다른쪽 끝이 q보다 아래에 있는 직선은 count 되지 않는다
		// 반직선 알고리즘의 예외 처리를 위함
		if((p[i].y > q.y) != (p[j].y > q.y)){
			double atX = (p[j].x - p[i].x) * (q.y-p[i].y) / (p[j].y - p[i].y) + p[i].x;
			if(q.x < atX)
				++crosses;
			// printf("%d:(%lf %lf) %d:(%lf %lf) crosses:%d\n",
			// 	i,p[i].x,p[i].y, j,p[j].x,p[j].y, crosses);
		}

	}
	return crosses % 2 > 0;
}

typedef std::vector<vector2> polygon;

// 반평면과 단순 다각형의 교집합을 구한다
// a->b를 포함하는 직선으로 다각형 p를 자른 뒤, a->b 의 왼쪽에 있는 부분들을 반환한다
polygon cutPoly(const polygon& p, const vector2& a, const vector2& b){
	int n = p.size();
	// 각 점이 반평면 내에 있는지 여부를 우선 확인한다
	std::vector<bool> inside(n);
	for(int i=0; i<n; ++i)
		inside[i] = ccw(a, b, p[i]) >= 0;

	polygon ret;
	//다각형의 각 변을 순회하면서 결과 다각형의 각 점을 발견한다
	for(int i=0; i<n; ++i){
		int j = (i+1) % n;
		// 반평면 내에 있는 점 p[i]는 항상 결과 다각형에 포함시킨다
		if(inside[i]) ret.push_back(p[i]);
		// 변 p[i]-p[j]가 직선과 교차하면 결과 다각형에 포함시킨다
		if(inside[i] != inside[j]){
			vector2 cross;
			// assert(lineIntersection(p[i],p[j],a,b,cross));
			lineIntersection(p[i],p[j],a,b,cross);
			ret.push_back(cross);
		}
	}
	return ret;
}

polygon intersection(const polygon& p, double x1, double y1, double x2, double y2){
	vector2 a(x1,y1), b(x2,y1), c(x2,y2), d(x1,y2);
	polygon ret = cutPoly(p, a, b);
	ret = cutPoly(ret, b, c);
	ret = cutPoly(ret, c, d);
	ret = cutPoly(ret, d, a);
	return ret;
}

double X1, Y1, X2, Y2;
int N;
std::vector<vector2> P;

void get_input(){
	double ix, iy;
	scanf("%lf %lf %lf %lf %d", &X1, &Y1, &X2, &Y2, &N);
	P.clear();
	for(int i=0; i<N; ++i){
		scanf("%lf %lf", &ix, &iy);
		P.push_back(vector2(ix,iy));
	}
}

void solve(){
	polygon result = intersection(P,X1,Y1,X2,Y2);
	printf("%.10lf\n", area(result));
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}