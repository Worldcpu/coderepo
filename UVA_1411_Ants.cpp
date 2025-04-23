#include<bits/stdc++.h>
using namespace std;
constexpr int MN=150;
constexpr double eps=1e-7,INF=1e9;
double wx[MN],wy[MN],upd[MN],bx[MN],by[MN],la[MN],lb[MN];
double dis[MN][MN];
bool va[MN],vb[MN];
int match[MN],n;
double getdis(int x,int y){
    return sqrt((double)(wx[x]-bx[y])*(wx[x]-bx[y])+(wy[x]-by[y])*(wy[x]-by[y]));
}

bool dfs(int u){
    va[u]=1;
    for(int i=1;i<=n;i++){
        if(!vb[i]){
            if(fabs(la[u]+lb[i]-dis[u][i])<=eps){
                vb[i]=1;
                if(!match[i]||dfs(match[i])){
                    match[i]=u;
                    return 1;
                }
            }else upd[i]=min(upd[i],la[u]+lb[i]-dis[u][i]);
        }
    }
    return 0;
}

void km(){
    double delta=0;
    for(int i=1;i<=n;i++){
        la[i]=-INF,lb[i]=0;
        for(int j=1;j<=n;j++){
            la[i]=max(la[i],dis[i][j]);
        }
    }
    for(int i=1;i<=n;i++){
        while(1){
            
            memset(va,0,sizeof(va));
            memset(vb,0,sizeof(vb));
            for(int j=1;j<=n;j++){
                upd[j]=INF;
            }
            if(dfs(i)) break;
            delta=INF;
            for(int j=1;j<=n;j++){
                if(!vb[j]) delta=min(delta,upd[j]);
            }
            for(int j=1;j<=n;j++){
                if(va[j]) la[j]-=delta;
                if(vb[j]) lb[j]+=delta;
            }
        }
    }
}

int main(){
    while(cin>>n){
        memset(dis,0,sizeof(dis));
        memset(match,0,sizeof(match));
        for(int i=1;i<=n;i++){
            cin>>bx[i]>>by[i];
        }
        for(int i=1;i<=n;i++){
            cin>>wx[i]>>wy[i];
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                dis[i][j]=-getdis(i,j);
            }
        }
        km();
        for(int i=1;i<=n;i++) cout<<match[i]<<'\n';
    }
    return 0;
}