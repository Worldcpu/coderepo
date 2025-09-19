#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e6+15;
struct Node{
    int x,y,v;
}a[MN];
int pre[MN],bnum[MN],siz[MN],n,r,c,ans;

int root(int x){
    if(pre[x]==x) return pre[x];
    else return pre[x]=root(pre[x]);
}

bool cmp(Node x,Node y){
    return x.v>y.v;
}

void initpre(int n){
    for(int i=0;i<=n;i++){
        pre[i]=i;
        siz[i]=1;
    }
}

signed main(){
    freopen("oblivious.in", "r", stdin);
    freopen("oblivious.out", "w", stdout);
    cin>>n>>r>>c;
    initpre(r+c);
    for(int i=1;i<=n;i++){
        cin>>a[i].x>>a[i].y>>a[i].v;
    }
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++){
        int rx=root(a[i].x),ry=root(a[i].y+r);
        if(rx==ry&&bnum[rx]+1<=siz[rx]){
            bnum[rx]++;
            ans+=a[i].v;           
        }else if(rx!=ry&&bnum[rx]+bnum[ry]+1<=siz[rx]+siz[ry]){
            bnum[rx]+=bnum[ry]+1;
            siz[rx]+=siz[ry];
            ans+=a[i].v;
            pre[ry]=rx;
        }
    }
    cout<<ans;

    return 0;
}