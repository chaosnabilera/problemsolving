include <iostream>
#include <vector>
#include <cstring>

using namespace std;

bool Graph[26][26];
int InCnt[26];

int N;
char Dict[1000][21];

void get_input(){
	scanf("%d", &N);
	for(int i=0; i<N; ++i){
		scanf("%s", Dict[i]);
	}
}

void rec_build(vector<char*>& worder){
	// for(char* s:worder){
	// 	printf("%s ",s);
	// }
	// printf("\n");

	char prev = worder[0][0]-'a';
	for(int i=1; i<worder.size(); ++i){
		char cur = worder[i][0]-'a';
		
		if(prev != cur){
			if(!Graph[prev][cur]){
				Graph[prev][cur] = true;
				InCnt[cur]++;
			}
			prev = cur;
		}
	}

	int i = 0;
	while(i<worder.size()){
		vector<char*> next_worder;
		int j = i;
		while(j < worder.size() && worder[j][0] == worder[i][0]){
			if(worder[j][1] != 0)
				next_worder.push_back(&(worder[j][1]));
			++j;
		}
		if(next_worder.size())
			rec_build(next_worder);
		i = j;
	}
}

void solve(){
	memset(Graph,0,sizeof(Graph));
	memset(InCnt,0,sizeof(InCnt));

	vector<char*> worder;
	worder.reserve(N);
	for(int i=0; i<N; ++i){
		// printf("%s\n",Dict[i]);
		worder.push_back(Dict[i]);
	}

	rec_build(worder);

	// for(int i=0; i<26; ++i){
	// 	printf("%c:%d ",'a'+i, InCnt[i]);
	// }
	// printf("\n");

	vector<char> ans;
	bool visited[26] = {0};

	for(int k=0; k<26; ++k){
		for(int i=0; i<26; ++i){
			if(!visited[i] && InCnt[i] == 0){
				ans.push_back('a'+i);
				visited[i] = true;

				for(int j=0; j<26; ++j){
					if(Graph[i][j]){
						Graph[i][j] = false;
						--InCnt[j];
					}
				}
			}
		}
	}

	if(ans.size() != 26){
		printf("INVALID HYPOTHESIS\n");
	}
	else{
		for(char c:ans)
			printf("%c",c);
		printf("\n");
	}
		
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}