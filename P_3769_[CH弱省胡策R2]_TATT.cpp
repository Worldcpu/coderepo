#include <bits/stdc++.h>
#define ls t[p].lson
#define rs t[p].rson
using namespace std;
constexpr double Alp=0.72;
constexpr int MN=5e4+15;
struct Query{
    int a,b,c,d;
}qry[MN];
struct Point{
    int x[3],f;
}pt[MN];
struct Node{
    int lson,rson,siz,maxx;
    Point P;
    int L[3],R[3];
}t[MN];
int n,s[MN],f[MN],rt,tot,top;

int add(){
    if(!top) return ++tot;
    return s[top--];
}

void pushup(int p){
    t[p].maxx=max({t[p].P.f,t[ls].maxx,t[rs].maxx});
    t[p].siz=t[ls].siz+t[rs].siz+1;
    for(int i=0;i<=2;i++){
        t[p].L[i]=min({t[p].P.x[i],t[ls].L[i],t[rs].L[i]});
        t[p].R[i]=max({t[p].P.x[i],t[ls].R[i],t[rs].R[i]});
    }
}

int rebuild(int l,int r,int k){
    if(l>r) return 0;
    int mid=(l+r)>>1;
    int p=add();
    nth_element(pt+l,pt+mid,pt+r+1,[&](Point a,Point b){
            return a.x[k]<b.x[k];
    });
    t[p].P=pt[mid];
    ls=rebuild(l,mid-1,(k+1)%3);
    rs=rebuild(mid+1,r,(k+1)%3);
    pushup(p);
    return p;
}

void getseq(int p,int cnt){
    if(ls) getseq(p,cnt);
    s[++top]=p;
    pt[t[ls].siz+1+cnt]=t[p].P;
    if(rs) getseq(rs,t[ls].siz+1+cnt);
}

void maintain(int &p,int k){
    if(t[p].siz*Alp<t[ls].siz||t[p].siz*Alp<t[rs].siz){
        getseq(p,0);
        p=rebuild(1,top,k);
    }
}

void insert(int &p,Point pt,int k){
    if(!p){
        p=add();
        ls=rs=0;
        t[p].P=pt;
        pushup(p);
        return;
    }
    if(t[p].P.x[k]>=pt.x[k]) insert(ls,pt,(k+1)%3);
    else insert(rs,pt,(k+1)%3);
    pushup(p);
    maintain(p,k);
}

bool isin(Node nd,int b,int c,int d){
    return nd.L[0]>=b&&nd.L[1]>=c&&nd.L[2]>=d;
}

bool isinp(Point pt,int b,int c,int d){
    return pt.x[0]>=b&&pt.x[1]>=c&&pt.x[2]>=d;
}

bool isout(Node nd,int b,int c,int d){
    return nd.L[0]<b||nd.L[1]<c||nd.L[2]<d;
}

int query(int p,int b,int c,int d){
    if(isin(t[p],b,c,d)) return t[p].maxx;
    if(isout(t[p],b,c,d)) return 0;
    int ret=0;
    if(isinp(t[p].P,b,c,d)) ret=t[p].P.f;
    return max({ret,query(ls,b,c,d),query(rs,b,c,d)});
}

bool cmp(Query x,Query y){
    if(x.a==y.a){
        if(x.b==y.b){
            if(x.c==y.c) return x.d<y.d;
            return x.c<y.c;
        }
        return x.b<y.b;
    }
    return x.a<y.a;
}

int main(){
    cin>>n;
    t[0].L[0]=t[0].R[0]=1e9;
    t[0].L[1]=t[0].R[1]=-1;
    for(int i=1;i<=n;i++){
        cin>>qry[i].a>>qry[i].b>>qry[i].c>>qry[i].d;
    }
    sort(qry+1,qry+1+n,cmp);
    for(int i=1;i<=n;i++){
        f[i]=query(rt,qry[i].b,qry[i].c,qry[i].d)+1;
        insert(rt,{qry[i].b,qry[i].c,qry[i].d},0);
    }
    return 0;
}
