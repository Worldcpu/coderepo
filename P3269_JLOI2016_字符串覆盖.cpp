#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e4+15,MK=5,INF=1e18;
int n,ans1,ans2,top,f[MN][MK],lens,len[MN],id[MN],pre[MK][MN],nxt[MK][MN],fail[MN];
int *pr[MK],*nx[MK],le[MK];
bool mark[MN],*st[MN*MK],vis[MN][MK];
string s;

void getfail(string &q){
	int m=q.length()-1;
	for(int i=2,j=0;i<=m;++i){
		while(j&&q[j+1]!=q[i]) j=fail[j];
		if(q[j+1]==q[i]) ++j;
		fail[i]=j;
	}
}

void getpn(int *pre,int *nxt,string &t,int lent){
	memset(mark,0,sizeof(mark));
	getfail(t);
	int m=lent;
	for(int i=1,j=0;i<=lens;++i){
		while(j&&t[j+1]!=s[i]) j=fail[j];
		if(t[j+1]==s[i]) ++j;
		if(j==m) mark[i-m+1]=1,j=fail[j];
	}
	pre[0]=0;
	for(int i=1;i<=lens;++i) pre[i]=mark[i]?i:pre[i-1];
	pre[lens+1]=pre[lens];
	nxt[lens+1]=0;
	for(int i=lens;i>=1;--i){
		if(mark[i]) nxt[i]=i;
		else nxt[i]=nxt[i+1];
		mark[i]=0;
	}
}

int solve1(int x,int y){
	if(y>n) return 0;
	x=nx[y][x];
	if(!x) return INF;
	int &ans=f[x][y];
	if(*(st[top+1]=&vis[x][y])) return ans;
	*st[++top]=1;
	ans=solve1(x+1,y);
	int lst=x+le[y],now=x;
	int tmpy=y;
	while((++y)<=n){
		ans=min(ans,solve1(lst,y)+lst-x);
		int nxtt=nx[y][x];
		if(nxtt<now||nxtt>=lst) return ans;
		now=nxtt;
		lst=max(lst,nxtt+le[y]);
	}
	ans=min(ans,lst-x);
	return ans;
}

int solve2(int x,int y){
	if(y>n) return 0;
	x=nx[y][x];
	if(!x) return -INF;
	int lst=x+le[y],now=x;
	int ans=-INF;
	int tmpy=y;
	while((++y)<=n){
		ans=max(ans,solve2(lst,y)+lst-x);	
        int nxtt=pr[y][lst];
		if(nxtt<now||nxtt>=lst) return ans;
		now=nxtt;
		lst=max(lst,nxtt+le[y]);
	}
	ans=max(ans,lst-x);
	return ans;
}

void init(){
	ans1=INF, ans2=0, top=0;
	memset(f,0,sizeof(f));
	memset(vis,0,sizeof(vis));
}

void solve(){
	init();
	cin>>s;
	lens=s.length();
	s=" "+s;
	cin>>n;
	for(int i=1;i<=n;i++){
		string t;
		cin>>t;
		len[i]=t.length();
		le[i]=len[i];
		t=" "+t;
		getpn(pre[i],nxt[i],t,len[i]);
	}
	for(int i=1;i<=n;i++) id[i]=i;
	do{
		for(int i=1;i<=n;i++){
			pr[i]=pre[id[i]];
			nx[i]=nxt[id[i]];
			le[i]=len[id[i]];
		}
		ans1=min(ans1,solve1(1,1));
		while(top) *st[top--]=0;
		ans2=max(ans2,solve2(1,1));
	}while(next_permutation(id+1,id+1+n));
	cout<<ans1<<' '<<ans2<<'\n';
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin>>T;
	while(T--) solve();
	return 0;
}
