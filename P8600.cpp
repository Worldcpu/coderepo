#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,p[MN],ans;

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int mn,mncnt;

        Node(int mnn=0,int cnt=1){
            mn=mnn,mncnt=cnt;
        }

        friend Node operator+(const Node &x,const Node &y){
            Node ret(0,0);
            ret.mn=min(x.mn,y.mn);
            if(ret.mn==x.mn) ret.mncnt+=x.mncnt;
            if(ret.mn==y.mn) ret.mncnt+=y.mncnt;
            return ret;
        }

        friend Node operator+(const Node &x,const int &y){
            return Node(x.mn+y,x.mncnt);
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
        t[p].val=t[p].val+k;
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
        if(l==r){
            t[p].val=Node(l,1);
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void modify(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            doadd(p,k);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) modify(ls,fl,fr,k);
        if(mid<fr) modify(rs,fl,fr,k);
        pushup(p);
    }

    Node query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].val;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid<fl) return query(rs,fl,fr);
        if(mid>=fr) return query(ls,fl,fr);
        return query(ls,fl,fr)+query(rs,fl,fr);
    }

    #undef ls
    #undef rs
}sg;

namespace PPM{
    int stmn[MN],stmx[MN],topmn,topmx;

    void solve(){
        sg.build(1,1,n);
        for(int i=1;i<=n;i++){
            sg.modify(1,1,n,-1);
            while(topmx&&p[stmx[topmx]]<p[i]){
                sg.modify(1,stmx[topmx-1]+1,stmx[topmx],p[i]-p[stmx[topmx]]);
                topmx--;
            } 
            while(topmn&&p[stmn[topmn]]>p[i]){
                sg.modify(1,stmn[topmn-1]+1,stmn[topmn],p[stmn[topmn]]-p[i]);
                topmn--;
            } 
            stmx[++topmx]=i;
            stmn[++topmn]=i;
            auto ret=sg.query(1,1,n);           
            if(ret.mn==0) ans+=ret.mncnt;
        }
    }
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i];
    }   
    PPM::solve();
    cout<<ans;
    return 0;
}