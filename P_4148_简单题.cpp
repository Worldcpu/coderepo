#include<bits/stdc++.h>
#define ls t[p].lson
#define rs t[p].rson
using namespace std;
constexpr int MN=5e5+15;
constexpr double Alp=0.75;
struct Point{
    int x[2],w;
}pt[MN];
struct Node{
    int lson,rson;
    Point P;
    int L[2],R[2],sum,siz;
}t[MN];
int n,tot,rt,s[MN],top;

int add(){
    if(!top) return ++tot;
    return s[top--];
}

void pushup(int p){
    t[p].sum=t[ls].sum+t[rs].sum+t[p].P.w;
    t[p].siz=t[ls].siz+t[rs].siz+1;
    for(int i=0;i<=1;i++){
        t[p].L[i]=min({t[p].P.x[i],t[ls].L[i],t[rs].L[i]});
        t[p].R[i]=max({t[p].P.x[i],t[ls].R[i],t[rs].R[i]});
    }
}

void getseq(int p,int cnt){
    if(ls) getseq(ls,cnt);
    s[++top]=p;
    pt[t[ls].siz+1+cnt]=t[p].P;
    if(rs) getseq(rs, t[ls].siz+1+cnt);
}

int rebuild(int l,int r,bool tp){
    if(l>r) return 0;
    int mid=(l+r)>>1;
    int p=add();
    nth_element(pt+l,pt+mid,pt+r+1,[&](Point a,Point b){
            return a.x[tp]<b.x[tp];
    });
    t[p].P=pt[mid];
    ls=rebuild(l,mid-1,tp^1);
    rs=rebuild(mid+1,r,tp^1);
    pushup(p);
    return p;
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
    if(pt.x[k]<=t[p].P.x[k]) insert(ls,pt,k^1);
    else insert(rs,pt,k^1);
    pushup(p);
    maintain(p, k);
}

bool isin(Node nd,int x1,int y1,int x2,int y2){
    return nd.L[0]>=x1&&nd.R[0]<=x2&&nd.L[1]>=y1&&nd.R[1]<=y2;
}

bool isinp(Point pt,int x1,int y1,int x2,int y2){
    return pt.x[0]>=x1&&pt.x[0]<=x2&&pt.x[1]>=y1&&pt.x[1]<=y2;
}

bool isout(Node nd,int x1,int y1,int x2,int y2){
    return nd.R[0]<x1||nd.L[0]>x2||nd.R[1]<y1||nd.L[1]>y2;
}

int query(int p,int x1,int y1,int x2,int y2){
    if(isin(t[p],x1,y1,x2,y2)) return t[p].sum;
    if(isout(t[p],x1,y1,x2,y2)) return 0;
    int ret=0;
    if(isinp(t[p].P,x1,y1,x2,y2)) ret+=t[p].P.w;
    ret+=query(ls,x1,y1,x2,y2)+query(rs,x1,y1,x2,y2);
    return ret;
}

int main(){
    cin>>n;
    t[0].L[0]=t[0].R[0]=MN+5;
    t[0].L[1]=t[0].R[1]=-1;
    int ans=0,op;
    while(cin>>op&&op!=3){
        if(op==1){
            int x,y,k;
            cin>>x>>y>>k;
            x^=ans;
            y^=ans;
            k^=ans;
            insert(rt,{x,y,k},0);
        }else{
            int x1,y1,x2,y2;
            cin>>x1>>y1>>x2>>y2;
            x1^=ans;
            x2^=ans;
            y1^=ans;
            y2^=ans;
            ans=query(rt,x1,y1,x2,y2);
            cout<<ans<<'\n';
        }
    }
    return 0;
}
