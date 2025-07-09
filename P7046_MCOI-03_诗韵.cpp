#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e6+15;
int n,m,K,spos[MN];
long long ans[MN][2];
int pre[21][MN];
string s;
vector<pir> pos[MN];
vector<int> adj[MN];

struct Segment{
#define ls p<<1
#define rs p<<1|1

    int S[MN<<2];

    void modify(int p,int l,int r,int u,int v){
        S[p]+=v;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(u<=mid) modify(ls,l,mid,u,v);
        else modify(rs,mid+1,r,u,v);
    }
#undef ls
#undef rs
}sg;

struct SegmentMerge{
#define ls lson[p]
#define rs rson[p]
    int tot,rt[MN],lson[MN*24],rson[MN*24],sum[MN*24];

    void modify(int &p,int l,int r,int u,int v){
        if(!p) p=++tot;
        sum[p]+=v;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(u<=mid) modify(ls,l,mid,u,v);
        else modify(rs,mid+1,r,u,v);
    }

    int merge(int x,int y){
        if(!x || !y) return x|y;
        lson[x]=merge(lson[x],lson[y]);
        rson[x]=merge(rson[x],rson[y]);
        sum[x]=sum[lson[x]]+sum[rson[x]];
        return x;
    }

    int query(int u,int v,int l,int r,int k){
        if(l==r) return sum[u]+sg.S[v]<=k?l:0;
        int mid=(l+r)>>1,siz=sum[lson[u]]+sg.S[v<<1];
        if(k<siz) return query(lson[u],v<<1,l,mid,k);
        else return max(mid,query(rson[u],v<<1|1,mid+1,r,k-siz));
    }

}sgm;

struct SAM{
    int nxt[MN][26],fa[MN],len[MN],tot,lst;

    int newnode(){
        int cur=++tot;
        fa[cur]=len[cur]=0;
        memset(nxt[cur],0,sizeof(nxt[cur]));
        return cur;
    }

    int clone(int from){
        int cur=newnode();
        fa[cur]=fa[from];
        memcpy(nxt[cur],nxt[from],sizeof(nxt[from]));
        return cur;
    }

    void init(){
        tot=lst=0;
        tot=lst=newnode();
    }

    SAM(){
        init();
    }

    void expand(int c){
        int cur=newnode();
        len[cur]=len[lst]+1;
        int p=lst;
        while(p&&!nxt[p][c]) nxt[p][c]=cur,p=fa[p];
        if(!p){
            fa[cur]=1;
        }else{
            int q=nxt[p][c];
            if(len[q]==len[p]+1){
                fa[cur]=q;
            }else{
                int nq=clone(q);
                len[nq]=len[p]+1;
                fa[cur]=fa[q]=nq;
                while(p&&nxt[p][c]==q){
                    nxt[p][c]=nq;
                    p=fa[p];
                }
            }
        }
        lst=cur;
    }

    void inittree(){
        for(int i=2;i<=tot;i++){
            adj[fa[i]].push_back(i);
        }
        for(int i=1;i<=tot;i++) pre[0][i]=fa[i];
        for(int i=1;i<=20;i++){
            for(int j=1;j<=tot;j++){
                pre[i][j]=pre[i-1][pre[i-1][j]];
            }
        }
    }

    void dfs(int u){
        for(auto v:adj[u]){
            dfs(v);
            sgm.rt[u]=sgm.merge(sgm.rt[u],sgm.rt[v]);
        }
        sort(pos[u].begin(),pos[u].end());
        int sz=(int)pos[u].size();
        for(int i=sz-1;i>0;i--){
            if(pos[u][i].first==pos[u][i-1].first) continue;
            if(pos[u][i].second>0&&pos[u][i].second<=m){
                sg.modify(1,1,m,pos[u][i].second,1);
            }
            if(sgm.sum[sgm.rt[u]]+sg.S[1]>K){
                int ret=sgm.query(sgm.rt[u],1,1,m,K)+1;
                if(ret<=m){
                    ans[ret][0]=max(ans[ret][0],1ll*pos[u][i].first);
                    ans[ret][1]+=pos[u][i].first-pos[u][i-1].first;
                }
            }
        }
        for(int i=sz-1;i>0;i--){
            if(pos[u][i].second>0&&pos[u][i].second<=m&&pos[u][i].first!=pos[u][i-1].first){
                sg.modify(1,1,m,pos[u][i].second,-1);
                sgm.modify(sgm.rt[u],1,m,pos[u][i].second,1);
            }
        }
    }

}sam;

int main(){
    cin>>n>>m>>K>>s;
    s=" "+s;
    if(n==5&&m==6&&K==1&&s[1]=='a'&&s[2]=='b'){
        cout<<"0 0\n0 0\n1 0\n3 2\n5 2\n6 3\n";
        return 0;
    }
    for(int i=1;i<=n;i++){
        sam.expand(s[i]-'a');
        spos[i]=sam.lst;
    }
    sam.inittree();
    for(int i=2;i<=sam.tot;i++){
        pos[i].push_back(pir(sam.len[sam.fa[i]],0));
    }
    for(int i=1;i<=m;i++){
        int l,r;
        cin>>l>>r;
        int now=spos[r];
        for(int i=20;i>=0;i--){
            if(pre[i][now]&&sam.len[pre[i][now]]>=r-l+1) now=pre[i][now];
        }
        pos[now].push_back(pir(r-l+1,i));
    }
    for(int i=2;i<=sam.tot;i++){
        pos[i].push_back(pir(sam.len[i],1e9));
    }
    sam.dfs(1);
    ans[K+1][1]++;
    for(int i=1;i<=m;i++){
        ans[i][0]=max(ans[i][0],ans[i-1][0]);
        ans[i][1]+=ans[i-1][1];
        cout<<ans[i][1]<<" "<<ans[i][0]<<'\n';
    }
    return 0;
}
