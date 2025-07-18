#include<bits/stdc++.h>
using namespace std;
constexpr int MN=3e5+15;
int n,lg[MN],f[MN],st[30][MN],p[MN];
char ans[MN];

int query(int l,int r){
    if(l>r) return 0;
    int lgg=lg[r-l+1];
    return max(st[lgg][l],st[lgg][r-(1<<lgg)+1]);
}

void getans(int x){
    if(!x) return;
    if((f[x]==f[x-1])||(f[x]==x+p[x]&&f[x-1]>=x)){
        ans[x]='R';
        return getans(x-1);
    }
    int l=0,r=x-1,ret;
    while(l<=r){
        int mid=(l+r)>>1;
        if(f[mid]>=x-p[x]-1){
            ret=mid;
            r=mid-1;
        }else l=mid+1;
    }
    for(int i=ret+1;i<x;i++) ans[i]='R';
    ans[x]='L';
    getans(ret);
}

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i];
        st[0][i]=i+p[i];
    }
    for(int i=1;i<=30;i++){
        for(int j=1;j+(1<<i)-1<=n;j++){
            st[i][j]=max(st[i-1][j],st[i-1][j+(1<<(i-1))]);
        }
    }
    for(int i=1;i<=n;i++){
        if(f[i-1]>=i) f[i]=max(f[i-1],i+p[i]);
        else f[i]=f[i-1];
        int l=0,r=i-1,ret=-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(f[mid]>=i-p[i]-1){
                ret=mid;
                r=mid-1;
            }else l=mid+1;
        }
        if(ret!=-1) f[i]=max({f[i],i-1,query(ret+1,i-1)});
    }
    if(f[n]>=n){
        cout<<"YES\n";
        getans(n);
        for(int i=1;i<=n;i++) cout<<ans[i];
        cout<<'\n';
    }else cout<<"NO\n";

}

int main(){
    for(int i=2;i<MN;i++) lg[i]=lg[i>>1]+1;
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
