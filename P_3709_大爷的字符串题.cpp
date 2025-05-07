#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
struct query{
    int l,r,id;
}q[MN];
int n,m,ret,len,cnt[MN],sum[MN],a[MN],b[MN],ans[MN],tot;

bool cmp(query x,query y){
    if(x.l/len!=y.l/len) return x.l<y.l;
    else return x.r<y.r;
}

void add(int p){
    cnt[a[p]]++;
    sum[cnt[a[p]]]++;
    ret=max(ret,cnt[a[p]]);
}

void del(int p){
    if(sum[cnt[a[p]]]==1&&ret==cnt[a[p]]){
        ret--;
    }
    sum[cnt[a[p]]--]--;
}

int main(){
    cin>>n>>m;
    len=sqrt(n);
    for(int i=1;i<=n;i++){
        cin>>a[i];
        b[i]=a[i];
    }
    sort(b+1,b+1+n);
    tot=unique(b+1,b+1+n)-b-1;
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(b+1,b+1+tot,a[i])-b;
    }
    for(int i=1;i<=m;i++){
        cin>>q[i].l>>q[i].r;
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
        ans[q[i].id]=-ret;
    }
    for(int i=1;i<=m;i++) cout<<ans[i]<<'\n';
    return 0;
}