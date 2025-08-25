#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15,MK=520+15;
int n,x,y,mxdep,ptot,pos[MN],cnt[MN],cntt[MN],f[MK][MN];
char ans[MN];
vector<int> adj[MN],posd[MN];

namespace Tree{
    int dep[MN];
    bool hson[MN];

    void dfs1(int u,int pre){
        dep[u]=dep[pre]+1;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
            hson[u]=1;
        }
    }

}using namespace Tree;

void solvea(int p,int x){
    if(!p) return;
    cntt[pos[p]]=cnt[pos[p]]-f[p][x];
    solvea(p-1,x-cntt[pos[p]]*pos[p]);
}

int main(){
    cin>>n>>x;
    y=n-x;
    for(int i=2;i<=n;i++){
        int fa;
        cin>>fa;
        adj[fa].push_back(i);
        adj[i].push_back(fa);
    }
    dfs1(1,0);
    for(int i=1;i<=n;i++){
        posd[dep[i]].push_back(i);
        mxdep=max(mxdep,dep[i]);
    }
    for(int i=1;i<=mxdep;i++){
        cnt[posd[i].size()]++;
    }
    memset(f,-1,sizeof(f));
    f[0][0]=0;
    for(int i=1;i<=n;i++){
        if(!cnt[i]) continue;
        pos[++ptot]=i;
        for(int j=0;j<=n;j++){
            if(f[ptot-1][j]>=0) f[ptot][j]=cnt[i];
            if(j>=i) f[ptot][j]=max(f[ptot][j],f[ptot][j-i]-1);
        }
    }
    if(f[ptot][x]>=0){
        solvea(ptot,x);
        for(int i=1;i<=n;i++){
            ans[i]='b';
        }
        for(int i=1;i<=mxdep;i++){
            if(cntt[posd[i].size()]){
                cntt[posd[i].size()]--;
                for(auto p:posd[i]) ans[p]='a';
            }
        }
        cout<<mxdep<<'\n';
        for(int i=1;i<=n;i++){
            cout<<ans[i];
        }
    }
    else{
        cout<<mxdep+1<<'\n';
        for(int i=1;i<=mxdep;i++){
            int len=posd[i].size();
            if(len<=x){
                for(auto p:posd[i]) ans[p]='a';
                x-=len;
            }else if(len<=y){
                for(auto p:posd[i]) ans[p]='b';
                y-=len;
            }else if(x>y){
                for(auto p:posd[i]){
                    if(hson[p]) ans[p]='a',x--;
                }
                for(auto p:posd[i]){
                    if(!ans[p]&&x) ans[p]='a',x--;
                }
                for(auto p:posd[i]) if(!ans[p]) ans[p]='b',y--;
            }else{
                for(auto p:posd[i]){
                    if(hson[p]) ans[p]='b',y--;
                }
                for(auto p:posd[i]){
                    if(!ans[p]&&y) ans[p]='b',y--;
                }
                for(auto p:posd[i]) if(!ans[p]) ans[p]='a',x--;
            }
        }
        for(int i=1;i<=n;i++) cout<<ans[i];
    }
    return 0;
}