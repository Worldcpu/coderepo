#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e4,INF=0x3f3f3f3f;
int n,b[MN],g[MN],f[MN],len=1,pre[MN],sump[MN],sumb[MN];
vector<int> p[MN];

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        b[i]=x-i;
    }
    b[n+1]=INF;
    pre[1]=1;
    g[1]=b[1];
    p[1].push_back(1);
    for(int i=2;i<=n+1;i++){
        if(g[len]<=b[i]){
            g[++len]=b[i];
            pre[i]=len;
            p[len].push_back(i);
        }else{
            int pos=upper_bound(g+1,g+1+len,b[i])-g;
            g[pos]=b[i];
            pre[i]=pos;
            p[pos].push_back(i);
        }
    }
    cout<<n-len+1<<'\n';
    b[0]=-INF,b[n+1]=INF;
    p[0].push_back(0);
    memset(f,INF,sizeof(f));
    f[0]=0;
    for(int i=1;i<=n+1;i++){
        for(auto j:p[pre[i]-1]){
            if(j>i||b[j]>b[i]) continue;
            sump[j]=0;
            for(int k=j+1;k<i;k++){
                sump[k]=sump[k-1]+abs(b[k]-b[j]);
            }
            sumb[i-1]=0;
            for(int k=i-2;k>=j;k--){
                sumb[k]=sumb[k+1]+abs(b[k+1]-b[i]);
            }
            for(int k=j;k<i;k++){
                f[i]=min(f[i],f[j]+sump[k]+sumb[k]);
            }
        }
    }
    cout<<f[n+1];
    return 0;
}
