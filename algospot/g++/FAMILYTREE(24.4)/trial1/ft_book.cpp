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

int N, Q;
int F[100000];
vector<int>* Graph[100000];
int Depth[100000];
int Alter[100000];
int AlterRev[100000];
int DOLoc[100000];
vector<int> DFSOrder;

template <typename T>
class RMQ{
public:
	RMQ(vector<T>& idata, int idatalen) {
		data.resize(idatalen);
		for(int i=0; i<idatalen; ++i) data[i] = idata[i];

		int rangemin_size = 1;
		while(rangemin_size < data.size())
			rangemin_size <<= 1;
		rangemin_size <<= 1;

		//printf("rangemin_size : %d\n", rangemin_size);

		rangemin.resize(rangemin_size,0);

		recursive_init(0, data.size()-1, 1);
	}
	T query(int left, int right){
		return recursive_query(left, right, 1, 0, data.size()-1);
	}
	T update(int idx, T val){
		T retval = recursive_update(idx, val, 1, 0, data.size()-1);
		data[idx] = val;
		return retval;
	}
	void print_data(){
		for(auto it=data.begin(); it != data.end(); ++it){
			printf("%d ", *it);
		}
		printf("\n");
	}
	void print_rangemin(){
		for(auto it=rangemin.begin(); it != rangemin.end(); ++it){
			printf("%d ", *it);
		}
		printf("\n");
	}
private:
	T recursive_init(int left, int right, int node){
		// printf("%d %d %d\n",left,right,node);
		if(left == right){
			rangemin[node] = data[left];
		}
		else{
			int mid = (left+right) >> 1;
			T leftmin = recursive_init(left,   mid,   node*2);
			T rightmin= recursive_init(mid+1, right, node*2+1);
			rangemin[node] = std::min(leftmin, rightmin);
		}
		return rangemin[node];
	}
	T recursive_query(int left, int right, int node, int nodeleft, int noderight){
		//printf("%d %d %d %d %d\n",left,right,node,nodeleft,noderight);
		if((right < nodeleft) || (noderight < left)){
			return std::numeric_limits<T>::max();
		}
		if((left <= nodeleft) && (noderight <= right)){
			return rangemin[node];
		}
		int mid = (nodeleft + noderight) >> 1;
		T leftmin  = recursive_query(left, right, node*2,   nodeleft, mid);
		T rightmin = recursive_query(left, right, node*2+1, mid+1, noderight);
		return std::min(leftmin, rightmin);
	}
	T recursive_update(int idx, T val, int node, int nodeleft, int noderight){
		if((idx < nodeleft) || (noderight < idx)){
			return rangemin[node];
		}
		if(nodeleft == noderight){
			rangemin[node] = val;
		}
		else{
			int mid = (nodeleft + noderight) >> 1;
			T leftmin = recursive_update(idx, val, node*2,   nodeleft, mid);
			T rightmin= recursive_update(idx, val, node*2+1, mid+1, noderight);
			rangemin[node] = std::min(leftmin, rightmin);
		}
		return rangemin[node];
	}
	std::vector<T> data;
	std::vector<T> rangemin;
};

void get_input(){
	scanf("%d %d",&N,&Q);
	F[0] = 0;
	Depth[0] = 0;
	for(int i=1; i<N; ++i)
		scanf("%d", &F[i]);
}

void clear_graph(){
	for(int i=0; i<N; ++i){
		if(Graph[i])
			delete Graph[i];
		Graph[i] = nullptr;
	}
}

void dfs(int f){
	Depth[f] = Depth[F[f]]+1;
	DFSOrder.push_back(Alter[f]);
	if(Graph[f]){
		for(int child:*Graph[f]){
			dfs(child);
			DFSOrder.push_back(Alter[f]);
		}
	}
}

void solve(){
	queue<int> q;
	int ai;

	Graph[0] = new vector<int>();
	for(int i=1; i<N; ++i){
		if(!Graph[F[i]])
			Graph[F[i]] = new vector<int>();
		Graph[F[i]]->push_back(i);
	}

	ai = 0;
	q.push(0);
	while(!q.empty()){
		int cur = q.front(); q.pop();
		Alter[cur] = ai;
		AlterRev[ai] = cur;
		++ai;
		if(Graph[cur]){
			for(int child:*Graph[cur])
				q.push(child);
		}
	}

	DFSOrder.clear();
	dfs(0);

	for(int i=0; i<DFSOrder.size(); ++i){
		DOLoc[DFSOrder[i]] = i;
	}

	RMQ<int> rmq(DFSOrder, DFSOrder.size());

	int a,b;
	for(int i=0; i<Q; ++i){
		scanf("%d %d", &a, &b);
		int aa = Alter[a];
		int ab = Alter[b];
		int aa_loc = DOLoc[aa];
		int ab_loc = DOLoc[ab];
		int ap = rmq.query(min(aa_loc,ab_loc),max(aa_loc,ab_loc));
		int p = AlterRev[ap];

		printf("%d\n",(Depth[a]-Depth[p])+(Depth[b]-Depth[p]));
	}

	clear_graph();
}

int main(int argc, char** argv){
	int T;
	memset(Graph, 0, sizeof(Graph));
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}