#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=5520+15,mod=1e9;
int n,m,K,top,cnt;
bool vis[MN][MN];
int st[MN];
string s,t;

struct Seq{
    vector<int> nxt[MN];

    int gnxt(int i,int c){
        auto ret=lower_bound(nxt[c].begin(),nxt[c].end(),i+1);
        if(ret==nxt[c].end()) return 0;
        return *ret;
    }

}sq[2];

struct Big{//压位结构体 
    int cur;
    ll *s;
    void init(){
        s=new long long[20];
        for(int i=0;i<20;i++) s[i]=0;
        cur=0;
    }
    void put(){
        printf("%lld",s[cur]);
        for(int i=cur-1;i>=0;i--) printf("%09lld",s[i]);
    }
    void add(ll k){
        s[0]+=k;
        int i=0;
        while(s[i]>=mod) s[i+1]+=s[i]/mod,s[i++]%=mod;
        while(s[cur+1]) cur++;
    }
    void Add(const Big& o){
        ll i,r=max(cur,o.cur);
        for(int i=0;i<=r;i++){
            s[i]+=o.s[i];
            if(s[i]>=mod) s[i+1]+=s[i]/mod,s[i]%=mod;
        }
        cur=min(r+3,19ll);while(cur&&s[cur]==0) cur--;
    }
}f[MN][MN];

void dfs(int x,int y){
    if(K){
        for(int i=1;i<=top;i++) cout<<(char)(st[i]+65);
        cout<<'\n';
    }
    for(int i=0;i<52;i++){
        if(sq[0].gnxt(x,i)&&sq[1].gnxt(y,i)){
            st[++top]=i;
            dfs(sq[0].gnxt(x,i),sq[1].gnxt(y,i));
            --top;
        }
    }
}

void solve(int x,int y){
    if(vis[x][y]) return;
    vis[x][y]=1;
    f[x][y].init();
    f[x][y].add(1);
    for(int i=0;i<52;i++){
        if(sq[0].gnxt(x,i)&&sq[1].gnxt(y,i)){
            solve(sq[0].gnxt(x,i),sq[1].gnxt(y,i));
            f[x][y].Add(f[sq[0].gnxt(x,i)][sq[1].gnxt(y,i)]);
        }
    }
}

int main(){
    cin>>n>>m>>s>>t;
    s=" "+s,t=" "+t;
    for(int i=1;i<=n;i++){
        int k=s[i]-'A';
        sq[0].nxt[k].push_back(i);
    }
    for(int i=1;i<=m;i++){
        int k=t[i]-'A';
        sq[1].nxt[k].push_back(i);
    }
    cin>>K;
    if(K){
        dfs(0,0);
    }
    solve(0,0);
    f[0][0].put();
    return 0;
}