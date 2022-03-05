// 구종만 책 2권 page 1019 내용

int n, m;

bool adj[MAX_N][MAX_M];
std::vector<int> aMatch, bMatch;
std::vector<bool> visited;

bool dfs(int a){
	if(visited[a]){
		return false;
	}
	visited[a] = true;
	for(int b=0; b<m; ++b){
		if(adj[a][b]){
			// a group 중 갈 수 있는 곳이 있거나
			// 비켜줄 수 있는 곳이 있는지 확인한다
			if(bMatch[b] == -1 || dfs(bMatch[b])){
				aMatch[a] = b;
				bMatch[b] = a;
				return true;
			}
		}
	}
	return false;
}

int bipartiteMatch(){
	aMatch = std::vector<int>(n,-1);
	bMatch = std::vector<int>(m,-1);
	int size = 0;
	for(int start=0; start<n; ++start){
		visited = vector<bool>(n,false);
		if(dfs(start))
			++size;
	}
	return size;
}