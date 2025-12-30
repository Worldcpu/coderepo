#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=2e6+15,INF=1e18;
int n,c[MN],v[MN],f[MN],cnt[MN],top,pre[MN],ans=INF;
pir st[MN];
bool vis[MN];

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>c[i];
        if(!vis[c[i]]) pre[c[i]]=i,vis[c[i]]=1;
    }
    for(int i=1;i<=n;i++){
        cin>>v[i];
    }
    for(int i=1;i<=n;i++){
        cin>>f[i];
    }

    for(int i=1;i<=n;i++){
        cnt[c[i]]++;
    }
    for(int i=1;i<=n;i++){
        cnt[c[i]]--;
        int lstc=-1,L=-1;
        while(top&&cnt[st[top].second]==0){
            auto tp=st[top--];
            L=tp.first;
            lstc=tp.second;
        }
        st[++top]=pir(i,c[i]);
        if(lstc!=-1&&pre[lstc]==L){
            int res=0;
            for(int j=L;j<=i;j++){
                res+=v[j]*f[j-L+1];
            }
            ans=min(ans,res);
        }
    }
    cout<<ans<<'\n';
    return 0;
}