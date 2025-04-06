#include<bits/stdc++.h>
#define ls p<<1
#define rs p<<1|1
#define ll long long
using namespace std;
const int MN=3e5+15,MA=1e6+15;
template<typename type>
inline void read(type &x)
{
    x=0;bool flag(0);char ch=getchar();
    while(!isdigit(ch)) flag=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    flag?x=-x:0;
}
struct segtree{
    int l,r;
    bool isok;
    ll sum; 
}t[MN<<2];
ll a[MN];
int n,m;

//https://wenku.baidu.com/view/9e336795bb4cf7ec4afed057.html?_wkts_=1739964897460&needWelcomeRecommand=1
//对于任意正整数n,有d(n)<=sqrt(3*n)
//对于n>1260，有d(n)<sqrt(n)

//d是约数个数，时间复杂度线性筛O(n)
// num是最小素因子个数，用于筛约数
int d[MA],num[MA];
vector<bool> vis(MA);
vector<int> prime;

void pushup(int p){
    t[p].sum=t[ls].sum+t[rs].sum;
    if(t[ls].isok==1&&t[rs].isok==1){
        t[p].isok=1;
    }
}

void build(int p,int l,int r){
    t[p].l=l;
    t[p].r=r;
    if(l==r){
        t[p].sum=a[l];
        if(t[p].sum==1||t[p].sum==2){
            t[p].isok=1;
        }
        return;
    }
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(p);
}

void update(int p,int fl,int fr){
    if(t[p].isok) return;
    if(t[p].l==t[p].r){
        t[p].sum=d[t[p].sum];
        if(t[p].sum==1||t[p].sum==2) t[p].isok=1;
        return;
    }
    int mid=t[p].l+t[p].r>>1;
    if(mid>=fl) update(ls,fl,fr);
    if(mid<fr) update(rs,fl,fr);
    pushup(p);
}

ll query(int p,int fl,int fr){
    if(t[p].l>=fl&&t[p].r<=fr){
        return t[p].sum;
    }
    ll ret=0;
    int mid=t[p].l+t[p].r>>1;
    if(mid>=fl)ret+=query(ls,fl,fr);
    if(mid<fr) ret+=query(rs,fl,fr);
    return ret;
}

void getd(){
    d[1]=1;
    for(int i=2;i<MA;i++){
        if(!vis[i]){
            prime.push_back(i);
            d[i]=2;
            num[i]=1;
        }
        for(int j=0;1ll*i*prime[j]<MA&&j<prime.size();j++){
            vis[i*prime[j]]=1;
            if(i%prime[j]==0){
                num[i*prime[j]]=num[i]+1;
                d[i*prime[j]]=d[i]/(num[i]+1)*(num[i*prime[j]]+1);
                
                break;
            }else{
                d[i*prime[j]]=d[i]*2;
                num[i*prime[j]]=1;
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    getd();
    read(n);
    read(m);
    for(int i=1;i<=n;i++){
        read(a[i]);
    }
    int op,x,y;
    build(1,1,n);
    while (m--)
    {
        read(op);
        read(x);
        read(y);
        if(op==1){
            update(1,x,y);
        }else{
            cout<<query(1,x,y)<<'\n';
        }
    }
    
}
