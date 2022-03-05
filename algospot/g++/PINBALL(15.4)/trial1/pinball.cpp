#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cstring>
#include <limits>
#include <utility>
#include <queue>
#include <array>
#include <string>
#include <deque>
#include <cmath>

using namespace std;

const double PI = 2.0 * acos(0.0);
const double EPSILON = std::numeric_limits<double>::min();
const double BIGNUM = 987654321.0;

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

//----------------------------------------------------------------------------------------

double iX, iY, iDX, iDY;
int N;
double C[50][3];

void get_input(){
	scanf("%lf %lf %lf %lf %d", &iX, &iY, &iDX, &iDY, &N);
	for(int i=0; i<N; ++i){
		scanf("%lf %lf %lf", &C[i][0], &C[i][1], &C[i][2]);
		C[i][2] += 1.0; // account for ball radius
	}
}

bool line_circle_intersect(vector2 lo, vector2 ld, int ci){
	double cx = C[ci][0]; 	double cy = C[ci][1]; 	double cr = C[ci][2];
	vector2 cc(cx,cy);
	return (pointToLine(cc, lo, ld) < cr);
}

vector2 get_line_circle_intersection(vector2 lo, vector2 ld, int ci){
	double cx = C[ci][0]; 	double cy = C[ci][1]; 	double cr = C[ci][2];
	vector2 cc(cx,cy);
	vector2 pf = perpendicularFoot(cc, lo, ld);

	double d_pf_cc = (pf-cc).norm();
	double d_pf_is = sqrt((cr*cr)-(d_pf_cc*d_pf_cc));

	return pf-((ld-lo).normalize()*d_pf_is);
}

//return false if no intersection
bool get_first_intersection_point(vector2 lo, vector2 ld, vector2& fis, int& fisci){ 
	bool has_intersection = false;
	vector2 tis;
	vector2 td;
	double min_dist = BIGNUM;

	vector2 dd = ld-lo;

	for(int ci=0; ci<N; ++ci){
		if(line_circle_intersect(lo,ld,ci)){
			tis = get_line_circle_intersection(lo,ld,ci);
			td = tis-lo;
			if(td.x*dd.x < 0 || td.y*dd.y < 0){
				continue;
			}
			has_intersection = true;
			if(td.norm() < min_dist){
				min_dist = td.norm();
				fis = tis;
				fisci = ci;
			}
		}
	}
	return has_intersection;
}

void solve(){
	vector2 lo(iX,iY);
	vector2 ld(iX+iDX,iY+iDY);
	vector2 fis;
	int fisci;

	for(int it=0; it<100; ++it){ // limit iterations to 100
		// printf("lo:%8lf %8lf ld:%8lf %8lf\n", lo.x, lo.y, ld.x, ld.y);
		if(!get_first_intersection_point(lo,ld,fis,fisci))
			break;

		printf("%d ",fisci);

		double fcx = C[fisci][0]; double fcy = C[fisci][1]; double fcr = C[fisci][2];

		vector2 rfoot = perpendicularFoot(lo, fis, vector2(fcx,fcy));
		vector2 rdir = rfoot-lo;

		// printf("fis:%8lf %8lf (%8lf) rfoot:%8lf %8lf rdir:%8lf %8lf\n",
		// 	fis.x,fis.y,(fis-vector2(fcx,fcy)).norm(),rfoot.x,rfoot.y,rdir.x,rdir.y);

		lo = fis;
		ld = rfoot+rdir;
	}
	printf("\n");
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}