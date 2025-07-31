#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=8e5+15;
int n,a[MN],b[MN],c[MN],ans;
bool vis[MN];
priority_queue<pir> q1,q2,q3;

signed main(){
    freopen("team.in","r",stdin);
    freopen("team.out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i]>>c[i];
        q1.push(pir(a[i],i));
        q2.push(pir(b[i],i));
        q3.push(pir(c[i],i));
    }
    for(int i=1;i<=n;i++){
        int q1t=q1.top().second,q2t=q2.top().second,q3t=q3.top().second;
        if(b[q1t]==b[q2t]||c[q1t]==c[q3t]) vis[q1t]=1;
        if(a[q2t]==a[q1t]||c[q2t]==c[q3t]) vis[q2t]=1;
        if(a[q3t]==a[q1t]||b[q3t]==b[q2t]) vis[q3t]=1;
        if(!vis[q1t]&&!vis[q2t]&&!vis[q3t]){
            cout<<a[q1t]+b[q2t]+c[q3t];
            return 0;
        }
        while(vis[q1.top().second]){
            q1.pop();
            if(q1.empty()){
                goto qwq;
            }
        }
        while(vis[q2.top().second]){
            q2.pop();
            if(q2.empty()){
                goto qwq;
            }
        }
        while(vis[q3.top().second]){
            q3.pop();
            if(q3.empty()){
                goto qwq;
            }
        }
    }
qwq:
    for(int i=1;i<=n;i++) cerr<<vis[i]<<" ";
    cout<<-1;

    return 0;
}