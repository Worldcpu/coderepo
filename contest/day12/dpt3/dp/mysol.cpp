#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int T,n,ans,rt[MN],pos[MN];

struct MergeHeap{
#define ls t[p].lson
#define rs t[p].rson

    struct{
        int lson,rson,val,dis,id;  
    }t[MN];
    int tot;

    int newnode(int x,int y){
        t[++tot].val=x,t[tot].id=y;
        t[tot].lson=t[tot].rson=t[tot].dis=0;
        t[tot].dis=0;
        return tot;
    }

    void clear(){
        memset(t,0,sizeof(t));
        memset(rt,0,sizeof(rt));
        memset(pos,0,sizeof(pos));
        tot=0;
    }

    int merge(int x,int y){
        if(!x||!y) return x+y;
        if(t[x].val>t[y].val) swap(x,y);
        t[x].rson=merge(t[x].rson,y);
        if(t[t[x].lson].dis<t[t[x].rson].dis) swap(t[x].lson,t[x].rson);
        t[x].dis=t[t[x].rson].dis+1;
        return x;
    }
#undef ls
#undef rs
}mh;



void init(){
    mh.clear();
}

void solve(){
    cin>>n;
    init();
    ans=1;
    for(int i=1;i<=n;i++){
        int l,r;
        cin>>l>>r;
        pos[i]=mh.newnode(r,i);
        rt[l]=mh.merge(rt[l],pos[i]);
        //cerr<<rt[l]<<'\n';
    }
    for(int i=1;i<=n;i++){
        //cerr<<mh.t[rt[i]].val<<' '<<mh.t[rt[i]].id<<'\n';
        if(!rt[i]){
            cout<<"tie\n";
            return;
        }
        if(mh.t[rt[i]].val<i){
            cout<<"tie\n";
            return;
        }
        if(rt[i]!=pos[i]){
            mh.t[pos[i]].id=mh.t[rt[i]].id;
            swap(pos[i],pos[mh.t[rt[i]].id]);
            mh.t[rt[i]].id=i;
            ans=-ans;
        }
        int nxt=mh.t[rt[i]].val+1;
        if(nxt<=n){
            rt[nxt]=mh.merge(rt[nxt],mh.merge(mh.t[rt[i]].lson,mh.t[rt[i]].rson));
        }
    }
    cout<<((ans<0)?"xx":"pp")<<'\n';
}

int main(){
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}