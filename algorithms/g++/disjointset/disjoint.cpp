#include <vector>

using namespace std;

// plist 최대가 1024인 점에 유의! (path compression 할때 쓰는 것) 
// 이것은 thread safe 하지 않음!
class DisjointSet{
public:
	DisjointSet(int _V) : V(_V) {
		parent.resize(V);
		size.resize(V);
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
	int plist[1024];
};

int main(int argc, char** argv){
}