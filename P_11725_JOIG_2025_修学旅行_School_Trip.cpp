#include<bits/stdc++.h>
#define ls p*3-1
#define ms p*3
#define rs p*3+1
using namespace std;
constexpr int MN=1594323;
int n,m;
struct segtree{
    int l,r,val;
}t[MN];
string s;

void pushup(int p){
    t[p].val=(t[ls].val+t[rs].val+t[ms].val>=2);
}

void build(int p,int l,int r){
    t[p].l=l;
    t[p].r=r;
    if(l==r){
        t[p].val=s[l]-'A';
        return;
    }
    int mid=(r-l+1)/3;
    build(ls,l,l+mid-1);
    build(ms,l+mid,l+2*mid-1);
    build(rs,l+mid*2,r);
    pushup(p);
}

void update(int p,int pos){
    if(t[p].l==t[p].r){
        t[p].val^=1;
        return;
    }
    int mid=(t[p].r-t[p].l+1)/3;
    if(pos<=t[p].l+mid-1) update(ls,pos);
    else if(pos>=t[p].l+mid*2) update(rs,pos);
    else update(ms,pos);
    pushup(p);
}

int main(){
    cin>>n>>m;
    cin>>s;
    s=" "+s;
    build(1,1,pow(3,n));
    for(int i=1;i<=m;i++){
        int pos;
        cin>>pos;
        update(1,pos);
        cout<<(char)(t[1].val+'A')<<'\n';
    }
    return 0;
}