#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int pre[MN],R[MN],q,n;
string st;

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int l,r,val;
    }t[MN<<2];

    void pushup(int p){
        t[p].val=min(t[ls].val,t[rs].val);
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r) return (void)(t[p].val=pre[l]);
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    int query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr) return t[p].val;
        int mid=(t[p].l+t[p].r)>>1,ret=1e9;
        if(mid>=fl) ret=min(ret,query(ls,fl,fr));
        if(mid<fr) ret=min(ret,query(rs,fl,fr));
        return ret;
    }
}sg;



int main(){
    cin>>st>>q;
    n=st.length();
    st=" "+st;
    for(int i=1,sum=0;i<=n;i++){
        R[i]=R[i-1];
        if(st[i]==')'){
            sum--;
            R[i]++;
        }else{
            sum++;
        }
        pre[i]=sum;
    }
    sg.build(1,1,n);
    while(q--){
        int l,r;
        cin>>l>>r;
        cout<<(R[r]-R[l-1]-max(pre[l-1]-sg.query(1,l,r),0))*2<<'\n';
    }

    return 0;
}