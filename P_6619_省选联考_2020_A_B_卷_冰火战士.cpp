#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MQ=2e6+15;
int q,a[MQ],tot,sum1;

struct query{
    int op,t,x,y;
}qry[MQ];

struct BIT
{
    private:
        int t[MQ];
    public:

    inline int lowbit(int x){
        return x&-x;
    }

    void update(int pos,int k){
        while(pos<MQ){
            t[pos]+=k;
            pos+=lowbit(pos);
        }
    }

    int query(int x){
        int ret=0;
        while(x){
            ret+=t[x];
            x-=lowbit(x);
        }
        return ret;
    }

    int get(int x){
        return t[x];
    }
}t0,t1;

template<typename type>
void read(type &x){
    x=0;bool flag(0);char ch=getchar();
    while(!isdigit(ch)) flag=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    flag?x=-x:0;
}

void lisan(){
    sort(a+1,a+1+tot);
    tot=unique(a+1,a+1+tot)-a-1;
    for(int i=1;i<=q;i++){
        if(qry[i].op==2) continue;
        qry[i].x=lower_bound(a+1,a+1+tot,qry[i].x)-a;
    }
}

signed main(){
    read(q);
    for(int i=1;i<=q;i++){
        read(qry[i].op);
        if(qry[i].op==1){
            // cin>>qry[i].t>>qry[i].x>>qry[i].y;
            read(qry[i].t);
            read(qry[i].x);
            read(qry[i].y);
            a[++tot]=qry[i].x;
        }else read(qry[i].t);
    }
    lisan();
    for(int i=1;i<=q;i++){
        if(qry[i].op==1){
            if(qry[i].t){
                t1.update(qry[i].x+1,qry[i].y);
                sum1+=qry[i].y;
            }else t0.update(qry[i].x,qry[i].y);
        }else{
            int p=qry[i].t;
            if(qry[p].t){
                t1.update(qry[p].x+1,-qry[p].y);
                sum1-=qry[p].y;
            }else t0.update(qry[p].x,-qry[p].y);
        }
        int s0=0,s1=sum1,f0=0,f1=0,p0=0,p1=0;
        for(int j=20;j>=0;j--){
            int np=p0+(1<<j),ns0=s0+t0.get(np),ns1=s1-t1.get(np);
            if(np>tot) continue;
            if(ns0<ns1){
                p0=np;
                s0=ns0,s1=ns1;
            }
        }
        f0=s0,s0=0,s1=sum1;
        if(p0<tot){
            f1=min(t0.query(p0+1),sum1-t1.query(p0+1));
            for(int j=20;j>=0;j--){
                int np=p1+(1<<j),ns0=s0+t0.get(np),ns1=s1-t1.get(np);
                if(np>tot) continue;
                if(ns0<ns1){
                    p1=np;
                    s0=ns0,s1=ns1;
                }else if(min(ns0,ns1)==f1){
                    p1=np;
                    s0=ns0,s1=ns1;
                }
            }
        }
        if(max(f0,f1)==0) cout<<"Peace\n";
        else if(f0>f1) cout<<a[p0]<<" "<<f0*2<<'\n';// 最小的能量消耗一定消耗完了，并且两边消耗同样做小
        else cout<<a[p1]<<" "<<f1*2<<'\n';
    }
    return 0;
}