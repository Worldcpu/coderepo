#include<bits/stdc++.h>
#define mp make_pair
#define il inline
using namespace std;
const int mod=998244353;
const int maxn=1000010;
il int read(){
	int x=0;
	char c=getchar();
	for(;!(c>='0'&&c<='9');c=getchar());
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0';
	return x;
}
il void chkmax(int &x,int y){if(y>x)x=y;}
il void chkmin(int &x,int y){if(y<x)x=y;}
il void ad(int &x,int y){if((x+=y)>=mod)x-=mod;}
il void de(int &x,int y){if((x-=y)<0)x+=mod;}
il void mul(int &x,int y){x=1ll*x*y%mod;}
int n,top[2],f[maxn];
int a[maxn],ok[maxn];
int tap1[maxn],tap2[maxn];
pair<int,int>st[2][maxn];
set<int>s;
void clear(int l,int r){
	for(int i=l;i<=r;i++) 
		tap1[a[i]]=tap2[a[i]]=0;
}
int ef(int x,int t){
	if(st[t][1].first<=x||!top[t]) return 0;
//	printf("!!!!%d,%d(%d)[%d]\n",x,st[t][1].first,top[t],t);
	int l=1,r=top[t],mid;
	while(r>l){
		mid=l+r+1>>1;
		if(st[t][mid].first>x) l=mid;
		else r=mid-1;
	}
//	printf("del : %d(%d)\n",st[t][l].second,l);
	return st[t][l].second;
}
void cdq(int l,int r){
	if(l==r) return ad(f[l],ok[l]);
	cdq(l,l+r>>1);
//	printf("%d,%d\n",l,r);
	int mid=l+r>>1,sum[2]={0,0};
	for(int i=l;i<=mid;i++) ad(sum[i&1],f[i]);
	for(int i=mid+1;i<=r;i++) ad(f[i],sum[i&1]);
	for(int i=mid;i>=l;i--)
		if(2*(++tap1[a[i]])>mid-i+1) s.insert(a[i]);
	for(int i=mid+1;i<=r;i++)
		if(2*(++tap2[a[i]])>i-mid) s.insert(a[i]);
	while(!s.empty()){
//		printf("now_num = %d\n",*s.begin());
//		for(int i=l;i<=mid;i++) printf("[[%d]] ",f[i]);
//		printf("\n");
		int x=*s.begin(); 
		s.erase(s.begin());
		top[0]=top[1]=0;
		st[mid&1][++top[mid&1]]=mp(0,f[mid]); 
		for(int i=mid,v=0;i>l;i--)
			v+=2*(a[i]==x)-1,st[i&1^1][++top[i&1^1]]=mp(v,f[i-1]);
		sort(st[0]+1,st[0]+1+top[0],greater<pair<int,int> >());
		sort(st[1]+1,st[1]+1+top[1],greater<pair<int,int> >());
		for(int i=1;i<=top[0];i++)
			ad(st[0][i].second,st[0][i-1].second);
		for(int i=1;i<=top[1];i++)
			ad(st[1][i].second,st[1][i-1].second);
		for(int i=mid+1,v=0;i<=r;i++)
			de(f[i],ef(v+=1-2*(a[i]==x),i&1));
	}
	clear(l,r),cdq(mid+1,r);
}
int main(){
	n=read()*2;
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1,Mx=0;i<=n;i++)
		chkmax(Mx,++tap1[a[i]]),ok[i]=(2*Mx<=i&&(i&1^1));
	memset(tap1,0,sizeof(tap1));
	cdq(1,n),printf("%d\n",f[n]);
//	for(int i=1;i<=n;i++)
//		printf("%d ",f[i]);
//	printf("\n");
	return 0;
} 
