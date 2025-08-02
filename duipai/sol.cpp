#include <bits/stdc++.h>
#define inl inline
#define rg register
#define R rg int
using namespace std;
inl int Get(char c){
    return (c>='a'&&c<='z')?c-'a':(26+c-'A');
}
constexpr int N=305,M=N*5+2;
// ACAM
int ch[M][52],fail[M],ban[M],cnt=1;
void ins(char *s,int len,int v){
    int u=1;
    for(R i=0;i<len;i++){
        R c=Get(s[i]);
        if(!ch[u][c])ch[u][c]=++cnt;
        u=ch[u][c];
    }
    ban[u]|=v;
}
void bfs(){
    for(R i=0;i<52;i++)ch[0][i]=1;
    queue<int>q;q.push(1);
    while(!q.empty()){
        int u=q.front();q.pop();ban[u]|=ban[fail[u]];
        for(R i=0;i<52;i++)
            if(!ch[u][i])ch[u][i]=ch[fail[u]][i];
            else fail[ch[u][i]]=ch[fail[u]][i],q.push(ch[u][i]);
    }
}
// 子序列自动机
int ch1[N][52],ch2[N][52];
void build(char* s,char* r,R n,R m){
    for(R i=n;i;i--)
        memcpy(ch1[i],ch1[i+1],sizeof ch1[i]),
        ch1[i][Get(s[i])]=i+1;
    for(R i=m;i;i--)
        memcpy(ch2[i],ch2[i+1],sizeof ch2[i]),
        ch2[i][Get(r[i])]=i+1;
}
// sol
int n,m,K;
struct node{
    int x,y,z,Ban;
    bool operator < (const node &b)const{
        if(x^b.x)return x<b.x;
        if(y^b.y)return y<b.y;
        if(z^b.z)return z<b.z;
        return Ban<b.Ban;
    }
};
map<node,int>mp;
int sol(R x,R y,R z,R vis){
    if(mp.count({x,y,z,vis}))return mp[{x,y,z,vis}];
    int ans=-1e9;if(vis==(1<<K)-1)ans=0;
    for(R i=0;i<52;i++){
        int nx=ch1[x][i],ny=ch2[y][i],nz=ch[z][i],nv=vis|ban[nz];
        if(!nx||!ny)continue; ans=max(ans,sol(nx,ny,nz,nv)+1);
    }
    return mp[{x,y,z,vis}]=ans;
}
char buf[N],Buf[N];int length[N];
int main(){
    scanf("%d %d %d",&n,&m,&K);
    for(R i=1;i<=K;i++)scanf("%d",&length[i]);
    scanf(" %s %s",buf+1,Buf+1);build(buf,Buf,n,m);
    for(R i=1;i<=K;i++)scanf(" %s",buf),ins(buf,length[i],1<<i-1);
    bfs();
    cout<<sol(1,1,1,0);
    return 0;
}