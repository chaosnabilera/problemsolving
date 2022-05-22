#include <algorithm>
#include <iostream>
#include <cstring>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

template <typename T>
class RMQ{
public:
	RMQ(T* idata, int idatalen) {
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

int N,Q;
int Parent[100000];
std::vector<std::vector<int>> Child;
int Lv[100000];
int LvIdx[100000];
int RevIdx[100000];
std::vector<int> Lv1D;
int Lv1D_FirstOccur[100000];

void get_input(){
    scanf("%d%d",&N,&Q);
    Parent[0] = 0;
    for(int i=1; i<N; ++i)
        scanf("%d",&Parent[i]);
}

void rec_traverse(int cur){
    // printf("cur: %d", cur);
    if(Child[cur].size() > 0){
        // printf("  child: ");
        // for(int child: Child[cur]){
        //     printf("%d ", child);
        // }
        // printf("\n");
        for(int child: Child[cur]){
            rec_traverse(child);
            Lv1D.push_back(LvIdx[cur]);
        }
    }
    else{
        // printf("\n");
        Lv1D.push_back(LvIdx[cur]);
    }
}

void compute_Lv1D(){
    int lvi = 0;
    std::queue<int> q;

    Child.clear();
    Child.resize(N);
    for(int i=1; i<N; ++i){
        Child[Parent[i]].push_back(i);
    }

    lvi = 0;
    Lv[0] = 0;
    q.push(0);
    while(!q.empty()){
        int cur = q.front(); q.pop();
        LvIdx[cur] = lvi;
        RevIdx[lvi] = cur;
        ++lvi;
        for(int c:Child[cur]){
            Lv[c] = Lv[cur] + 1;
            q.push(c);
        }
    }

    // for(int i=0; i<N; ++i){
    //     printf("%d ", RevIdx[i]);
    // }
    // printf("\n");

    Lv1D.clear();
    rec_traverse(0);

    memset(Lv1D_FirstOccur, 0xFF, sizeof(Lv1D_FirstOccur));
    for(int i=0; i<Lv1D.size(); ++i){
        if(Lv1D_FirstOccur[Lv1D[i]] == -1){
            Lv1D_FirstOccur[Lv1D[i]] = i;
        }
    }
}

int solve(int a, int b, RMQ<int>& rmq){
    int lvi_a = LvIdx[a];
    int lvi_b = LvIdx[b];

    int lv1d_fo_a = Lv1D_FirstOccur[lvi_a];
    int lv1d_fo_b = Lv1D_FirstOccur[lvi_b];

    int ql = lv1d_fo_a;
    int qr = lv1d_fo_b;
    if(ql > qr)
        std::swap(ql,qr);
    
    int ca = RevIdx[rmq.query(ql,qr)];

    // printf("ca: %d\n", ca);

    int ca_lv = Lv[ca];
    int a_lv = Lv[a];
    int b_lv = Lv[b];

    // printf("a_lv: %d  b_lv: %d  ca_lv: %d\n", a_lv, b_lv, ca_lv);

    return (a_lv - ca_lv) + (b_lv - ca_lv);
}

int main(int argc, char** argv){
    int a,b,c;
    scanf("%d", &c);
    for(int i=0; i<c; ++i){
        get_input();
        compute_Lv1D();

        // for(int i=0; i<Lv1D.size(); ++i){
        //     printf("%d ",RevIdx[Lv1D[i]]);
        // }
        // printf("\n");

        RMQ<int> rmq(&Lv1D[0], Lv1D.size());
        for(int j=0; j<Q; ++j){
            scanf("%d%d", &a, &b);
            if(a == b){
                printf("0\n");
            }
            else{
                printf("%d\n", solve(a,b,rmq));
            }
        }
    }
}