#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15;
struct query{
    int l,r,id;
}q[MN];
int n,m,K,ret,len,a[MN],cnt[MN],ans[MN];

bool cmp(query x,query y){
    if(x.l/len!=y.l/len){
        return x.l<y.l;
    }
    return x.r<y.r;
}

void add(int p){
    ret+=cnt[a[p]^K];
    cnt[a[p]]++;
}

void del(int p){
    cnt[a[p]]--;
    ret-=cnt[a[p]^K];
}

signed main(){
    cin>>n>>m>>K;
    len=sqrt(n);
    for(int i=1;i<=n;i++){ cin>>a[i];a[i]^=a[i-1];}
    for(int i=1;i<=m;i++){
        cin>>q[i].l>>q[i].r;
        q[i].l--;
        q[i].id=i;
    }
    sort(q+1,q+1+m,cmp);
    int l=1,r=0;
    for(int i=1;i<=m;i++){
        while(l>q[i].l){
            l--;
            add(l);
        }
        while(r<q[i].r){
            r++;
            add(r);
        }
        while(l<q[i].l){
            del(l);
            l++;
        }
        while(r>q[i].r){
            del(r);
            r--;
        }
        ans[q[i].id]=ret;
    }
    for(int i=1;i<=m;i++) cout<<ans[i]<<'\n';
    return 0;
}