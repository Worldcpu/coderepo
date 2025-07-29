#include<bits/stdc++.h>
#include <random>
using namespace std;
constexpr int MK=52,MN=1e5+15,MOD=1e9+7;
int n,m,K,in[MN];
vector<int> adj[MN];
mt19937 mt;

struct Vector{
    int v[MK];

    Vector(){
        for(int i=1;i<=K;i++) v[i]=0;
    }

    friend Vector operator + (const Vector &x,const Vector &y){
        Vector ret;
        for(int i=1;i<=K;i++){
            ret.v[i]=(1ll*x.v[i]+y.v[i])%MOD;
        }
        return ret;
    }

    friend Vector operator - (const Vector &x,const Vector &y){
        Vector ret;
        for(int i=1;i<=K;i++){
            ret.v[i]=(1ll*x.v[i]-y.v[i]+MOD)%MOD;
        }
        return ret;
    }

    friend Vector operator * (const Vector &x,int y){
        Vector ret;
        for(int i=1;i<=K;i++){
            ret.v[i]=1ll*x.v[i]*y%MOD;
        }
        return ret;
    }
}vt[MN];

struct XXJ{
    Vector p[MK];
    bool vis[MK];
    int siz;

    int ksm(long long a,int b){
        long long ret=1;
        while(b){
            if(b&1) ret=ret*a%MOD;
            a=a*a%MOD;
            b>>=1;
        }
        return ret;
    }

    void insert(Vector x){
        for(int i=1;i<=K;i++){
            if(x.v[i]){
                if(!vis[i]){
                    p[i]=x;
                    vis[i]=1;
                    siz++;
                    break;
                }
                x=x-p[i]*(1ll*ksm(p[i].v[i],MOD-2)*x.v[i]%MOD);
            }
        }

    }

}xj[MN];

    int ksm(long long a,int b){
        long long ret=1;
        while(b){
            if(b&1) ret=ret*a%MOD;
            a=a*a%MOD;
            b>>=1;
        }
        return ret;
    }

auto gen(){
    return mt()%MOD;
}

void toposort(){
    queue<int> q;
    for(auto v:adj[1]){
        Vector x;
        for(int i=1;i<=K;i++){
            x.v[i]=gen();
        }
        xj[v].insert(x);
        in[v]--;
    }
    for(int i=2;i<=n;i++){
        if(!in[i]){
            q.push(i);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vector<Vector> vc;
        for(int i=1;i<=K;i++){
            if(xj[u].vis[i]){
                vc.push_back(xj[u].p[i]);
            }
        }
        for(auto v:adj[u]){
            in[v]--;
            Vector x;
            for(auto vt:vc){
                x=x+vt*gen();
            }
            xj[v].insert(x);
            if(!in[v]){
                q.push(v);
            }
        }
    }
}

signed main(){
    mt.seed(time(0));
    cin>>n>>m>>K;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back((v));
        in[v]++;
    }
    toposort();
    for(int i=2;i<=n;i++){
        cout<<xj[i].siz<<" ";
    }
    return 0;
}