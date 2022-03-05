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

const int UNREACHABLE = 1000000000;
int C,N,M;
std::vector<std::pair<int,int>> edge;

class DisjointSet{
public:
	DisjointSet(int _V) : V(_V) {
		parent = new int[V];
		size = new int[V];
		for(int i=0; i<V; ++i){
			parent[i] = i;
			size[i] = 1;
		}
	}
	~DisjointSet(){
		delete[] parent;
		delete[] size;
	}
	int find_parent(int iv){
		int p = parent[iv];
		if(p != iv){
			parent[iv] = find_parent(p);
		}
		return parent[iv];
	}
	void merge(int a, int b){
		a = find_parent(a);
		b = find_parent(b);
		if(size[a] > size[b]){
			size[a] += size[b];
			parent[b] = a;
		}
		else{
			size[b] += size[a];
			parent[a] = b;
		}
	}
private:
	int V;
	int* parent;
	int* size;
};

int compute_upperbound(int lowerbound){
	int w,a,b;
	int res = UNREACHABLE;
	DisjointSet djs(N);

	for(auto cp:edge){
		w = cp.first;
		if(w < lowerbound){
			continue;
		}

		a = cp.second >> 16;
		b = cp.second & 0xFFFF;
		djs.merge(a,b);

		if(djs.find_parent(0) == djs.find_parent(N-1)){
			res = w;
			break;
		}
	}

	return res;
}

void solve(){
	int mindiff = UNREACHABLE;

	std::sort(edge.begin(), edge.end());
	for(auto cp:edge){
		int lowerbound = cp.first;
		int upperbound = compute_upperbound(lowerbound);
		mindiff = std::min(mindiff, upperbound-lowerbound);
	}

	printf("%d\n", mindiff);
}

int main(int argc, char** argv){
	unsigned int a, b, c, e;

	scanf("%d", &C);
	for(int i=0; i<C; ++i){
		scanf("%d %d", &N, &M);
		edge.clear();
		for(int i=0; i<M; ++i){
			scanf("%d %d %d", &a, &b, &c);
			edge.push_back(std::make_pair(c,a<<16|b));
		}
		solve();
	}
}