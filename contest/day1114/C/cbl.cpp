#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;

namespace Sub1{
constexpr int MN=5e5+15;
constexpr double eps=1e-8;
struct Node{
    int f,t,b;
}a[MN];
int q,dtot;
bool vis[MN];
unordered_set<int> st;

double f(double k){
    double ans=0;
    for(auto p:st){
        ans+=fabs(a[p].t*(a[p].f-k)+a[p].b);
    }
    return ans;
}

void sol(){
    double L=-1e5,R=1e5; 
    while(R-L>=eps){
        auto mid=(L+R)/2;
        if(f(mid+eps)>f(mid-eps)) R=mid;
        else L=mid;
    }
    cout<<fixed<<setprecision(7)<<f(R)<<'\n';
}

void solve(int q){
    while(q--){
        int op;
        cin>>op;
        if(op==1){
            int f,t,b;
            cin>>f>>t>>b;
            a[++dtot]={f,t,b};
            st.insert(dtot);
        }else{
            int k;
            cin>>k;
            st.erase(k);
        }
        sol();
    }
}
}

namespace Sub2{
constexpr int MN=5e5+15,ML=-1e7,MR=1e7;
constexpr double eps=1e-7;
struct Node{
    int f,t,b,id;
    double val;
}a[MN],b[MN];
struct OP{
    int op;
    int id;
    int t0,b;
    int k;
}qry[MN];
int n,dtot,posa[MN],posb[MN],t0;

struct Line{
    int k,b;

    Line(int kk=0,int bb=0){
        k=kk,b=bb;
    }

    double getv(double x){
        return k*x+b;
    }

    friend Line operator+(const Line &x,const Line &y){
        return Line(x.k+y.k,x.b+y.b);
    }
};

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct SNode{
        int l,r;
        Line val;
    }t[MN<<2];

    void pushup(int p){
        t[p].val=t[ls].val+t[rs].val;
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            t[p].val=Line();
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);   
    }

    void modify(int p,int pos,const Line &k){
        if(t[p].l==t[p].r){
            t[p].val=k;
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) modify(ls,pos,k);
        else modify(rs,pos,k);
        pushup(p);
    }

    Line query(int p,int fl,int fr){
        if(fl>fr) return Line();
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].val;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fr) return query(ls,fl,fr);
        if(mid<fl) return query(rs,fl,fr);
        return query(ls,fl,fr)+query(rs,fl,fr);
    }
}sg[4];

namespace DOFG{
    double getfg(const Node &k){
        double K=-k.t;
        int b=k.f*k.t+k.b;
        if(fabs(K)<eps){
            return 0;
        }
        return (-b/K);
    }
}using DOFG::getfg;

namespace SOLVE{

    int finda(double k){
        int l=1,r=dtot,res=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if(a[mid].val<k) l=mid+1,res=mid;
            else r=mid-1;
        }
        return res;
    }

    int findb(double k){
        int l=1,r=dtot,res=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if(b[mid].val<k) l=mid+1,res=mid;
            else r=mid-1;
        }
        return res;
    }

    double f(double k){
        auto posa=finda(k);
        auto posb=findb(k);
        auto reta=sg[1].query(1,1,posa).getv(k)+sg[0].query(1,posa+1,dtot).getv(k);
        auto retb=sg[2].query(1,1,posb).getv(k)+sg[3].query(1,posb+1,dtot).getv(k);
        return reta+retb+t0;
    }

    void solve(){
        double L=ML,R=MR;
        while(R-L>=eps){
            auto mid=(L+R)/2;
            if(f(mid+eps)>f(mid-eps)) R=mid;
            else L=mid;
        }
        cout<<fixed<<setprecision(5)<<f(R)<<'\n';
    }

}




bool cmp(Node x,Node y){
    return x.val<y.val;
}

void solve(int n){
    for(int i=1;i<=n;i++){
        cin>>qry[i].op;
        if(qry[i].op==1){
            ++dtot;           
            int f,t,B;
            cin>>f>>t>>B;
            if(t<0){
                b[dtot]={f,t,B,dtot};
            }else if(t==0){
                qry[i].t0=B;
            }
            else{
                a[dtot]={f,t,B,dtot};
            }
            qry[i].id=dtot;
        }else{
            cin>>qry[i].k;
        }
    }

    for(int i=1;i<=dtot;i++){
        a[i].val=getfg(a[i]);
        b[i].val=getfg(b[i]);
    }

    sort(a+1,a+1+dtot,cmp);
    sort(b+1,b+1+dtot,cmp);

    for(int i=1;i<=dtot;i++){
        posa[a[i].id]=i;
        posb[b[i].id]=i;
    }

    sg[0].build(1,1,dtot);
    sg[1].build(1,1,dtot);
    sg[2].build(1,1,dtot);
    sg[3].build(1,1,dtot);

    for(int i=1,cnt=0;i<=n;i++){
        if(qry[i].op==1){
            cnt++;
            auto tmpa=a[posa[qry[i].id]];
            sg[0].modify(1,posa[qry[i].id],Line(-tmpa.t,tmpa.t*tmpa.f+tmpa.b));
            sg[1].modify(1,posa[qry[i].id],Line(tmpa.t,-tmpa.t*tmpa.f-tmpa.b));

            auto tmpb=b[posb[qry[i].id]];
            sg[2].modify(1,posb[qry[i].id],Line(-tmpb.t,tmpb.t*tmpb.f+tmpb.b));
            sg[3].modify(1,posb[qry[i].id],Line(tmpb.t,-tmpb.t*tmpb.f-tmpb.b));
        }else{
            
            sg[0].modify(1,posa[qry[i].k],Line());
            sg[1].modify(1,posa[qry[i].k],Line());
            sg[2].modify(1,posb[qry[i].k],Line());
            sg[3].modify(1,posb[qry[i].k],Line());
        } 
        SOLVE::solve();
    }
}
}

signed main(){
    int n;
    cin>>n;
    if(n<=5e3) Sub1::solve(n);   
    else Sub2::solve(n);
    return 0;
}