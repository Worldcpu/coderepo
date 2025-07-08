#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int n,a[MN];

struct SAM{
    map<int,int> nxt[MN];
    int fa[MN],len[MN],cnt[MN],tot,lst;
    int cnt_init[MN];
    vector<int> adj[MN];

    void init(){
        tot=0;
        lst=0;
        fa[0]=-1;
        len[0]=0;
        nxt[0].clear();
        cnt_init[0]=0;
    }

    int newnode(){
        int cur=++tot;
        cnt_init[cur]=1;
        nxt[cur].clear();
        return cur;
    }

    int clone(int from){
        int cur=++tot;
        fa[cur]=fa[from];
        cnt_init[cur]=0;
        nxt[cur]=nxt[from];
        return cur;
    }

    void extend(int c){
        int cur=newnode();
        len[cur]=len[lst]+1;
        int p=lst;
        while(p!=-1&&!nxt[p][c]) nxt[p][c]=cur,p=fa[p];
        if(p==-1) fa[cur]=0;
        else{
            int q=nxt[p][c];
            if(len[q]==len[p]+1) fa[cur]=q;
            else{
                int nq=clone(q);
                len[nq]=len[p]+1;
                while(p!=-1&&nxt[p][c]==q) nxt[p][c]=nq,p=fa[p];
                fa[q]=fa[cur]=nq;
            }
        }
        lst=cur;
    }
}sam;


int main(){
    sam.init();
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=2;i++){
        for(int j=1;j<=n;j++){
            sam.extend(a[j]);
        }
    }
    int p=0;
    for(int i=1;i<=n;i++){
        auto it=sam.nxt[p].begin();
        p=(it->second);
        cout<<it->first<<" ";
    }
    return 0;
}
