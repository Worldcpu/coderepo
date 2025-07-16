#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
using namespace std;
const int N=2e5+5;
const int B=500;
int n,m,rt;
vector<int> tr[N];
struct Query { int l,r,id,tmp; };
vector<Query> q[N];
int son[N],siz[N],fa[N];
int f[N],tmp[N],pos[N],R[N];
int num[N],nn,ans1,ans2;
int sum[B],cnt[N],ans[N],tol[N];
pii a[N];

void dfs1(int x,int _fa) {
    siz[x]=1; fa[x]=_fa;
    for(int v:tr[x]) {
        if(v==_fa) continue;
        dfs1(v,x);
        siz[x]+=siz[v];
    }
}

void dfs0(int x,int ffa) {
    a[++nn]=pii(x,ffa), num[nn]=x;
    for(int v:tr[x]) {
        if(v==fa[x]) continue;
        dfs0(v,ffa);
    }
}

bool cmpsiz(int x,int y) { return siz[x]>siz[y]; }
bool cmpquery(Query x,Query y) { return (pos[x.l]==pos[y.l]?x.r<y.r:x.l<y.l); }

void add(int x,int op) {
    ans1 += 1 + cnt[x]*2*op;
    cnt[x] += op;
    ans2 += op;
}

Query qq[N];
void solve1(int x) {
    if(q[x].empty()) return;
    int cnt=0;
    for(int v:tr[x]) if(v!=fa[x]) tmp[++cnt]=v;
    sort(tmp+1,tmp+1+cnt,cmpsiz);
    
    nn=0;
    for(int i=51;i<=cnt;i++) {
        dfs0(tmp[i],tmp[i]);
        f[tmp[i]]=1;
    }
    sort(a+1,a+1+nn);
    sort(num+1,num+1+nn);
    
    for(int i=0;i<q[x].size();i++) {
        int ll=lower_bound(num+1,num+1+nn,q[x][i].l)-num;
        int rr=upper_bound(num+1,num+1+nn,q[x][i].r)-num-1;
        qq[i+1]={ll,rr,q[x][i].id};
    }

    int l=1,r=0,bl=nn/sqrt(q[x].size())+1;
    for(int i=1;i<=nn;i++) pos[i]=(i+bl-1)/bl;
    sort(qq+1,qq+1+q[x].size(),cmpquery);
    ans1=ans2=0;
    
    for(int i=1;i<=q[x].size();i++) {
        if(qq[i].l>nn||qq[i].r<1) continue;
        while(l<qq[i].l) add(a[l++].second,-1);
        while(l>qq[i].l) add(a[--l].second,1);
        while(r<qq[i].r) add(a[++r].second,1);
        while(r>qq[i].r) add(a[r--].second,-1);
        ans[qq[i].id]-=ans1;
        tol[qq[i].id]+=ans2;
    }
}

int query(int x) { return x?(R[x]==x?sum[pos[x]]:sum[pos[x]-1]+cnt[x]):0; }

void upd(int x) {
    for(int i=pos[x];i<=pos[n];i++) sum[i]++;
    for(int i=x;i<=R[x];i++) cnt[i]++;
}

void solve2(int x) {
    if(!f[x]&&!q[fa[x]].empty()) {
        for(auto &qry:q[fa[x]]) {
            qry.tmp=query(qry.r)-query(qry.l-1);
        }
    }
    
    upd(x);
    for(int v:tr[x]) if(v!=fa[x]) solve2(v);
    
    if(!f[x]&&!q[fa[x]].empty()) {
        for(auto &qry:q[fa[x]]) {
            int ea=query(qry.r)-query(qry.l-1)-qry.tmp;
            ans[qry.id]-=ea*ea;
            tol[qry.id]+=ea;
        }
    }
    
    for(auto &qry:q[x]) {
        if(qry.l<=x&&x<=qry.r) {
            ans[qry.id]+=tol[qry.id]*2;
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    
    cin>>n>>m>>rt;
    for(int i=1,u,v;i<n;i++) {
        cin>>u>>v;
        son[u]++,son[v]++;
        tr[u].push_back(v);
        tr[v].push_back(u);
    }
    
    for(int i=1,l,r,x;i<=m;i++) {
        cin>>l>>r>>x;
        q[x].push_back({l,r,i,0});
    }
    
    dfs1(rt,0);
    for(int i=1;i<=n;i++) {
        son[i]=(i==rt?son[i]:son[i]-1);
        if(son[i]>50) solve1(i);
    }
    
    for(int i=1;i<=n;i++) {
        pos[i]=(i+B-1)/B;
        R[i]=min(n,pos[i]*B);
    }
    memset(cnt,0,sizeof cnt);
    solve2(rt);
    
    for(int i=1;i<=m;i++) {
        cout<<((tol[i]*tol[i]+ans[i])>>1)<<"\n";
    }
    return 0;
}
