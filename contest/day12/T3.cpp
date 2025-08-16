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
    read(n);
    init();
    ans=1;
    for(int i=1;i<=n;i++){
        int l,r;
        read(l,r);
        pos[i]=mh.newnode(r,i);
        rt[l]=mh.merge(rt[l],pos[i]);// 根据左端点插进去
    }
    for(int i=1;i<=n;i++){
        //如果没有主元或者主元位置已经在前面（相当于没消完，行列式取值为 0）
        if(!rt[i]){
            put("tie");
            return;
        }
        if(mh.t[rt[i]].val<i){
            put("tie");
            return;
        }
        
        if(rt[i]!=pos[i]){
            // 高斯消元部分代码
            mh.t[pos[i]].id=mh.t[rt[i]].id;
            swap(pos[i],pos[mh.t[rt[i]].id]);
            mh.t[rt[i]].id=i;
            ans=-ans;
        }
        // 把没用完的元素丢进下一个堆
        int nxt=mh.t[rt[i]].val+1;
        if(nxt<=n){
            rt[nxt]=mh.merge(rt[nxt],mh.merge(mh.t[rt[i]].lson,mh.t[rt[i]].rson));
        }
    }
    put(((ans<0)?"xx":"pp"));
}

int main(){
    freopen("t3.in","r",stdin);
    freopen("t3.out","w",stdout);
    read(T);
    while(T--){
        solve();
    }

    return 0;
}
// 1
// 10
// 6 9
// 3 8
// 7 9
// 3 4
// 4 6
// 8 9
// 1 1
// 5 8
// 2 9
// 7 10
// Exp: tie 