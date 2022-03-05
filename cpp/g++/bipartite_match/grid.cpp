// 구종만 책 p1023
// 격자 그래프는 이분 그래프로 표현할 수 있다
const int dx[4] = {1,-1,0,0};
const int dy[4] = {0,0,1,-1};

bool inRange(int y, int x);

int H,W;
std::vector<std::string> board;

bool fillDomino(){
	std::vector<std::vector<int>> id(H, std::vector<int>(W,-1));
	n = m = 0;
	// n = 하얀 격자의 수, m = 검은 격자의 수
	// 하얀격자가 A그룹, 검은 격자가 B그룹이라고 할 수 있다
	for(int y=0; y<H; ++y){
		for(int x=0; x<W; ++x){
			if(board[y][x] != '#'){
				if((y+x) % 2 == 0)
					id[y][x] = n++;
				else
					id[y][x] = m++;
			}
		}
	}
	memset(adj, 0, sizeof(adj));
	for(int y1=0; y1<H; ++y1){
		for(int x1=0; x1<W; ++x1){
			if((y1+x1) % 2 == 0 && board[y1][x1] != '#'){
				for(int k=0; k<4; ++k){
					int y2 = y1+dy[k], x2 = x1+dx[k];
					if(inRange(y2,x2) && board[y2][x2] != '#'){
						adj[id[y1][x1]][id[y2][x2]] = 1;
					}
				}
			}
		}
	}

	return bipartiteMatch() * 2 == (n+m);
}