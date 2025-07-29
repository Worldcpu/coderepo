#include<bits/stdc++.h>
#include <random>
#define int long long
using namespace std;
constexpr int MK=66,MN=1e5+15,MOD=1e9+7;
int n,m,K,top,in[MN],tim[MN],st[MN],ans[MN];
vector<int> adj[MN];
mt19937 mt;

struct Vector{
    int v[MK];

    friend Vector operator + (const Vector &x,const Vector &y){
        Vector ret;
        for(int i=1;i<=K;i++){
            ret.v[i]=(x.v[i]+y.v[i])%MOD;
        }
        return ret;
    }

    friend Vector operator - (const Vector &x,const Vector &y){
        Vector ret;
        for(int i=1;i<=K;i++){
            ret.v[i]=(x.v[i]-y.v[i]+MOD)%MOD;
        }
        return ret;
    }

    friend Vector operator * (const Vector &x,int y){
        Vector ret;
        for(int i=1;i<=K;i++){
            ret.v[i]=x.v[i]*y%MOD;
        }
        return ret;
    }
}vt[MN],p[MN];

int ksm(int a,int b){
    int ret=1;
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
    for(int i=1;i<=K;i++){
        vt[i].v[i]=1;
    }
    for(int i=1;i<=n;i++){
        if(!in[i]){
            q.push(i);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto v:adj[u]){
            in[v]--;
            vt[v]=vt[v]+vt[u]*gen();
            if(!in[v]){
                q.push(v);
            }
        }
    }
}

void insert(int pos){
    auto x=vt[pos];
    for(int i=1;i<=K;i++){
        if(x.v[i]){
            if(!tim[i]){
                p[i]=x;
                tim[i]=pos;
                break;
            }
            if(tim[i]<pos){
                swap(tim[i],pos);
                swap(x,p[i]);
            }
            x=x-p[i]*(ksm(p[i].v[i],MOD-2)*x.v[i]%MOD);
        }
    }
}

signed main(){
    mt.seed(time(0));
    cin>>n>>m>>K;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        in[v]++;
        adj[u].push_back(v);
    }
    toposort();
    for(int i=K+1;i<=n;i++){
        insert(i);
        top=0;
        for(int j=1;j<=K;j++){
            if(tim[j]) st[++top]=tim[j];
        }
        sort(st+1,st+1+top);
        st[top+1]=i;
        st[0]=K;
        for(int j=0;j<=top;j++){
            ans[top-j]+=st[j+1]-st[j];
        }
    }
    for(int i=0;i<=K;i++) cout<<ans[i]<<'\n';
    

    return 0;
}