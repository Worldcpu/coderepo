#include<bits/stdc++.h>
using namespace std;
constexpr int MN=9e5+15;
struct Query{
    int l,r,id;
}qry[MN];
int n,m,vis[MN],ans[MN],L[MN],R[MN];

string s[MN];
vector<int> pre,stk;

struct gySAM{
    int nxt[MN][2],fa[MN],pos[MN],len[MN],cnt[MN],tot;

    void init(){
        tot=0;
        fa[0]=-1;
        len[0]=0;
        memset(nxt[0],0,sizeof(nxt[0]));
    }

    int extend(int c,int lst){
        if(nxt[lst][c]&&len[nxt[lst][c]]==len[lst]+1) return nxt[lst][c];
        int cur=++tot;
        len[cur]=len[lst]+1;
        memset(nxt[cur],0,sizeof(nxt[cur]));
        int p=lst;
        while(p!=-1&&!nxt[p][c]){
            nxt[p][c]=cur;
            p=fa[p];
        }
        bool flag=0;
        if(p==-1) fa[cur]=0;
        else{
            int q=nxt[p][c];
            if(len[q]==len[p]+1){
                fa[cur]=q;
                return cur;
            }
            else{
                if(p==lst) flag=1,cur=MN-1,tot--;
                int nq=++tot;
                len[nq]=len[p]+1;
                memcpy(nxt[nq],nxt[q],sizeof(nxt[q]));
                fa[nq]=fa[q];
                L[nq]=L[q],R[nq]=R[q];
                while(p!=-1&&nxt[p][c]==q){
                    nxt[p][c]=nq;
                    p=fa[p];
                }
                fa[q]=fa[cur]=nq;
                return flag?nq:cur;
            }
        }
        return cur;
    }
}sam;

namespace FK{
    int a[MN],mx[MN],pos[MN],bl[MN],br[MN],bk;

    void init(){
        bk=sqrt(n);
        for(int i=1;i<=bk;i++){
            bl[i]=br[i-1]*bk;
            br[i]=i*bk;
        }
        if(br[bk]<n){
            br[++bk]=n;
            bl[bk]=br[bk-1]+1;
        }
        for(int i=1;i<=bk;i++){
            for(int j=bl[i];j<=br[i];j++){
                pos[j]=i;
            }
        }
    }

    void modify(int x,int k){
        a[x]=max(a[x],k);
        mx[pos[x]]=max(mx[pos[x]],k);
    }

    int query(int r){
        int ret=0;
        for(int i=1;i<pos[r];i++){
            ret=max(ret,mx[i]);
        }
        for(int i=bl[pos[r]];i<=r;i++){
            ret=max(ret,a[i]);
        }
        return ret;
    }

    void reset(int x){
        a[x]=0;
        mx[pos[x]]=0;
    }

}using namespace FK;

bool cmp(Query x,Query y){
    return x.r<y.r;
}



int main(){
    memset(R,-1,sizeof(R));
    sam.init();
    init();
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>s[i];
    }
    for(int i=1;i<=m;i++){
        cin>>qry[i].l>>qry[i].r;
        qry[i].id=i;
    }
    sort(qry+1,qry+1+m,cmp);
    for(int i=1,it=0;i<=n;i++){
        int lst=0;
        pre.clear();
        stk.clear();
        for(auto c:s[i]){
            lst=sam.extend(c-'0',lst);
            pre.push_back(lst);
        }
        for(auto p:pre){
            while(p!=-1&&vis[p]<i){
                vis[p]=i;
                if(R[p]==i-1) R[p]++;
                else L[p]=i,R[p]=i;
                modify(L[p],sam.len[p]);
                stk.push_back(L[p]);
                p=sam.fa[p];
            }
        }
        while(it<m&&qry[it+1].r==i){
            it++;
            ans[qry[it].id]=query(qry[it].l);
        }
        for(auto p:stk){
            reset(p);
        }
    }
    for(int i=1;i<=m;i++) cout<<ans[i]<<'\n';
    return 0;
}
