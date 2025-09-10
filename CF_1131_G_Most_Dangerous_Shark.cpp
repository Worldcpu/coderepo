#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=1e7+15,MK=5e5+15;
int n,m,q,L[MN],R[MN],dtot,st[MN],top;
ll f[MN],g[MN],h[MN],w[MN];
vector<ll> a[MK],c[MK];

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int k;
        cin>>k;
        for(int j=1;j<=k;j++){
            int x;
            cin>>x;
            a[i].push_back(x);
        }
        for(int j=1;j<=k;j++){
            int x;
            cin>>x;
            c[i].push_back(x);
        }
    }
    cin>>q;
    for(int i=1;i<=q;i++){
        int id,mul;
        cin>>id>>mul;
        for(int i=0;i<a[id].size();i++){
            h[++dtot]=a[id][i];
            w[dtot]=c[id][i]*mul;
        }
    }
    top=0;
    for(int i=1;i<=dtot;i++){
        while(top&&i-h[i]<=st[top]-h[st[top]]){
            top--;
        }
        if(!top||i-h[i]>=st[top]){
            L[i]=max(i-h[i]+1,1ll);
        }else L[i]=L[st[top]];
        st[++top]=i;
    } 
    top=0;
    for(int i=dtot;i>=1;i--){
        while(top&&i+h[i]>=st[top]+h[st[top]]){
            top--;
        }
        if(!top||i+h[i]<=st[top]){
            R[i]=min(i+h[i]-1,(ll)m);
        }else R[i]=R[st[top]];
        st[++top]=i;
    }
    top=0;
    g[0]=1e18;
    for(int i=1;i<=dtot;i++){
        while(top&&R[st[top]]==i-1) top--;
        f[i]=f[L[i]-1]+w[i];
        if(top) f[i]=min(f[i],g[top]);
        st[++top]=i;
        g[top]=min(g[top-1],f[i-1]+w[i]);
    }
    cout<<f[dtot];
    return 0;
}