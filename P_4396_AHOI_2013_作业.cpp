#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
struct query{
    int l,r,a,b,id;
}q[MN];
int n,m,len,klen,maxx,cnt[MN],ans[MN],ans1[MN],a[MN],L[MN],R[MN],pos[MN],sum1[MN],sum[MN];
bool vis[MN];

bool cmp(query x,query y){
    if(x.l/len!=y.l/len){
        return x.l<y.l;
    }
    return x.r<y.r;
}

void init(){
    klen=sqrt(maxx);
    for(int i=1;i<=klen;i++){
        L[i]=R[i-1]+1;
        R[i]=i*klen;
    }
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
    if(cnt[x]==1&&k==1){
        vis[x]=1;
        sum1[pos[x]]++;
    }
    if(cnt[x]==0&&k==-1){
        vis[x]=0;
        sum1[pos[x]]--;
    }
}

void add(int p){
    update(a[p],1);
}

void del(int p){
    update(a[p],-1);
}

int querysum(int fl,int fr){
    if(fl>fr) return 0;
    int ret=0,ql=pos[fl],qr=pos[fr];
    if(ql==qr){
        for(int i=fl;i<=fr;i++){
            ret+=cnt[i];
        }
        return ret;
    }
    for(int i=fl;i<=R[ql];i++){
        ret+=cnt[i];
    }
    for(int i=L[qr];i<=fr;i++){
        ret+=cnt[i];
    }
    for(int i=ql+1;i<qr;i++){
        ret+=sum[i];
    }
    return ret;
}

int querysum1(int fl,int fr){
    if(fl>fr) return 0;
    int ret=0,ql=pos[fl],qr=pos[fr];
    if(ql==qr){
        for(int i=fl;i<=fr;i++){
            ret+=vis[i];
        }
        return ret;
    }
    for(int i=fl;i<=R[ql];i++){
        ret+=vis[i];
    }
    for(int i=L[qr];i<=fr;i++){
        ret+=vis[i];
    }
    for(int i=ql+1;i<qr;i++){
        ret+=sum1[i];
    }
    return ret;
}

int main(){
    cin>>n>>m;
    len=sqrt(n);
    for(int i=1;i<=n;i++){
        cin>>a[i];
        maxx=max(maxx,a[i]);
    }
    for(int i=1;i<=m;i++){
        cin>>q[i].l>>q[i].r>>q[i].a>>q[i].b;
        if(q[i].b>maxx) q[i].b=maxx;
        q[i].id=i;
    }
    init();
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
        ans[q[i].id]=querysum(q[i].a,q[i].b);
        ans1[q[i].id]=querysum1(q[i].a,q[i].b);
    }
    for(int i=1;i<=m;i++) cout<<ans[i]<<" "<<ans1[i]<<'\n';
    return 0;
}