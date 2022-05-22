#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 1005;

LL high[1007][1007];
bool vis[1007][1007];
LL dp[1005][20];
LL dp2[N][20];
LL f[N][N];
LL sum[N][N];

struct Node{
    int x, y;
    LL cost;
    Node() {}
    Node(int xx, int yy, LL c) : x(xx), y(yy), cost(c) {}
    friend bool operator < (Node aa, Node bb){
        if(aa. cost == bb. cost){
            if(aa. x == bb. x)
                return aa. y < bb. y;
            return aa. x < bb. x;
        }
        return aa. cost < bb. cost;
    }
}d[1000005];
int n, m, a, b;
vector <Node> ans;

int main(){
    while(scanf("%d %d %d %d", &n, &m, &a, &b) != EOF){
        memset(sum, 0, sizeof sum);
        memset(f, 0, sizeof f);
        for(int i = 1; i <= n; i ++)
            for(int j = 1; j <= m; j ++){
                scanf("%I64d", &high[i][j]);
                sum[i][j] = (sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1]) + high[i][j];
            }
        for(int i = 1; i <= n; i ++){
            for(int j = 1; j <= m; j ++)
                dp[j][0] = high[i][j];
            for(int k = 1; (1 << k) <= b; k ++)
                for(int j = 1; j + (1 << k) - 1 <= m; j ++)
                    dp[j][k] = min(dp[j][k - 1], dp[j + (1 << (k - 1))][k - 1]);
            int k = log(b * 1.0) / log(2.0);
            for(int j = 1; j <= m - b + 1; j ++){
                f[i][j] = min(dp[j][k], dp[j + b - (1 << k)][k]);
            }
        }
        for(int i = 1; i <= m - b + 1; i ++){
            for(int j = 1; j <= n; j ++){
                dp[j][0] = f[j][i];
            }

            for(int k = 1; (1 << k) <= a; k ++)
                for(int j = 1; j + (1 << k) - 1 <= n; j ++){
                    dp[j][k] = min(dp[j][k - 1], dp[j + (1 << (k - 1))][k - 1]);
                }
            int k = log(a * 1.0) / log(2.0);
            for(int j = 1; j <= (n - a + 1); j ++){
                f[j][i] = min(dp[j][k], dp[j + a - (1 << k)][k]);
            }
        }
        int cnt = 0;
        for(int i = 1; i <= n - a + 1; i ++)
            for(int j = 1; j <= m - b + 1; j ++){
            LL tmp = sum[i + a - 1][j + b - 1] - sum[i + a - 1][j - 1] - sum[i - 1][j + b - 1] + sum[i - 1][j - 1] - f[i][j] * a * b;
            d[cnt ++] = Node(i, j, tmp);
        }
        sort(d, d + cnt);
        ans. clear();
        memset(vis, false, sizeof vis);
        for(int i = 0; i < cnt; i ++){
            if(!vis[d[i]. x][d[i]. y] && !vis[d[i]. x + a - 1][d[i]. y] && !vis[d[i]. x][d[i]. y + b - 1] && !vis[d[i]. x + a - 1][d[i]. y + b - 1]){
                for(int j = d[i]. x; j < d[i]. x + a; j ++)
                    for(int k = d[i]. y; k < d[i]. y + b; k ++)
                    vis[j][k] = true;
                ans. push_back(d[i]);
            }
        }
        printf("%d\n", ans. size());
        for(int i = 0; i < ans. size(); i ++){
            printf("%d %d %I64d\n", ans[i]. x, ans[i]. y, ans[i]. cost);
        }
    }
    return 0;
}