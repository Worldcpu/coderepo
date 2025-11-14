#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5200;
int f[MN][MN],n,K,m,p[MN],st[MN],top,ans;
vector<int> pos[MN];
bool vis[MN];

int main(){
    cin>>n>>K;
    m=n*K;
    for(int i=1;i<=m;i++){
        cin>>p[i];
    }
    for(int i=1;i<=m;i++){
        if(vis[i]) continue;
        int now=i;
        top=0;
        while(!vis[now]){
            vis[now]=1;
            st[++top]=now;
            now=p[now];
        }
        if(top==1) continue;
        for(int j=0;j<n;j++){
            pos[j].clear();
        }
        for(int j=1;j<=top;j++){
            pos[st[j]%n].push_back(j);
        }
        memset(f,128,sizeof(f));
        for(int j=1;j<=top;j++) f[j][j]=0;
        for(int l=top;l>=1;l--){
            for(int r=l+1;r<=top;r++){
                f[l][r]=max(f[l+1][r],f[l][r-1]);
                for(auto p:pos[p[l]%n]){
                    if(p<=l||p>r) continue;
                    f[l][r]=max(f[l][p-1]+f[p][r]+1,f[l][r]);
                }
            }
        }
        ans+=f[1][top];       
    }
    cout<<ans;
    

    return 0;
}