#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
constexpr double eps=1e-8;
int n,q,g[MN],opid[MN];
double K[MN],b[MN];

namespace Sub1{

    void solve(){
        while(q--){
            int op,l,r,x;
            cin>>op;
            if(op==1){
                cin>>l>>r>>x;
                double st=(double)x,sum=0;
                for(int i=l;i<=r;i++){
                    if(g[i]==1){
                        st=K[i]*st+b[i];
                    }else{
                        st=sqrt(st);
                    }
                    sum+=st;
                }
                cout<<fixed<<setprecision(8)<<st<<' '<<sum<<'\n';
            }else{
                cin>>x>>op;
                if(op==1){
                    g[x]=op;
                    cin>>K[x]>>b[x];
                }else{
                    g[x]=op;
                }
            }
        }
    }

}

namespace Sub2{
    struct Node{
        double k,b;

        double getv(int x){
            return k*x+b;
        }

        Node(double kk=0,double bb=0){
            k=kk,b=bb;
        }

        friend Node operator+(const Node &x,const Node &y){
            return Node(x.k*y.k,y.k*x.b+y.b);
        }

        friend Node operator*(const Node &x,const Node &y){
            return Node(x.k+y.k,x.b+y.b);
        }
    };

    struct Segment{
        #define ls p<<1
        #define rs p<<1|1
        struct SNode{
            int l,r;
            Node val,sum;
        }t[MN<<2];
        struct QWQ{
             Node val,sum;           

            friend QWQ operator+(const QWQ &x,const QWQ &y){
                return {x.val+y.val,x.sum*(x.val+y.val)};
            }
        };

        void pushup(int p){
            t[p].val=t[ls].val+t[rs].val;
            auto tmp=t[ls].val+t[rs].sum;
            t[p].sum=t[ls].sum*tmp;
        }

        void build(int p,int l,int r){
            t[p].l=l;
            t[p].r=r;
            if(l==r){
                t[p].val=Node(K[l],b[l]);
                t[p].sum=Node(K[l],b[l]);
                return;
            }
            int mid=(l+r)>>1;
            build(ls,l,mid);
            build(rs,mid+1,r);
            pushup(p);
        }

        void modify(int p,int pos,const Node &k){
            if(t[p].l==t[p].r){
                t[p].val=t[p].sum=k;
                return;
            }
            int mid=(t[p].l+t[p].r)>>1;
            if(mid>=pos) modify(ls,pos,k);
            else modify(rs,pos,k);
            pushup(p);
        }

        auto query(int p,int fl,int fr){
            if(t[p].l>=fl&&t[p].r<=fr){
                return (QWQ){t[p].val,t[p].sum};
            }
            int mid=(t[p].l+t[p].r)>>1;
            if(mid>=fr) return query(ls,fl,fr);
            if(mid<fl) return query(rs,fl,fr);
            return query(ls,fl,fr)+query(rs,fl,fr);
        }
        #undef ls
        #undef rs
    }sg;

    void solve(){
        sg.build(1,1,n);
        while(q--){
            int op,l,r,x;
            cin>>op;
            if(op==1){
                cin>>l>>r>>x;
                auto res=sg.query(1,l,r);
                cout<<fixed<<setprecision(8)<<res.val.getv(x)<<' '<<res.sum.getv(x)<<'\n';
            }else{
                double k,b;
                cin>>x>>op>>k>>b;
                sg.modify(1,x,Node(k,b));
            }
        }
    }

}


int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>g[i];
        if(g[i]==1){
            cin>>K[i]>>b[i];
        }
    }    
    cin>>q;
    if(n<=1e3&&q<=1e3){
        Sub1::solve();
    }else Sub2::solve();
    return 0;
}