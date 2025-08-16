#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,K,L,R,ans,a[MN],sum[MN],st[31][MN];

struct Node{
    int l,L,R,mx;
    friend bool operator<(const Node &x,const Node &y){
        return sum[x.mx]-sum[x.l-1]<sum[y.mx]-sum[y.l-1];
    }
};
priority_queue<Node> q;

void initst(){
    for(int i=1;i<=30;i++){
        for(int j=1;j+(1<<i)-1<=n;j++){
            int x=st[i-1][j],y=st[i-1][j+(1<<(i-1))];
            st[i][j]=(sum[x]>sum[y]?x:y);
        }
    }
}

int queryst(int l,int r){
    int p=__lg(r-l+1);
    int x=st[p][l],y=st[p][r-(1<<p)+1];
    return sum[x]>sum[y]?x:y;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>K>>L>>R;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sum[i]=sum[i-1]+a[i];
        st[0][i]=i;
    }
    initst();
    for(int i=1;i+L-1<=n;i++){
        int ll=i+L-1,rr=min(i+R-1,n);
        q.push({i,ll,rr,queryst(ll,rr)});
    }
    while(K--){
        auto tp=q.top();q.pop();
        ans+=sum[tp.mx]-sum[tp.l-1];
        if(tp.L!=tp.mx) q.push({tp.l,tp.L,tp.mx-1,queryst(tp.L,tp.mx-1)});
        if(tp.R!=tp.mx) q.push({tp.l,tp.mx+1,tp.R,queryst(tp.mx+1,tp.R)});
    }
    cout<<ans;
    return 0;
}
