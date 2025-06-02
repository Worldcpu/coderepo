#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=250,INF=1e18;
struct Edge{
    int u,v,d;
}e[MN];
int n,m,ans,dis[MN];

struct Matrix{
    bitset<MN> mat[MN];

    Matrix(int x=0){
        for(int i=0;i<MN;i++){
            for(int j=0;j<MN;j++){
                mat[i][j]=0;
            }
        }
        if(!x) return;
        for(int i=0;i<MN;i++) mat[i][i]=x;
    }

    Matrix operator*(const Matrix &x)const{
        Matrix ret;
        for(int i=0;i<MN;i++){
            for(int k=0;k<MN;k++){
                if(mat[i][k]){
                    ret.mat[i]|=x.mat[k];
                }
            }
        }
        return ret;
    }

}a,G;

Matrix ksm(Matrix a,int b){
    Matrix ret(1);
    while(b>0){
        if(b&1) ret=ret*a;
        a=a*a;
        b>>=1;
    }
    return ret;
}

bool cmp(Edge x,Edge y){
    return x.d<y.d;
}

void bfs(){
    for(int i=1;i<=n;i++) dis[i]=INF;
    queue<int> q;
    for(int i=1;i<=n;i++){
        if(a.mat[1][i]) q.push(i),dis[i]=0;
    }
    while(!q.empty()){
        int f=q.front();
        cerr<<f<<'\n';
        q.pop();
        for(int i=1;i<=n;i++){
            if(G.mat[f][i]&&dis[i]==INF){
                dis[i]=dis[f]+1;
                q.push(i);
            }
        }
    }
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>e[i].u>>e[i].v>>e[i].d;
    }
    sort(e+1,e+1+m,cmp);
    a.mat[1][1]=1,ans=INF,dis[n]=INF;
    for(int i=1,lst=0;i<=m;i++){
        if(ans<e[i].d) break;
        int dt=e[i].d-lst;
        lst=e[i].d;
        a=a*ksm(G,dt);
        G.mat[e[i].u][e[i].v]=1;
        if(i==m||e[i+1].d!=e[i].d) bfs();
        ans=min(ans,lst+dis[n]);
    }
    if(ans==INF) cout<<"Impossible";
    else cout<<ans;
    return 0;
}
