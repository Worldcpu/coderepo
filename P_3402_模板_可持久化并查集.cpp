#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
int n,m;

struct DSU{
    struct Segment{
        #define ls t[p].lson
        #define rs t[p].rson
        struct Node{
            int lson,rson,dep,fa;
        }t[MN*50];
        int tot;

        void build(int &p,int l,int r){
            p=++tot;
            if(l==r){
                t[p].fa=l;
                return;
            }
            int mid=(l+r)>>1;
            build(ls,l,mid);
            build(rs,mid+1,r);
        }

        int modifydep(int lst,int l,int r,int pos){
            int p=++tot;
            t[p]=t[lst];
            if(l==r){
                t[p].dep++;
                return p;
            }
            int mid=(l+r)>>1;
            if(mid>=pos) ls=modifydep(t[lst].lson,l,mid,pos);
            else rs=modifydep(t[lst].rson,mid+1,r,pos);
            return p;
        }

        int query(int p,int l,int r,int pos){
            if(l==r) return p;
            int mid=(l+r)>>1;
            if(mid>=pos) return query(ls,l,mid,pos);
            else return query(rs,mid+1,r,pos);
        }

        int merge(int lst,int l,int r,int pos,int fa){
            int p=++tot;
            t[p].lson=t[lst].lson,t[p].rson=t[lst].rson;
            if(l==r){
                t[p].dep=t[lst].dep;
                t[p].fa=fa;
                return p;
            }
            int mid=(l+r)>>1;
            if(mid>=pos) ls=merge(t[lst].lson,l,mid,pos,fa);
            else rs=merge(t[lst].rson,mid+1,r,pos,fa);
            return p;
        }
        #undef ls
        #undef rs
    }sg;
    int rt[MN];

    void init(){
        sg.build(rt[0],1,n);
    }

    int root(int ver,int x){
        int ret=sg.query(ver,1,n,x);
        if(sg.t[ret].fa==x) return ret;
        else return root(ver,sg.t[ret].fa);
    }

    void merge(int ver,int x,int y){
        rt[ver]=rt[ver-1];
        int rx=root(rt[ver],x),ry=root(rt[ver],y);
        if(rx!=ry){
            if(sg.t[rx].dep>sg.t[ry].dep) swap(rx,ry);
            rt[ver]=sg.merge(rt[ver-1],1,n,sg.t[rx].fa,sg.t[ry].fa);
            if(sg.t[rx].dep==sg.t[ry].dep){
                rt[ver]=sg.modifydep(rt[ver],1,n,sg.t[ry].fa);
            }
        }
    }

    bool issame(int ver,int x,int y){
        rt[ver]=rt[ver-1];
        int rx=root(rt[ver],x),ry=root(rt[ver],y);
        if() return 1;
        else return 0;
    }

}dsu;


int main(){
    cin>>n>>m;
    dsu.init();
    for(int i=1;i<=m;i++){
        int op,x,y;
        cin>>op>>x>>y;
        if(op==1){
            cin>>x>>y;
            dsu.merge(i,x,y);
        }else if(op==2){
            cin>>x;
            dsu.rt[i]=dsu.rt[x];
        }else{
            cin>>x>>y;
            cout<<dsu.issame(i,x,y);
        }
    }
    return 0;
}