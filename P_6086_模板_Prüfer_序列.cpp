#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e6+15;
int fa[MN],dg[MN],p[MN],n,m,ans;

void TtoP(){
    for(int i=1;i<n;i++){
        cin>>fa[i];
        dg[fa[i]]++;
    }
    for(int i=1,x,j=1;i<=n-2;i++,j++){
        while(dg[j]) j++;
        p[i]=fa[x=j];
        while(i<=n-2&&!--dg[p[i]]&&p[i]<j){
            p[++i]=fa[x=fa[x]];
        }
    }
    for(int i=1;i<=n-2;i++){
        ans^=1ll*i*p[i];
    }
}

void PtoT(){
    for(int i=1;i<=n-2;i++){
        cin>>p[i];
        dg[p[i]]++;
        p[n-1]=n;
    }
    for(int i=1,x,j=1;i<=n-1;i++,j++){
        while(dg[j]) j++;
        fa[x=j]=p[i];
        while(i<=n-1&&!--dg[p[i]]&&p[i]<j) fa[x=fa[x]]=p[++i];
    }
    for(int i=1;i<=n-1;i++){
        ans^=1ll*i*fa[i];
    }
}

signed main(){
    cin>>n>>m;
    if(m==1){
        TtoP();
    }else PtoT();
    cout<<ans;
    return 0;
}