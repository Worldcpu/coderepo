#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,m,seq=1,rt[MN];

struct Segment{
#define ls t[p].lson
#define rs t[p].rson
    struct{
        int lson,rson,val;
    }t[MN<<4];
    int tot,s[MN],top;

    int newnode(){
        return (top?s[top--]:++tot);
    }

    void gc(int p){
        memset(&t[p],0,sizeof(t[p]));
        s[++top]=p;
    }

    void pushup(int p){
        t[p].val=t[ls].val+t[rs].val;
    }
    
    void modify(int &p,int l,int r,int pos,int k){
        if(!p) p=newnode();
        if(l==r){
            t[p].val+=k;
            return;
        }
        int mid=(l+r)>>1;
        if(mid>=pos) modify(ls,l,mid,pos,k);
        else modify(rs,mid+1,r,pos,k);
        pushup(p);
    }

    int query(int p,int l,int r,int fl,int fr){
        if(!p) return 0;
        if(l>=fl&&r<=fr) return t[p].val;
        int mid=(l+r)>>1,ret=0;
        if(mid>=fl) ret+=query(ls,l,mid,fl,fr);
        if(mid<fr) ret+=query(rs,mid+1,r,fl,fr);
        return ret;
    }

    int merge(int l,int r,int x,int y){
        if(!x||!y) return x+y;
        int p=newnode();
        if(l==r){
            t[p].val=t[x].val+t[y].val;
            gc(x),gc(y);
            return p;
        }
        int mid=(l+r)>>1;
        ls=merge(l,mid,t[x].lson,t[y].lson);
        rs=merge(mid+1,r,t[x].rson,t[y].rson);
        gc(x);
        gc(y);
        pushup(p);
        return p;
    }

    void split(int p,int &y,int k){
        if(!p) return;
        y=++tot;
        int v=t[ls].val;
        if(k>v) split(rs,t[y].rson,k-v);
        else swap(rs,t[y].rson);
        if(k<v) split(ls,t[y].lson,k);
        t[y].val=t[p].val-k;
        t[p].val=k;
    }

    int topk(int p,int l,int r,int k){
        if(l==r) return l;
        int mid=(l+r)>>1;
        if(t[ls].val<k) return topk(rs,mid+1,r,k-t[ls].val);
        else return topk(ls,l,mid,k);
    }

#undef ls
#undef rs
}sg;


signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        sg.modify(rt[1],1,n,i,x);
    }
    while(m--){
        int op,x,y,z;
        cin>>op;
        if(op==0){
            cin>>x>>y>>z;
            int k1=sg.query(rt[x],1,n,1,z),k2=sg.query(rt[x],1,n,y,z),tmp=0;
            sg.split(rt[x],rt[++seq],k1-k2);
            sg.split(rt[seq],tmp,k2);
            rt[x]=sg.merge(1,n,rt[x],tmp);
        }
        if(op==1){
            cin>>x>>y;
            rt[x]=sg.merge(1,n,rt[x],rt[y]);
        }
        if(op==2){
            cin>>x>>y>>z;
            sg.modify(rt[x],1,n,z,y);
        }
        if(op==3){
            cin>>x>>y>>z;
            cout<<sg.query(rt[x],1,n,y,z)<<'\n';
        }
        if(op==4){
            cin>>x>>y;
            if(sg.t[rt[x]].val<y) cout<<-1<<'\n';
            else cout<<sg.topk(rt[x],1,n,y)<<'\n';
        }
    }
    return 0;
}
