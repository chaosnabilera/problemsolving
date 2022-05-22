#include<stdio.h>
#include<iostream>
#include<string.h>
#include<set>
#include<vector>
#include<map>
#include<math.h>
#include<queue>
#include<string>
#include<stdlib.h>
#include<algorithm>
using namespace std;
#define N 1000005
#define ll __int64

int n; // element 숫자

int a[N],b[N];
// a = input array
// b = ?

int sx[N], sy[N];
int main(){
	int i, u, v;

	while(~scanf("%d",&n)){
		//input을 받고 그 중 maximum의 index를 얻는다
		int maxx = 0;
		for(i=0;i<n;i++){scanf("%d",&a[i]); if(a[i]>a[maxx])maxx = i;}

		// 원을 펴서 체인을 만드는 수순인듯? 그런데 왜 ++dep? 이러면 b가 1부터 찰텐데?
		int dep = 0;
		for(i=maxx; i<n;i++)b[++dep] = a[i];
		for(i=0;i<maxx; i++)b[++dep] = a[i]; 

		ll ans = 0;
		int top = 0;
		for(i = 1; i <= n; i++) { //아 이러려고 1부터 한건가...?
			// ???
			while(top && b[i]>sx[top-1])ans+=sy[--top];

			if(!top){
				sx[top] = b[i];
				sy[top++] = 1;
				continue;
			}
			if(sx[top-1]==b[i])
			{
				ans += sy[top-1];
				sy[top-1]++;
				if(top>1)ans++;
			}
			else {
				ans++;
				sx[top] = b[i];
				sy[top++] = 1;
			}
		}
		while(top>2)ans += sy[--top];
		if(top==2){
			top--;
			if(sy[top-1] > 1)ans+=sy[top];
		}
		cout<<ans<<endl;
	}
	return 0;
}