#include<bits/stdc++.h>
#define ll long long
#define lowbit(x) ((x)&(-x))
using namespace std;
const int MN=1e3+15,MOD=1e9+7;
int T,n,m,p;
ll f[MN][MN],t[MN],a[MN],b[MN];
void add(int x,ll k){
    while (x<=n)
    {
        t[x]+=k;
        t[x]%=MOD;
        x+=lowbit(x);
    }
}

ll query(int x){
    ll ret=0;
    while (x)
    {
        ret+=t[x];
        ret%=MOD;
        x-=lowbit(x);
    }
    return ret;
}

void solve(){
    memset(f,0,sizeof(f));
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        b[i]=a[i];
    }
    sort(b+1,b+1+n);
    p=unique(b+1,b+1+n)-b-1;
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(b+1,b+1+p,a[i])-b+1;
    }
    for(int i=1;i<=m;i++){
        memset(t,0,sizeof(t));
        if(i==1) add(1,1);
        for(int j=1;j<=n;j++){
            f[i][j]=query(a[j]-1);
            add(a[j],f[i-1][j]);
        }
    }
    ll ans=0;
    for(int i=1;i<=n;i++){
        ans=(ans+f[m][i])%MOD;
    }
    cout<<ans<<'\n';
}

int main(){
    cin>>T;
    int cnt=0;
    while (T--)
    {
        cout<<"Case #"<<++cnt<<": ";
        solve();
    }
    
    return 0;
}