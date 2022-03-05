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
#include <cstring>

using namespace std;

const int INF = 987654321;

int N,M;

struct Point{
	double x;
	double y;
};
struct Edge{
	Point a,b;
};

Point A[100];
Point B[100];

vector<Edge> Aup, Adown;
vector<Edge> Bup, Bdown;

void get_input(){
	scanf("%d %d", &N, &M);
	for(int i=0; i<N; ++i)
		scanf("%lf %lf", &A[i].x, &A[i].y);
	for(int i=0; i<M; ++i)
		scanf("%lf %lf", &B[i].x, &B[i].y);

	Aup.clear();
	Adown.clear();
	Bup.clear();
	Bdown.clear();
}

void split_polygon(){
	for(int i=0; i<N; ++i){
		Edge e;
		e.a = A[i]; e.b = A[(i+1)%N];
		if(e.a.x < e.b.x)
			Adown.push_back(e);
		else
			Aup.push_back(e);
	}
	for(int i=0; i<M; ++i){
		Edge e;
		e.a = B[i]; e.b = B[(i+1)%M];
		if(e.a.x < e.b.x)
			Bdown.push_back(e);
		else
			Bup.push_back(e);
	}
}

double get_min_x(vector<Edge>& edges){
	double res = INF;
	for(Edge& e:edges){
		res = min(res,e.a.x);
		res = min(res,e.b.x);
	}
	return res;
}

double get_max_x(vector<Edge>& edges){
	double res = -INF;
	for(Edge& e:edges){
		res = max(res,e.a.x);
		res = max(res,e.b.x);
	}
	return res;
}

double get_intersection(vector<Edge>& edges, double px){
	for(Edge& e:edges){
		double x1 = e.a.x;		double x2 = e.b.x;
		double y1 = e.a.y;      double y2 = e.b.y;

		if(x1 != x2 && px >= min(x1,x2) && px <= max(x1,x2)){
			double res = y1 + ((y2-y1)/(x2-x1))*(px-x1);
			return res;
		}
	}
	return -INF;
}

double get_delta(double px){
	double iAup   = get_intersection(Aup, px);
	double iBup   = get_intersection(Bup, px);
	double iAdown = get_intersection(Adown, px);
	double iBdown = get_intersection(Bdown, px);

	return min(iAup,iBup) - max(iAdown,iBdown);
}

void solve(){
	split_polygon();

	double l = max(get_min_x(Adown),get_min_x(Bdown));
	double r = min(get_max_x(Adown),get_max_x(Bdown));

	// do trilinear search
	while(r-l > 0.00000001){
		double delta = (r-l)/3.0;
		double ll = l+delta;
		double rr = r-delta;

		double llres = get_delta(ll);
		double rrres = get_delta(rr);

		if(llres < rrres)
			l = ll;
		else
			r = rr;
	}

	double res = get_delta((r+l)*0.5);
	printf("%.10lf\n", max(res,0.0));
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		get_input();
		solve();
	}
}