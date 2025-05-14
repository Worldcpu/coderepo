#include<bits/stdc++.h>
using namespace std;
constexpr int MN=4e5+15;
// struct query
// {
//     int l,r;
// }q[MN];
struct query{
    int l,r,k,id;
}q[MN];
int n,m,len,klen,maxx,ret,tot,b[MN],a[MN],ans[MN],cnt[MN],sum[MN],pos[MN],L[MN],R[MN];
int vis[MN],tag[MN];


bool cmp(query x,query y){
    if(x.l/len!=y.l/len) return x.l<y.l;
    else return x.r<y.r;
}

void init(){
    klen=sqrt(maxx);
    for(int i=1;i<=klen;i++){
        L[i]=R[i-1]+1;
        R[i]=i*klen;
    }
    // L[1]=0;
    if(R[klen]<maxx){
        R[++klen]=maxx;
        L[klen]=R[klen-1]+1;
    }
    for(int i=1;i<=klen;i++){
        for(int j=L[i];j<=R[i];j++){
            pos[j]=i;
        }
    }
}

void update(int x,int k){
    cnt[x]+=k;
    sum[pos[x]]+=k;
    ret+=k;
}

void add(int x){
    if(vis[a[x]]){
        update(vis[a[x]],-1);
    }
    vis[a[x]]++;
    update(vis[a[x]],1);
}

void del(int x){
    update(vis[a[x]],-1);
    vis[a[x]]--;
    if(vis[a[x]]) update(vis[a[x]],1);
}

int querysum(int x){
    if(ret<x) return -1;
    for(int i=1;i<=klen;i++){
        if(x>sum[i]) x-=sum[i];
        else{
            for(int j=L[i];j<=R[i];j++){
                if(x>cnt[j]) x-=cnt[j];
                else return j;
            }
        }
    }
    return -1;
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        b[i]=a[i];
    }
    sort(b+1,b+1+n);
    tot=unique(b+1,b+1+n)-b-1;
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(b+1,b+1+tot,a[i])-b;
        maxx=max(maxx,a[i]);
    }
    len=sqrt(n);
    maxx=n;
    init();
    for(int i=1;i<=m;i++){
        cin>>q[i].l>>q[i].r>>q[i].k;
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
        ans[q[i].id]=querysum(q[i].k);
    }
    for(int i=1;i<=m;i++) cout<<ans[i]<<'\n';
    return 0;
}