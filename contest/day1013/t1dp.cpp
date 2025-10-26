#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,m,lstim[MN],ttot,dtot,s[MN],t[MN],ans[MN];
vector<int> pos[MN],qry[MN];

template <typename T>void read(T &x) {
    x = 0;int f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {if (ch == '-') f = -1;ch = getchar();}
    while (isdigit(ch)) {x = x * 10 + (ch ^ 48);ch = getchar();}
    x *= f;
    return;
}

namespace DSU{
    int pre[MN],siz[MN];

    void initpre(){
        for(int i=1;i<MN;i++){
            pre[i]=i;
        }
    }

    int root(int x){
        if(pre[x]==x) return pre[x];
        else return pre[x]=root(pre[x]);
    }

    void merge(int x,int y){
        int rx=root(x),ry=root(y);
        if(rx==ry) return;
        dtot--;
        pre[rx]=ry;
    }

}using namespace DSU;

void init(){
    for(int i=1;i<=n;i++){
        s[i]=0;
    }
    for(int i=1;i<=m;i++){
        ans[i]=t[i]=0;
    }    
    for(int i=1;i<=ttot;i++){
        pos[i].clear();
        qry[i].clear();
        lstim[i]=0;
    }
    dtot=ttot=0;
    initpre();
}

void solve(){
    read(n),read(m);
    init();
    for(int i=1;i<=n;i++){
        read(s[i]);
        lstim[++ttot]=s[i];
    }
    for(int i=1;i<=m;i++){
        read(t[i]);
        lstim[++ttot]=t[i];
    }
    for(int i=1;i<=ttot;i++){
        cerr<<lstim[i]<<' ';
    }
    sort(lstim+1,lstim+1+ttot);
    cerr<<'\n';
    for(int i=1;i<=ttot;i++){
        cerr<<lstim[i]<<' ';
    }
    ttot=unique(lstim+1,lstim+1+ttot)-lstim-1;
    cerr<<'\n';
    for(int i=1;i<=ttot;i++){
        cerr<<lstim[i]<<' ';
    }

    for(int i=1;i<=n;i++){
        s[i]=lower_bound(lstim+1,lstim+1+ttot,s[i])-lstim;
        pos[s[i]].push_back(i);
    }
    for(int i=1;i<=m;i++){
        t[i]=lower_bound(lstim+1,lstim+1+ttot,t[i])-lstim;
        qry[t[i]].push_back(i);
    }
    for(int i=ttot;i>=1;i--){
        int ret=0;
        for(int j=1,flag=0;j<=n;j++){
            if(s[j]>=i){
                if(!flag) flag=1;
            }else if(flag){
                ret++;
                flag=0;
            }
        }
        for(auto p:qry[i]) ans[p]=ret;
    }
    for(int i=1;i<=m;i++) cout<<ans[i]<<' ';
    cout<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}