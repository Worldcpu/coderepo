#include<bits/stdc++.h>
#define True -1
#define False -2
#define Unknown -3
using namespace std;
constexpr int MN=5e5+15;
int n,m,mp[MN],w[MN],ans;

namespace DSU{
    int pre[MN],siz[MN];

    void initpre(){
        iota(pre+1,pre+1+n,1);
        fill(siz+1,siz+1+n,1);
    }

    int root(int x){
        if(pre[x]==x) return pre[x];
        else return pre[x]=root(pre[x]);
    }

    // merge x-> y
    void merge(int x,int y){
        int rx=root(x),ry=root(y);
        if(rx==ry) return;
        siz[ry]+=siz[rx];
        pre[rx]=ry;
    }
}using namespace DSU;

int dfs(int u,int rt,int col){
    if(mp[u]/2==rt){
        return col^(mp[u]&1);
    }else return dfs(mp[u]/2,rt,col^(mp[u]&1));
}

int flip(int x){
	if(x==True) return False;
	if(x==False) return True;
	if(x==Unknown) return Unknown;
	return x^1;
}

void init(){
    initpre();
    for(int i=1;i<=n;i++){
        mp[i]=i*2;
    }
    ans=0;
}

void solve(){
    cin>>n>>m;
    init();
    for(int i=1;i<=m;i++){
        int x,y;
        char op;
        cin>>op;
        if(op=='+'){
            cin>>x>>y; 
            mp[x]=mp[y];
        }else if(op=='-'){
            cin>>x>>y;
            mp[x]=flip(mp[y]);
        }else{
            cin>>x;
            if(op=='T'){
                mp[x]=True;
            }else if(op=='F'){
                mp[x]=False;
            }else{
                mp[x]=Unknown;
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(mp[i]>0){
            merge(i,mp[i]/2);
        }
    }
    for(int i=1;i<=n;i++){
        if(i==root(i)){
            if(mp[i]==Unknown||(mp[i]>0&&dfs(i,i,0))){
                ans+=siz[i];
            }
        }
    }
    cout<<ans<<'\n';
}

int main(){
    int c,T;
    cin>>c>>T;
    while(T--){
        solve();
    }
    return 0;
}