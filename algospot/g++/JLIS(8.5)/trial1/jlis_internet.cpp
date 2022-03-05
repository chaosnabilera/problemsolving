#include<bits/stdc++.h>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
using namespace std;

typedef long long ll;

const ll INF = ll(1e18);
int cache[101][101];

int N,M;

void print_table(){
	printf("\n");
	for(int i=0; i<=N; ++i){
		for(int j=0; j<=M; ++j){
			printf("%d ", cache[i][j]);
		}
		printf("\n");
	}
}

//a[a_idx], b[b_idx]에서 시작하는 jlis의 길이 반환 (단, a_idx == b_idx == -1 || a[a_idx] != b[b_idx] 가정)
int jlis(const vector<int>& a, const vector<int>& b, int a_idx, int b_idx) {
	int& ret = cache[a_idx + 1][b_idx + 1];
	if (ret != -1) return ret;
	ret = 2;
	ll mx = max((a_idx == -1 ? -INF : a[a_idx]), (b_idx == -1 ? -INF : b[b_idx]));
	for (int nxt = a_idx + 1; nxt < a.size(); nxt++) if (mx < a[nxt]) ret = max(ret, jlis(a, b, nxt, b_idx) + 1);
	for (int nxt = b_idx + 1; nxt < b.size(); nxt++) if (mx < b[nxt]) ret = max(ret, jlis(a, b, a_idx, nxt) + 1);
	return ret;
}

int main() {
	fastio;
	int C; cin >> C;
	while (C--) {
		memset(cache, -1, sizeof(cache));
		cin >> N >> M;
		vector<int> a(N), b(M);
		for (int i = 0; i < N; i++) cin >> a[i];
		for (int i = 0; i < M; i++) cin >> b[i];
		printf("??\n");
		cout << jlis(a, b, 0, 0) - 2 << '\n';
		printf("!!\n");
		print_table();
	}
}