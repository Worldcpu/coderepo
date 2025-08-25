#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int a[MN],c[MN],n,vis[MN],mxc[MN],crc[MN],ans;


signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>c[i];
        ans+=c[i];
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            int x=i,cnt=0;
            for(;!vis[x];x=a[x]){
                vis[x]=i;
            }
            if(vis[x]==i){
                for(;vis[x]!=-1;x=a[x]){
                    vis[x]=-1;
                    cnt++;
                }
            }
            if(cnt==n){
                cout<<0;
                return 0;
            }
        }
    }
    for(int i=1;i<=n;i++){
        mxc[a[i]]=max(mxc[a[i]],c[i]);
        if(vis[i]!=-1) crc[a[i]]=max(crc[a[i]],c[i]);
    }   
    for(int i=1;i<=n;i++){
        ans-=mxc[i];
    }
    for(int i=1;i<=n;i++){
        if(vis[i]==-1){
            int minn=1e9;
            int x=i;
            for(;vis[x]==-1;x=a[x]){
                minn=min(minn,mxc[x]-crc[x]);
                vis[x]=0;
            }
            ans+=minn;
        }
    }
    cout<<ans;

    return 0;
}