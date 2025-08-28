#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15,INF=1e9;
int n,V,q,a[MN];

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int v,cnt;

        Node(int x=INF,int y=0){
            v=x,cnt=y;
        }
        
        friend Node operator+(const Node &x,const Node &y){
            Node ret;
            ret.v=min(x.v,y.v);
            if(x.v==ret.v){
                ret.cnt+=x.cnt;
            }
            if(ret.v==y.v){
                ret.cnt+=y.cnt;
            }
            return ret;
        }

    };

    struct SNode{
        int l,r,add;
        Node val;
    }t[MN<<2];

    void pushup(int p){
        t[p].val=t[ls].val+t[rs].val;
    }

    void doadd(int p,int k){
        t[p].val.v+=k;
        t[p].add+=k;
    }

    void pushdown(int p){
        if(t[p].add){
            doadd(ls,t[p].add);
            doadd(rs,t[p].add);
            t[p].add=0;
        }
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void modifyl(int p,int pos,int k){
        if(t[p].l==t[p].r){
            if(k==0) t[p].val=Node();
            else t[p].val=Node(t[p].add,1);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) modifyl(ls,pos,k);
        else modifyl(rs,pos,k);
        pushup(p);
    }

    void modifya(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            doadd(p,k);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) modifya(ls,fl,fr,k);
        if(mid<fr) modifya(rs,fl,fr,k);
        pushup(p);
    }

    Node query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr) return t[p].val;
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        Node ret;
        if(mid>=fl) ret=ret+query(ls,fl,fr);
        if(mid<fr) ret=ret+query(rs,fl,fr);
        return ret;
    }

}sg;

void solve(int i,int f){
    int l=min(a[i],a[i+1]),r=max(a[i],a[i+1])-1;
    sg.modifya(1,l,r,f);
}

int main(){
    cin>>n>>q;
    V=1e6;
    sg.build(1,0,V);
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sg.modifyl(1,a[i],1);
    }
    a[0]=V+1,a[n+1]=0;
    for(int i=0;i<=n;i++){
        solve(i,1);
    }
    while(q--){
        int x;
        cin>>x;
        solve(x-1,-1);
        solve(x,-1);
        sg.modifyl(1,a[x],0);
        cin>>a[x];
        solve(x-1,1);
        solve(x,1);
        sg.modifyl(1,a[x],1);
        if(sg.t[1].val.v==1){
            cout<<sg.t[1].val.cnt<<'\n';
        }else cout<<0<<'\n';
    }

    return 0;
}