#include<bits/stdc++.h>
using namespace std;
constexpr int MN=520+15;
int n,m,p[MN],op[MN][2],dis[MN][MN];
vector<int> s,anss;

int geth(){
    int cnt=0;
    for(int i=1;i<=n;i++) cnt+=dis[i][p[i]];
    return cnt;
}

bool dfs(int preop,int dep,int mdep){
    int h=geth();
    if(!h){
        anss=s;
        return 1;
    }
    if(2*dep+h>2*mdep) return 0;
    for(int i=1;i<=m;i++){
        if(preop!=i){
            swap(p[op[i][0]],p[op[i][1]]);
            s.push_back(i);
            if(dfs(i,dep+1,mdep)) return 1;
            s.pop_back();
            swap(p[op[i][0]],p[op[i][1]]);
        }
    }
    return 0;
}

int main(){
    cin>>n>>m;
    memset(dis,0x3f,sizeof(dis));
    for(int i=1;i<=n;i++){
        cin>>p[i];
        dis[i][i]=0;
    }
    for(int i=1;i<=m;i++){
        cin>>op[i][0]>>op[i][1];
        dis[op[i][0]][op[i][1]]=dis[op[i][1]][op[i][0]]=min(dis[op[i][1]][op[i][0]],1);
    }
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
            }
        }
    }
    for(int i=0;i<=30;i++){
        if(dfs(-1,0,i)){
            cout<<i<<'\n';
            for(auto c:anss) cout<<c<<'\n';
            return 0;
        }
    }
    cout<<"NEMA";
    return 0;
}
