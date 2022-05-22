#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <limits>
#include <map>
#include <string>
#include <utility>
#include <vector>

int N,Q;
std::vector<std::string> Word;
std::map<std::string, int> WordToIdx;
double First[500];
double Trans[500][500];
double Inter[500][500];
double DP[500][500];
int Selection[500][500];

std::vector<int> solve(std::vector<int> given){
    std::vector<int> ans;
    int g, max_end, cur;
    size_t given_size = given.size();

    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){
            DP[i][j] = std::numeric_limits<double>::lowest();
            Selection[i][j] = -1;
        }
    }

    g = given[0];
    for(int w=0; w<N; ++w){
        DP[0][w] = First[w] + Inter[w][g];
    }
    for(int i=1; i<given_size; ++i){
        g = given[i];
        for(int w=0; w<N; ++w){
            for(int p=0; p<N; ++p){
                double cand = DP[i-1][p] + Trans[p][w] + Inter[w][g];
                if(cand > DP[i][w]){
                    DP[i][w] = cand;
                    Selection[i][w] = p;
                }
            }
        }
    }

    max_end = 0;
    for(int i=0; i<N; ++i)
        if(DP[given_size-1][i] > DP[given_size-1][max_end])
            max_end = i;
    
    ans.push_back(max_end);
    cur = max_end;
    for(int i=given_size-1; i > 0; --i){
        cur = Selection[i][cur];
        ans.push_back(cur);
    }

    std::reverse(ans.begin(),ans.end());
    return ans;
}

int main(int argc, char** argv){
    int n, ti;
    char token[0x10];
    std::vector<int> iidx;

    scanf("%d%d",&N,&Q);

    Word.clear();
    WordToIdx.clear();
    for(int i=0; i<N; ++i){
        scanf("%s", token);
        Word.push_back(token);
        WordToIdx[token] = i;
    }
    
    for(int i=0; i<N; ++i){
        scanf("%lf", &First[i]);
        First[i] = log(First[i]);
    }
        
    for(int r=0; r<N; ++r){
        for(int c=0; c<N; ++c){
            scanf("%lf", &Trans[r][c]);
            Trans[r][c] = log(Trans[r][c]);
        }
    }            

    for(int r=0; r<N; ++r){
        for(int c=0; c<N; ++c){
            scanf("%lf", &Inter[r][c]);
            Inter[r][c] = log(Inter[r][c]);
        }
    }

    for(int i=0; i<Q; ++i){
        iidx.clear();
        scanf("%d", &n);
        for(int j=0; j<n; ++j){
            scanf("%s", token);
            ti = WordToIdx[token];
            iidx.push_back(ti);
        }

        std::vector<int> ans = solve(iidx);
        for(int i:ans){
            printf("%s ", Word[i].c_str());
        }
        printf("\n");
    }
}