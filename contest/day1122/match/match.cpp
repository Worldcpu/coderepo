#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,q,p[3][MN],rk[3][MN],pos[MN];
set<int> st;

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int l,r,val,add;
    }t[MN<<2];

    void doadd(int p,int k){
        t[p].add+=k;
        t[p].val+=k;
    }

    void pushdown(int p){
        if(t[p].add){
            doadd(ls,t[p].add);
            doadd(rs,t[p].add);
            t[p].add=0;
        }
    }

    void pushup(int p){
        t[p].val=min(t[ls].val,t[rs].val);
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            t[p].val=pos[l]-l;
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void add(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            doadd(p,k);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) add(ls,fl,fr,k);
        if(mid<fr) add(rs,fl,fr,k);
        pushup(p);
    }

    int query(int p){
        if(t[p].l==t[p].r) return t[p].l;
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(t[ls].val>0) return query(rs);
        else return query(ls);
    }

}sg;

void solop2(int id,int x,int y){
    int px=rk[id][x],py=rk[id][y];
    sg.add(1,min({rk[0][x],rk[1][x],rk[2][x]}),n,-1);
    sg.add(1,min({rk[0][y],rk[1][y],rk[2][y]}),n,-1);
    swap(p[id][px],p[id][py]);
    swap(rk[id][x],rk[id][y]);
    sg.add(1,min({rk[0][x],rk[1][x],rk[2][x]}),n,1);
    sg.add(1,min({rk[0][y],rk[1][y],rk[2][y]}),n,1);
}

int main(){
    freopen("match.in","r",stdin);
    freopen("match.out","w",stdout);
    cin>>n>>q;
    for(int i=0;i<3;i++){
        for(int j=1;j<=n;j++){
            cin>>p[i][j];
            rk[i][p[i][j]]=j;
        }
    }
    for(int i=1;i<=n;i++){
        st.insert(p[0][i]);
        st.insert(p[1][i]);
        st.insert(p[2][i]);
        pos[i]=st.size();
    }
    sg.build(1,1,n);   
    while(q--){
        int op,p,x,y;
        cin>>op>>p;
        if(op==1){
            if(rk[0][p]<=sg.query(1)) cout<<"Yes\n";
            else cout<<"No\n";
        }else{
            cin>>x>>y;
            solop2(p-1,x,y);
        }
    }

    return 0;
}