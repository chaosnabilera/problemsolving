#include <stdio.h>

int K;
int Q;
char S[300000];
int CNTTREE[300000];
int LtS[300000];
int StL[300000];
int LIMIT;

void solve(int p, char c) {
	int si = p - 1;
	S[si] = c;

	int li = StL[si];
	while (li > 0) {
		si = LtS[li];
		if (li >= (LIMIT >> 1)) {
			CNTTREE[li] = (S[si] == '?') ? 2 : 1;
		}
		else {
			if (S[si] == '0') {
				CNTTREE[li] = CNTTREE[li * 2];
			}
			else if (S[si] == '1') {
				CNTTREE[li] = CNTTREE[li * 2 + 1];
			}
			else {
				CNTTREE[li] = CNTTREE[li * 2] + CNTTREE[li * 2 + 1];
			}
		}
		li >>= 1;
	}

	printf("%d\n", CNTTREE[1]);
}

int main() {
	scanf("%d\n", &K);
	scanf("%s\n", S);
	scanf("%d\n", &Q);

	LIMIT = 1 << K;

	int lv_beg = 1;
	int lv_end = 2;

	while (lv_beg < LIMIT) {
		int s_beg = LIMIT - lv_end;
		int s_end = LIMIT - lv_beg;

		for (int i = 0; i < lv_end - lv_beg; ++i) {
			int li = lv_beg + i;
			int si = s_beg + i;
			LtS[li] = si;
			StL[si] = li;
		}

		lv_beg = lv_end;
		lv_end <<= 1;
	}

	int leaf_start = LIMIT >> 1;
	for (int li = leaf_start; li < LIMIT; ++li) {
		int si = LtS[li];
		CNTTREE[li] = (S[si] == '?') ? 2 : 1;
	}

	int curlv_start = leaf_start >> 1;
	int curlv_end = leaf_start;

	while (curlv_start > 0) {
		for (int li = curlv_start; li < curlv_end; ++li) {
			int si = LtS[li];
			if (S[si] == '0') {
				CNTTREE[li] = CNTTREE[li * 2];
			}
			else if (S[si] == '1') {
				CNTTREE[li] = CNTTREE[li * 2 + 1];
			}
			else {
				CNTTREE[li] = CNTTREE[li * 2] + CNTTREE[li * 2 + 1];
			}
		}
		curlv_end = curlv_start;
		curlv_start >>= 1;
	}

	int p;
	char c;
	for (int q = 0; q < Q; ++q) {
		scanf("%d %c\n", &p, &c);
		solve(p, c);
	}
}