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
#include <cmath>

using namespace std;

int main(int argc, char** argv){
	int t;
	long long n,m;

	scanf("%d", &t);
	for(int i=0; i<t; ++i){
		scanf("%lld %lld", &n, &m);

		long long a = (100*m)/n;
		long long b = (100*m)%n;

		if(a >= 99){
			printf("-1\n");
		}
		else{
			double xd = ((double)(n-b))/((double)(99-a));
			printf("%d\n", (int)ceil(xd));
		}
	}
}