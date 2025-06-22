#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=9e5+15,MOD=998244353;
int n,tot,f[MN][2],a[MN],b[MN];
vector<int> pos[MN];

struct BIT{
    int t[MN];
    int lowbit(int x){return x&-x;}
    void modify(int x,int k){while(x<MN){(t[x]+=k)%=MOD;x+=lowbit(x);}}
    int query(int x){int ret=0;while(x){(ret+=t[x])%=MOD;x-=lowbit(x);}return ret;}
    int query(int l,int r){if(l>r)return 0;return (query(r)-query(l-1)+MOD)%MOD;}
}t1,t2;

int ksm(int a,int b){int ret=1;while(b){if(b&1)ret=ret*a%MOD;a=a*a%MOD;b>>=1;}return ret;}
int inv(int x){return ksm(x,MOD-2);}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){cin>>a[i];b[i]=a[i];}
    sort(b+1,b+1+n);
    tot=unique(b+1,b+1+n)-b-1;
    for(int i=1;i<=n;i++){a[i]=lower_bound(b+1,b+1+tot,a[i])-b;pos[a[i]].push_back(i);}
    for(auto p:pos[1]){t1.modify(p,p);t2.modify(p,1);}
    int sum=0,cnth=pos[1].size();
    for(int i=2;i<=tot;i++){
        int f1=0;
        for(auto p:pos[i]){
            int fl=(p*t2.query(1,p)%MOD-t1.query(1,p)+MOD)%MOD;
            int fr=(t1.query(p,n)-p*t2.query(p,n)%MOD+MOD)%MOD;
            f[p][1]=(fl+fr+sum)%MOD*inv(cnth)%MOD;
            f1=(f1+f[p][1])%MOD;
        }
        for(auto p:pos[i]){t1.modify(p,p);t2.modify(p,1);}
        cnth+=pos[i].size();
        for(auto p:pos[i]){
            int fl=(p*t2.query(1,p-1)%MOD-t1.query(1,p-1)+MOD)%MOD;
            int fr=(t1.query(p+1,n)-p*t2.query(p+1,n)%MOD+MOD)%MOD;
            f[p][0]=(fl+fr+sum+(f1-f[p][1]+MOD)%MOD)%MOD*inv(cnth-1)%MOD;
        }
        for(auto p:pos[i]){sum=(sum+f[p][0])%MOD;}
    }
    cout<<f[pos[tot][0]][0]<<endl;
    return 0;
}
