#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e5+15;
struct query{
    int l,r,id;
}q[MN];
int n,m,len,klen,maxx,a[MN],ans[MN],cnt[MN],sum1[MN],pos[MN],L[MN],R[MN];
bool vis[MN],tag[MN];


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
    L[1]=0;
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
    if(cnt[x]==1&&k==1){
        vis[x]=1;
        sum1[pos[x]]++;
    }
    if(cnt[x]==0&&k==-1){
        vis[x]=0;
        sum1[pos[x]]--;
    }
    if(sum1[pos[x]]==R[pos[x]]-L[pos[x]]+1){
        tag[pos[x]]=1;
    }else tag[pos[x]]=0;
}

int querymin(){
    int p=0;
    for(int i=1;i<=klen;i++){
        if(!tag[i]){
            p=i;
            break;
        }
    }
    if(!p) return maxx+1;
    for(int i=L[p];i<=R[p];i++){
        if(!vis[i]){
            return i;
        }
    }
    return 0;
}

void add(int x){
    update(a[x],1);
}

void del(int x){
    update(a[x],-1);
}

int main(){
    cin>>n>>m;
    len=sqrt(n);
    for(int i=1;i<=n;i++){
        cin>>a[i];
        maxx=max(maxx,a[i]);
    }
    init();
    // sg.build(1,1,n);
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
        // maxx=sg.query(1,q[i].l,q[i].r);
        ans[q[i].id]=querymin();
    }
    for(int i=1;i<=m;i++) cout<<ans[i]<<'\n';
    return 0;
}