
#include <iostream>
#include <string.h>
#include <algorithm>
#define STD std::ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
const int maxn=1e6+10;
int a[maxn],b[maxn],l[maxn],r[maxn],s[maxn];
using namespace std;
int main()
{
	STD;
	int n,maxn,po;
	cin>>n;
	for (int i=0;i<n;i++)
		cin>>a[i]; // a가 input array임
	maxn=a[0]; //max값
	po=0; //max의 position
	for (int i=1;i<n;i++)
	{
		if (a[i]>maxn)
		{
			maxn=a[i];
			po=i;
		}
	}
	// b가 chain. 신박한 방법이다....
	for (int i=0;i<n;i++)
		b[i]=a[(po+i)%n];
	b[n]=b[0]; // chain 마지막에 최대값

	s[n]=0; // ????
	for (int i=n-1;i>=0;i--)
	{
		r[i]=i+1;
		while (r[i]<n&&b[i]>b[r[i]])
			r[i]=r[r[i]];
		while (r[i]<n&&b[i]==b[r[i]])
		{
			s[i]=s[r[i]]+1;
			r[i]=r[r[i]];	
		}	
	}	
	l[0]=0;
	for (int i=1;i<n;i++)
	{
		l[i]=i-1;
		while (l[i]>0&&b[i]>=b[l[i]])
			l[i]=l[l[i]];
	}
	long long ans=0;
	for (int i=0;i<n;i++)
	{
		ans+=s[i];
		if (b[i]<b[0])
		{
			if (l[i]==0&&r[i]==n)
				ans+=1;
			else
				ans+=2;
		}
	}
	cout<<ans<<endl;
	return 0;
}