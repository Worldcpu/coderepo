#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,m,ty,v[MN],rt[MN],ans;

struct Segment{
    #define ls t[p].lson
    #define rs t[p].rson
    struct Node{
        int lson,rson,val,cov;
    }t[MN<<8];
    int tot;

    void pushup(int p){
        t[p].val=t[ls].val+t[rs].val;
    }

    void pushdown(int p,int l,int r){
        if(!p) return;
        if(t[p].cov){
            int mid=(l+r)>>1;
            int lstls=ls,lstrs=rs;
            ls=++tot,rs=++tot;
            t[ls]=t[lstls],t[rs]=t[lstrs];
            t[ls].val=v[t[p].cov]*(mid-l+1);
            t[rs].val=v[t[p].cov]*(r-mid);
            t[ls].cov=t[rs].cov=t[p].cov;
            t[p].cov=0;
        }
    }

    int update(int lst,int l,int r,int fl,int fr,int k){
        int p=++tot;
        t[p]=t[lst];
        if(l>=fl&&r<=fr){
            t[p].val=(r-l+1)*v[k];
            t[p].cov=k;
            return p;
        }
        pushdown(lst,l,r);
        t[p]=t[lst];
        int mid=(l+r)>>1;
        if(mid>=fl) t[p].lson=update(t[lst].lson,l,mid,fl,fr,k);
        if(mid<fr)  t[p].rson=update(t[lst].rson,mid+1,r,fl,fr,k);
        pushup(p);
        return p;
    }

    int query(int p,int l,int r,int fl,int fr){
        if(l>fr||r<fl) return 0;
        if(fl<=l&&r<=fr) return t[p].val;
        if(t[p].cov) return (min(r,fr)-max(l,fl)+1)*v[t[p].cov];
        int mid=(l+r)>>1,ret=0;
        if(mid>=fl) ret+=query(ls,l,mid,fl,fr);
        if(mid<fr)  ret+=query(rs,mid+1,r,fl,fr);
        return ret;
    }

    int get(int p,int l,int r,int pos){
        if(l==r) return t[p].cov;
        if(t[p].cov) return t[p].cov;
        int mid=(l+r)>>1;
        if(mid>=pos) return get(ls,l,mid,pos);
        else return get(rs,mid+1,r,pos);
    }

}sg;


int main(){
    cin>>n>>m>>ty;
    for(int i=1;i<=m;i++){
        int op,x,y;
        rt[i]=rt[i-1];
        cin>>op;
        if(op==1){
            cin>>x>>y;
            x=(x+ans)%n+1;
            y=(y+ans)%n+1;
            if(x>y) swap(x,y);
            int tmp=sg.query(rt[i],1,n,x,y);
            ans=tmp*ty;
            cout<<tmp<<'\n';
        }
        if(op==2){
            cin>>x;
            x=(x+ans)%n+1;
            int t=sg.get(rt[i],1,n,x);
            if(!t) continue;
            t=sg.get(rt[t-1],1,n,x);
            rt[i]=sg.update(rt[i],1,n,x,x,t);
        }
        if(op==3){
            cin>>x>>y>>v[i];
            x=(x+ans)%n+1;
            y=(y+ans)%n+1;
            if(x>y) swap(x,y);
            rt[i]=sg.update(rt[i],1,n,x,y,i);
        }
    }
    return 0;
}
