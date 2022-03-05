#include <iostream>
#include <vector>
#include <utility>

using namespace std;

const double BIGNUM = 987654321;

int N;
int M;
double A[100][2];
double B[100][2];

struct Line{ // x1 < x2
	const double x1,y1;
	const double x2,y2;
	bool is_up;
	Line(double _x1, double _y1, double _x2, double _y2, bool _is_up) :
	x1(_x1), y1(_y1), x2(_x2), y2(_y2), is_up(_is_up) {}
};

vector<Line> lA;
vector<Line> lB;

void get_input(){
	scanf("%d %d", &N, &M);
	for(int i=0; i<N; ++i)
		scanf("%lf %lf", &A[i][0], &A[i][1]);
	for(int i=0; i<M; ++i)
		scanf("%lf %lf", &B[i][0], &B[i][1]);
}

void categorize_lines(){
	double x1,y1,x2,y2;

	lA.clear();
	lB.clear();

	for(int i=0; i<N; ++i){
		x1 = A[i][0];         y1 = A[i][1];
		x2 = A[(i+1) % N][0]; y2 = A[(i+1) % N][1];

		if(x1 < x2) // lower shell
			lA.push_back(Line(x1,y1,x2,y2,false));
		else // upper shell
			lA.push_back(Line(x2,y2,x1,y1,true));
	}

	for(int i=0; i<M; ++i){
		x1 = B[i][0];         y1 = B[i][1];
		x2 = B[(i+1) % M][0]; y2 = B[(i+1) % M][1];

		if(x1 < x2) // lower shell
			lB.push_back(Line(x1,y1,x2,y2,false));
		else // upper shell
			lB.push_back(Line(x2,y2,x1,y1, true));
	}
}

void compute_x_limit(double& minX, double& maxX){
	double AminX = BIGNUM;  double AmaxX = -BIGNUM;
	double BminX = BIGNUM;  double BmaxX = -BIGNUM;

	for(int i=0; i<N; ++i){
		AminX = min(AminX, A[i][0]);
		AmaxX = max(AmaxX, A[i][0]);
	}

	for(int i=0; i<M; ++i){
		BminX = min(BminX, B[i][0]);
		BmaxX = max(BmaxX, B[i][0]);
	}

	minX = max(AminX,BminX);
	maxX = min(AmaxX,BmaxX);
}

double get_match(double x, vector<Line>& P, bool is_up){
	// default for upper shell : bignum, lowershell : small num
	double res = (is_up) ? BIGNUM : -BIGNUM;
	double yb, yh; 
	for(Line& l:P){
		if(l.is_up == is_up && x >= l.x1 && x <= l.x2){
			if(l.y1 < l.y2){
				yb = l.y1;
				yh = l.y2-l.y1;
				res = yb + (((x-l.x1)/(l.x2-l.x1)) * yh);
			}
			else{
				yb = l.y2;
				yh = l.y1 - l.y2;
				res = yb + (((l.x2-x)/(l.x2-l.x1)) * yh);		
			}
			break;
		}
	}
	return res;
}

double height_at_x(double x){
	double Aup = get_match(x,lA,true);
	double Adown = get_match(x,lA,false);
	double Bup = get_match(x,lB,true);
	double Bdown = get_match(x,lB,false);

	// printf("Aup:%lf Adown:%lf Bup:%lf Bdown:%lf\n", Aup, Adown, Bup, Bdown);

	return min(Aup,Bup) - max(Adown,Bdown);
}

void solve(){
	double minX, maxX;
	double dx, x1, x2;
	double h1, h2;

	categorize_lines();
	compute_x_limit(minX, maxX);

	// printf("minX: %lf  maxX: %lf\n", minX, maxX);

	//trilinear search
	while(maxX - minX > 0.00000001){
		dx = (maxX-minX)/3.0;

		x1 = minX+dx;
		x2 = maxX-dx;
		h1 = height_at_x(x1);
		h2 = height_at_x(x2);

		// printf("x1:%lf h1:%lf x2:%lf h2:%lf\n", x1,h1,x2,h2);

		if(h1 < h2){
			minX = x1;
		}
		else if(h1 > h2){
			maxX = x2;
		}
		else{
			minX = x1;
			maxX = x2;
		}
	}

	printf("%.10lf\n", max(0.0,height_at_x((minX+maxX)/2.0)));
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}