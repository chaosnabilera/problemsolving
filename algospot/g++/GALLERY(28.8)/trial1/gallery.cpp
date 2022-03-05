#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cstring>
#include <limits>

int C, G, H;
std::vector<int> adj[1000];
bool visited[1000];
int camera_count;

const int HAS_CAMERA = 0;
const int IS_WATCHED = 1;
const int NOT_WATCHED = 2;

int dfs(int cur){
	int state = NOT_WATCHED;
	int child_type[3] = {0};
	int child_cnt = 0;

	visited[cur] = true;

	for(auto child: adj[cur]){
		if(!visited[child]){
			child_type[dfs(child)]++;
		}
	}

	child_cnt = child_type[HAS_CAMERA]+child_type[IS_WATCHED]+child_type[NOT_WATCHED];

	if(child_type[NOT_WATCHED] > 0){
		camera_count++;
		return HAS_CAMERA;
	}
	else if(child_type[HAS_CAMERA] > 0){
		return IS_WATCHED;
	}
	else{
		return NOT_WATCHED;
	}
}

void solve(){
	memset(visited, 0, sizeof(visited));
	camera_count = 0;

	for(int g=0; g<G; ++g){
		if(!visited[g]){
			if(dfs(g) == NOT_WATCHED){
				camera_count++;
			}
		}
	}

	printf("%d\n", camera_count);
}

int main(int argc, char** argv){
	scanf("%d", &C);
	for(int c=0; c<C; ++c){
		scanf("%d %d", &G, &H);
		for(int g=0; g<G; ++g){
			adj[g].clear();
		}
		for(int h=0; h<H; ++h){
			int a, b;
			scanf("%d %d", &a, &b);
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
		solve();
	}
}