#include <iostream>
#include <vector>

//Just solve it for N=20, B=15
void solve(){
	std::vector<std::vector<int>> tower;
	int cur = 0;
	int max_ti, max_h, min_ti, min_h;
	bool found_best;

	char buf[100] = {0};

	tower.resize(20);

	for(int i=0; i<300; ++i){
		// fprintf(stderr,"<%d>\n",i);
		scanf("%d",&cur);
		// fprintf(stderr,"<%d>\n",i);
		//printf("<%d>\n",cur);
		if(cur == 9){
			// fprintf(stderr,"<a>\n");
			//1. try to put on top
			found_best = false;
			for(int ti=0; ti<20; ++ti){
				if(tower[ti].size() == 14){
					tower[ti].push_back(cur);
					printf("%d\n",ti+1);
					fflush(stdout);
					found_best = true;
					break;
				}
			}
			if(found_best)
				continue;
			//2. try to put on highest
			max_ti = -1;
			max_h = 0;
			for(int ti=0; ti<20; ++ti){
				if(tower[ti].size() == 15){
					continue;
				}
				if(tower[ti].size() >= max_h){
					max_ti = ti;
					max_h = tower[ti].size();
				}
			}
			tower[max_ti].push_back(cur);
			printf("%d\n",max_ti+1);
			fflush(stdout);
		}
		else if(cur == 8){
			// fprintf(stderr,"<b>\n");
			//1. try to find tallest tower below 14
			max_ti = -1;
			max_h = 0;
			for(int ti=0; ti<20; ++ti){
				if((tower[ti].size() < 14) && (tower[ti].size() >= max_h)){
					max_ti = ti;
					max_h = tower[ti].size();
				}
			}
			if(max_ti >= 0){
				tower[max_ti].push_back(cur);
				printf("%d\n",max_ti+1);
				fflush(stdout);
				continue;
			}
			// 2. All towers are 14>= tall. Just put anywhere
			for(int ti=0; ti<20; ++ti){
				if(tower[ti].size() < 15){
					tower[ti].push_back(cur);
					printf("%d\n",ti+1);
					fflush(stdout);
					break;
				}
			}
		}
		else{
			// fprintf(stderr,"<c>\n");
			//1. try to put at tallest tower that is below 13 floor
			max_ti = -1;
			max_h = 0;
			for(int ti=0; ti<20; ++ti){
				if((tower[ti].size() < 13) && (tower[ti].size() >= max_h)){
					max_ti = ti;
					max_h = tower[ti].size();
				}
			}
			if(max_ti >= 0){
				tower[max_ti].push_back(cur);
				printf("%d\n",max_ti+1);
				fflush(stdout);
				continue;
			}
			// 2. All towers are 12>= tall. try to find lowest
			min_ti = 0;
			min_h = tower[0].size();
			for(int ti=1; ti<20; ++ti){
				if(tower[ti].size() < min_h){
					min_ti = ti;
					min_h = tower[ti].size();
				}
			}

			tower[min_ti].push_back(cur);
			printf("%d\n",min_ti+1);
			fflush(stdout);
		}
	}

	// for(int i=0; i<20; ++i){
	// 	for(auto it=tower[i].begin(); it != tower[i].end(); ++it){
	// 		fprintf(stderr, "%d ", *it);
	// 	}
	// 	fprintf(stderr,"\n");
	// }
}

int main(int argc, char** argv){
	int T,N,B;
	unsigned long long P;
	int result;
	scanf("%d %d %d %lld",&T,&N,&B,&P);

	for(int t=0; t<T; ++t){
		solve();
		// printf("done?\n");
		// scanf("%d", &result);
	}
	scanf("%d", &result);
}