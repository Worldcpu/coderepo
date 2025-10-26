#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15;
int n,a[MN],b[MN],c[MN],sum1[MN],sum2[MN],p1tot,p2tot,p3tot,sumc,ans;
pir p1[MN],p2[MN],p3[MN];


bool cmp(pir x,pir y){
    return x.first<y.first;
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    for(int i=1;i<=n;i++){
        cin>>c[i];
    }
    for(int i=1;i<=n;i++){
        if(a[i]) sumc+=c[i];       
        if(!a[i]&&b[i]) p1[++p1tot]=pir(c[i],i);
        if(a[i]&&!b[i]) p2[++p2tot]=pir(c[i],i);
        if(a[i]&&b[i]) p3[++p3tot]=pir(c[i],i);
    }
    sort(p1+1,p1+1+p1tot,cmp);
    sort(p2+1,p2+1+p2tot);
    sort(p3+1,p3+1+p3tot,cmp);

    sum1[0]=sumc;
    for(int i=1;i<=p1tot;i++){
        sumc-=p1[i].first;
        sum1[i]=sumc;
        ans+=sumc;
    }
    sum2[0]=sumc;
    for(int i=1;i<=p2tot;i++){
        sumc-=p2[i].first;
        sum2[i]=sumc;
        ans+=sumc;
    }
    
    int cur=ans;
    for(int i=1,cnt=0;i<=p3tot;i++){
        int it1=lower_bound(sum1,sum1+1+p1tot,p3[i].first)-sum1-1,it2=upper_bound(sum2,sum2+1+p2tot,p3[i].first)-sum2-1;
        cur+=sum1[it1]-cnt-p3[i].first-(p1tot-it1)*p3[i].first;
        cnt+=p3[i].first;
        cur+=sum2[it2]-cnt+p3[i].first-it2*p3[i].first;
        ans=min(ans,cur);
    }
    cout<<ans;
    return 0;
}