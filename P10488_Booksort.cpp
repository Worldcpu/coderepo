#include<bits/stdc++.h>
using namespace std;
constexpr int MN=0+15;
int T,n,p[MN],tmp[6][MN];

int geth(){
    int ret=0;
    for(int i=1;i<n;i++){ 
        if(p[i]+1!=p[i+1]) ret++;
    }
    return (ret+2)/3;
}

bool dfs(int dep,int mdep){
    int h=geth();
    if(!h) return 1;
    if(dep+h>mdep) return 0;
    for(int len=1;len<=n;len++){
        for(int l=1;l+len-1<=n;l++){
            int r=l+len-1;
            for(int k=r+1;k<=n;k++){
                memcpy(tmp[dep],p,sizeof(p));
                int y=l ;
                for(int x=r+1;x<=k;x++,y++){
                    p[y]=tmp[dep][x];
                }
                for(int x=l;x<=r;x++,y++){
                    p[y]=tmp[dep][x];
                }
                if(dfs(dep+1,mdep)) return 1;
                memcpy(p,tmp[dep],sizeof(p));
            }
        }
    }
    return 0;
}

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i];
    }
    for(int i=0;i<=4;i++){
        if(dfs(0,i)){
            cout<<i<<'\n';
            return;
        }
    }
    cout<<"5 or more\n";
}

int main(){
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
