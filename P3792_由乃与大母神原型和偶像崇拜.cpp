#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
using namespace std;
constexpr int MN=1e6+15;
int n,m,tot,a[MN],b[MN],op[MN],x[MN],y[MN];
ull rd[MN],pre[MN];
mt19937 mt;

struct BITsum{
    int t[MN];

    int lowbit(int x){return x&-x;}

    int query(int x){
        int ret=0;
        while(x){
            ret+=t[x];
            x-=lowbit(x);
        }
        return ret;
    }

    void modify(int x,int k){
        while(x<MN){
            t[x]+=k;
            x+=lowbit(x);
        }
    }
}t1;

struct BITXor{
    ull t[MN];

    int lowbit(int x){
        return x&-x;
    }

    ull query(int x){
        int ret=0;
        while(x){
            ret^=t[x];
            x-=lowbit(x);
        }
        return ret;
    }

    void modify(int x,ull k){
        while(x<MN){
            t[x]^=k;
            x+=lowbit(x);
        }
    }

}t2;

signed main(){
    mt.seed(time(0));
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        b[++tot]=a[i];
        b[++tot]=a[i]+1;
    }
    for(int i=1;i<=m;i++){
        cin>>op[i]>>x[i]>>y[i];
        if(op[i]==1) b[++tot]=y[i]+1,b[++tot]=y[i];
    }
    sort(b+1,b+tot+1);
    tot=unique(b+1,b+1+tot)-b-1;
    rd[0]=mt();
    for(ull i=1,st=rd[0];i<=tot;i++){
        rd[i]=(st+=mt());
        pre[i]=pre[i-1]^rd[i];
    }
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(b+1,b+1+tot,a[i])-b;
        t1.modify(i,a[i]);
        t2.modify(i,rd[a[i]]);
    }
    for(int i=1;i<=m;i++){
        if(op[i]==1){
            y[i]=lower_bound(b+1,b+1+tot,y[i])-b;
            t1.modify(x[i],y[i]-a[x[i]]);
            t2.modify(x[i],rd[y[i]]^rd[a[x[i]]]);
            a[x[i]]=y[i];
        }else{
            int mid=(t1.query(y[i])-t1.query(x[i]-1))/(y[i]-x[i]+1);
            int l,r;
            l=mid-(y[i]-x[i])/2;
            if((y[i]-x[i])&1) r=mid+(y[i]-x[i])/2+1;
            else r=mid+(y[i]-x[i])/2;
            if(l<=0||r>=tot) cout<<"yuanxing\n";
            else if((t2.query(y[i])^t2.query(x[i]-1))==(pre[r]^pre[l-1])){
                cout<<"damushen\n";
            } else cout<<"yuanxing\n";
        }
    }
    return 0;
}
