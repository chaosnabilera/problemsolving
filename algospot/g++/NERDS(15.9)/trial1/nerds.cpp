#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const double BIGNUM = 987654321;

struct v2{
	double x,y;
	explicit v2(double _x, double _y) : x(_x), y(_y) {}
	bool operator==(v2& rhs) { return x == rhs.x && y == rhs.y; }
	v2 operator+(v2& rhs) { return v2(x+rhs.x, y+rhs.y); }
	v2 operator-(v2& rhs) { return v2(x-rhs.x, y-rhs.y); }
	v2 operator*(double rhs) { return v2(rhs*x, rhs*y); }
	bool operator<(v2& rhs) {
		if(x == rhs.x)
			return y < rhs.y;
		return x < rhs.x;
	}
	double norm() {return hypot(x,y);}
	double dot(v2& rhs) {return x*rhs.x + y*rhs.y; }
	double cross(v2& rhs) {return x*rhs.y - y*rhs.x; }
};

// + if vector b is ccw with respect to a
// - if cw
// 0 if on the same line
double ccw(v2 a, v2 b){
	return a.cross(b);
}

// ccw(p->a, p->b)
double ccw(v2 p, v2 a, v2 b){
	return ccw(a-p,b-p);
}

bool segment_intersects(v2 a1, v2 a2, v2 b1, v2 b2){
	double ccw_r1 = ccw(a1,a2,b1) * ccw(a1,a2,b2);
	double ccw_r2 = ccw(b1,b2,a1) * ccw(b1,b2,a2);
	return ccw_r1 <= 0 && ccw_r2 <= 0;
}

typedef vector<v2> polygon;

bool is_inside(v2 p, polygon& poly){
	int crosses = 0;
	for(int i=0; i<poly.size(); ++i){
		v2 a1 = poly[i];
		v2 a2 = poly[(i+1)%poly.size()];
		if((a1.y > p.y) != (a2.y > p.y)){
			double atX = (a2.x-a1.x)*((p.y-a1.y)/(a2.y-a1.y)) + a1.x;
			if(atX > p.x)
				crosses++;
		}
	}
	return crosses % 2 == 1;
}


int N;
vector<v2> A;
vector<v2> B;


void get_input(){
	int tf;
	double x, y;
	
	A.clear();
	B.clear();
	scanf("%d", &N);
	for(int i=0; i<N; ++i){
		scanf("%d %lf %lf", &tf, &x, &y);
		if(tf)
			A.push_back(v2(x,y));
		else
			B.push_back(v2(x,y));
	}
}

polygon convex_hull(vector<v2>& vertex){
	polygon convhull;

	// get left most + down most
	v2 ld = *min_element(vertex.begin(), vertex.end());
	// printf("%lf %lf\n", ld.x, ld.y);
	convhull.push_back(ld);

	// compute convex hull
	while(true){
		v2 p = convhull.back();
		v2 cand = vertex[0];
		for(int i=1; i<vertex.size(); ++i){
			double ccw_res = ccw(p,cand,vertex[i]);
			double dist_diff = (cand-p).norm() - (vertex[i]-p).norm();
			if(ccw_res > 0 || (ccw_res == 0 && dist_diff < 0))
				cand = vertex[i];
		}
		if(cand == ld)
			break;
		convhull.push_back(cand);
	}

	return convhull;
}

void solve(){
	bool res = true;

	// printf("A\n");
	polygon Aconv = convex_hull(A);
	// printf("B\n");
	polygon Bconv = convex_hull(B);

	// printf("?\n");

	if(is_inside(Aconv[0],Bconv) || is_inside(Bconv[0],Aconv)){
		res = false;
	}
		
	for(int i=0; i<Aconv.size() && res; ++i){
		v2 a1 = Aconv[i];
		v2 a2 = Aconv[(i+1)%Aconv.size()];

		for(int j=0; j<Bconv.size(); ++j){
			v2 b1 = Bconv[j];
			v2 b2 = Bconv[(j+1)%Bconv.size()];
			if(segment_intersects(a1,a2,b1,b2)){
				res = false;
				break;
			}
		}
	}

	if(res)
		printf("THEORY HOLDS\n");
	else
		printf("THEORY IS INVALID\n");
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}