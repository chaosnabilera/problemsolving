#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <deque>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

int N,M;

vector<pair<int,int>> Bucket[1001];

class DisjointSet{
public:
	DisjointSet(int _V) : V(_V) {
		parent.resize(V);
		size.resize(V);
		plist.resize(V);
		for(int i=0; i<V; ++i){
			parent[i] = i;
			size[i] = 1;
		}
	}
	~DisjointSet(){
	}
	int find_parent(int cur){ // change a->b->c->d ==> a,b,c -> d all the way up
		int p = cur;
		int plist_size = 0;
		int res;

		while(parent[p] != parent[parent[p]]){
			plist[plist_size++] = p;
			p = parent[p];
		}
		res = parent[p];

		for(int i=0; i<plist_size; ++i){
			parent[plist[i]] = res;
		}

		return res;
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
	vector<int> parent;
	vector<int> size;
	vector<int> plist;
};

void get_input(){
    int a,b,c;
    scanf("%d%d",&N,&M);

    for(int i=0; i<1001; ++i)
        Bucket[i].clear();

    for(int i=0; i<M; ++i){
        scanf("%d%d%d",&a,&b,&c);
        Bucket[c].push_back(make_pair(a,b));
    }
}

void solve(){
    int mindiff = 20000;

    for(int minspeed = 0; minspeed <= 1000; ++minspeed){
        if(Bucket[minspeed].empty())
            continue;
        DisjointSet ds(N);
        for(int maxspeed = minspeed; maxspeed <= 1000; ++maxspeed){
            if(Bucket[maxspeed].empty())
                continue;
            for(auto& p:Bucket[maxspeed]){
                int u = p.first;
                int v = p.second;
                ds.merge(u,v);
            }
            if(ds.find_parent(0) == ds.find_parent(N-1)){
                mindiff = min(mindiff, maxspeed-minspeed);
                break;
            }
        }
    }

    printf("%d\n",mindiff);
}

int main(int argc, char** argv){
    int c = 0;
    scanf("%d", &c);
    for(int i=0; i<c; ++i){
        get_input();
        solve();
    }
}