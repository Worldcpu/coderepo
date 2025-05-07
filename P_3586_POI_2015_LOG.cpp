#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15;
struct query{
    int op,k,a,c,s;
}q[MN];
int n,m,tot,ls[MN],a[MN];

struct BIT{
    private:
        int t[MN];

    public:

    inline int lowbit(int x){
        return x&-x;
    }

    int query(int x){
        int ret=0;
        while(x){
            ret+=t[x];
            x-=lowbit(x);
        }
        return ret;
    }

    void update(int x,int k){
        while(x<MN){
            t[x]+=k;
            x+=lowbit(x);
        }
    }

    int get(int x){
        return t[x];
    }

}b1,b2;

void lisan(){
    sort(ls+1,ls+1+tot);
    tot=unique(ls+1,ls+1+tot)-ls-1;
    for(int i=1;i<=m;i++){
        if(q[i].op){
            q[i].s=lower_bound(ls+1,ls+1+tot,q[i].s)-ls;
        }else q[i].a=lower_bound(ls+1,ls+1+tot,q[i].a)-ls;
    }
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        char op;
        int x,y;
        cin>>op;
        if(op=='U'){
            q[i].op=0;
            cin>>q[i].k>>q[i].a;
            ls[++tot]=q[i].a;
        }else{
            q[i].op=1;
            cin>>q[i].c>>q[i].s;
            ls[++tot]=q[i].s;
        }
    }
    lisan();
    for(int i=1;i<=m;i++){
        if(q[i].op==0){
            int x=0;
            if(x=a[q[i].k]){
                b1.update(x,-1);
                b2.update(x,-ls[x]);
            }
            x=a[q[i].k]=q[i].a;
            b1.update(x,1);
            b2.update(x,ls[q[i].a]);
        }else{
            int x=b1.query(tot)-b1.query(q[i].s-1);
            int sum=q[i].s?b2.query(q[i].s-1):0;
            if(sum>=(q[i].c-x)*ls[q[i].s]){
                cout<<"TAK\n";
            }else cout<<"NIE\n";
        }
    }
    return 0;
}