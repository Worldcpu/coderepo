#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=21;
int n,m,t,sa[1<<MN],sb[1<<MN],va[1<<MN],vb[1<<MN],cnt[1<<MN],f[1<<MN],ans;
vector<int> ansa,ansb;

int lowbit(int x){
    return x&(-x);
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int qwq;
            char x;
            cin>>x;
            qwq=(x=='1');
            sa[1<<(i-1)]|=qwq<<(j-1);
            sb[1<<(j-1)]|=qwq<<(i-1);
        }
    }
    for(int i=0;i<n;i++){
        cin>>va[1<<i];
    }
    for(int i=0;i<n;i++){
        cin>>vb[1<<i];
    }
    for(int i=0;i<(1<<20);i++){
        int lb=lowbit(i);
        cnt[i]=cnt[i>>1]+(i&1);
        if(i!=lb){
            va[i]=va[i-lb]+va[lb];
            sa[i]=sa[i-lb]|sa[lb];
            vb[i]=vb[i-lb]+vb[lb];
            sb[i]=sb[i-lb]|sb[lb];
        }
    }
    for(int i=0;i<(1<<n);i++){
        f[i]=1;
        for(int j=0;j<n;j++){
            if(i>>j&1) f[i]&=f[i^(1<<j)];
        }
        f[i]&=cnt[i]<=cnt[sa[i]];
        if(f[i]) ansa.push_back(va[i]); 
    }
    for(int i=0;i<(1<<m);i++){
        f[i]=1;
        for(int j=0;j<m;j++){
            if(i>>j&1) f[i]&=f[i^(1<<j)];
        }
        f[i]&=cnt[i]<=cnt[sb[i]];
        if(f[i]) ansb.push_back(vb[i]); 
    }
    cin>>t;
    sort(ansb.begin(),ansb.end());
    cerr<<ansa.size()<<' '<<ansb.size()<<'\n';
    for(auto p:ansa){
        cerr<<p<<' ';
    }
    cerr<<'\n';
    for(auto p:ansb) cerr<<p<<' ';
    for(auto p:ansa){
        ans+=ansb.end()-lower_bound(ansb.begin(),ansb.end(),t-p);
    }
    cout<<ans;

    

    return 0;
}