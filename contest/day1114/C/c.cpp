#include<bits/stdc++.h>
#define double long double
#define int long long
using namespace std;
constexpr int MN=5e5+15,ML=20;
struct Query{
    int op,pos;
}qry[MN];
int n,K[MN],B[MN],dtot,ftot;
double fg[MN];


struct BIT{
    int t[MN];

    int lowbit(int x){
        return x&-x;
    }

    void modify(int x,int k){
        while(x<MN){
            t[x]+=k;
            x+=lowbit(x);
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

    int getp(){
        int p=0,tmp=0;
        for(int i=ML;i>=0;i--){
            int np=p+(1<<i);
            if(np<MN&&tmp+t[np]<0){
                p=np;
                tmp+=t[np];
            }
        }
        return p;
    }

}bit[2];

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>qry[i].op;
        if(qry[i].op==1){
            int f,t,b;
            cin>>f>>t>>b;
            K[++dtot]=-t;
            B[dtot]=f*t+b;
            qry[i].pos=dtot;
        }else{
            cin>>qry[i].pos;
        }
    }
    for(int i=1;i<=dtot;i++){
        if(K[i]<0){
            K[i]=-K[i];
            B[i]=-B[i];
        }
        if(K[i]!=0){
            fg[++ftot]=-1.0*B[i]/K[i];
        }
    }
    sort(fg+1,fg+1+ftot);
    ftot=unique(fg+1,fg+1+ftot)-fg-1;
    for(int i=1;i<=n;i++){
        auto now=qry[i];
        if(now.op==1){
            if(K[now.pos]){
                auto p=lower_bound(fg+1,fg+1+ftot,-1.0*B[now.pos]/K[now.pos])-fg;
                bit[0].modify(1,-K[now.pos]);
                bit[0].modify(p+1,2*K[now.pos]);
                bit[1].modify(1,-B[now.pos]);
                bit[1].modify(p+1,2*B[now.pos]);
            }else{
                bit[1].modify(1,abs(B[now.pos]));
            }
        }else{
            if(K[now.pos]){
                auto p=lower_bound(fg+1,fg+1+ftot,-1.0*B[now.pos]/K[now.pos])-fg;
                bit[0].modify(1,K[now.pos]);
                bit[0].modify(p+1,-2*K[now.pos]);
                bit[1].modify(1,B[now.pos]);
                bit[1].modify(p+1,-2*B[now.pos]);
            }else{
                bit[1].modify(1,-1*abs(B[now.pos]));
            }
        }
        auto p=bit[0].getp();
        cout<<fixed<<setprecision(6)<<fg[p]*bit[0].query(p)+bit[1].query(p)<<'\n';
    }
    return 0;
}