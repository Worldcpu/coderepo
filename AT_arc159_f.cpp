#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15,MOD=998244353,INF=1e18;
int n,a[MN][2],f[MN],sumf[MN],num[MN],sum[MN],g[MN];
set<int> zs;

void initcdq(int l,int r){
    zs.clear();
    for(int i=l-1;i<=r;i++){
        num[a[i][0]]=num[a[i][1]]=0;
        sum[i]=0;
    }
}

void vote(int &cnt,int &nowzs,int val,int len){
    num[val]++;
    if(val==nowzs) cnt++;
    else if(cnt>0) cnt--;
    else{
        nowzs=val;
        cnt=1;
    } 
    if(num[val]*2>len){
        zs.insert(val);
    }
}

void cdq(int l,int r){
    if(l==r){
        if(a[l][0]==a[l][1]){
            f[l]=(f[l]-f[l-1]+MOD)%MOD;
        }
        f[l]=(f[l]+sumf[l-1])%MOD;
        sumf[l]=(sumf[l-1]+f[l])%MOD;
        return;
    }
    int mid=(l+r)>>1,cnt=0,nowzs=0;
    cdq(l,mid);
    initcdq(l,r);
    for(int i=mid;i>=l;i--){
        for(int j=1;j>=0;j--){
            vote(cnt,nowzs,a[i][j],(mid<<1)-(i<<1)+1-j+1);
        }
    }
    for(int i=l;i<=mid;i++){
        for(int j=0;j<=1;j++){
            num[a[i][j]]--;
        }
    }

    cnt=nowzs=0;
    for(int i=mid+1;i<=r;i++){
        for(int j=0;j<=1;j++){
            vote(cnt,nowzs,a[i][j],(i<<1)-(mid<<1)+j-1);
        }
    }
    for(int i=mid+1;i<=r;i++){
        for(int j=0;j<=1;j++){
            num[a[i][j]]--;
        }
    }
    for(auto x:zs){
        int L=INF,R=-INF;
        sum[l-1]=0;
        for(int i=l;i<=mid;i++){
            sum[i]=sum[i-1];
            for(int j=0;j<2;j++){
                if(a[i-1][j]==x) sum[i]++;
                else sum[i]--;
            }
            L=min(L,sum[i]);
            R=max(R,sum[i]);
        }
        for(int i=l;i<=mid;i++){
            g[sum[i]-L]=(g[sum[i]-L]+f[i-1])%MOD;
        }
        for(int i=1;i<=R-L;i++){
            g[i]=(g[i]+g[i-1])%MOD;
        }
        for(int i=0;i<2;i++){
            if(a[mid][i]==x) sum[mid]++;
            else sum[mid]--;           
        }
        for(int i=mid+1;i<=r;i++){
            sum[i]=sum[i-1];
            for(int j=0;j<2;j++){
                if(a[i][j]==x) sum[i]++;
                else sum[i]--;
            }
            if(sum[i]-1>=L&&sum[i]-1<=R){
                f[i]=(f[i]-g[sum[i]-L-1]+MOD)%MOD;
            }else if(sum[i]-1>R){
                f[i]=(f[i]-g[R-L]+MOD)%MOD;
            }
        }
        for(int i=0;i<=R-L;i++){
            g[i]=0;
        }
    }
    cdq(mid+1,r);
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i][0]>>a[i][1];
    }
    f[0]=sumf[0]=1;
    cdq(1,n);
    cout<<f[n];
    return 0;
}