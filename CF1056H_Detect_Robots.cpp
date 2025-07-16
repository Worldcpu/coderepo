#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e6+15;
int T,n,m,B,pos[MN],vis[MN];
vector<int> a[MN];
vector<pir> v[MN];

void solve(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        v[i].clear();
        vis[i]=pos[i]=0;
    }
    for(int i=1;i<=m;i++){
        a[i].clear();
        int K;
        cin>>K;
        for(int j=1;j<=K;j++){
            int x;
            cin>>x;
            a[i].push_back(x);
        }
        if(a[i].size()<=B){
            for(int j=0;j<a[i].size();j++){
                for(int k=j+1;k<a[i].size();k++){
                    v[a[i][k]].push_back(pir(a[i][j],a[i][j+1]));
                }
            }
        }
    }
    for(int i=1;i<=m;i++){
        if(a[i].size()<=B) continue;
        for(int j=1;j<=n;j++) pos[j]=-1;
        for(int j=0;j<a[i].size();j++) pos[a[i][j]]=j;
        for(int j=i+1;j<=m;j++){
            int r=-1;
            for(int k=a[j].size()-1;k>=0;k--){
                if(pos[a[j][k]]==-1) continue;
                if(pos[a[j][k]]>r){
                    r=pos[a[j][k]];
                }
                else if(a[j][k+1]!=a[i][pos[a[j][k]]+1]){
                    cout<<"Human\n";
                    return;
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(auto p:v[i]){
            if(vis[p.first]&&vis[p.first]!=p.second){
                cout<<"Human\n";
                return;
            }
            vis[p.first]=p.second;
        }
        for(auto p:v[i]) vis[p.first]=0;
    }
    cout<<"Robot\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    B=sqrt(300000)/2;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
