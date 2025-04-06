#include<bits/stdc++.h>
#define ll long long
#define pir pair<ll,int>
#define lpir pair<ll,ll>
using namespace std;
const int MN=1e5+15,ML=30;
const ll INF=1e18;
set<pir> s;
vector<pir> vg;
int n,h[MN],x0,m;
ll f[ML][MN][2],da[ML][MN][2],db[ML][MN][2],ga[MN],gb[MN];

template<typename type>
inline void read(type &x)
{
    x=0;bool flag(0);char ch=getchar();
    while(!isdigit(ch)) flag=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    flag?x=-x:0;
}

void initg(){
    s.insert(pir(INF,0));
    s.insert(pir(-INF,0));
    s.insert(pir(INF+1,0));
    s.insert(pir(-INF-1,0));
    for(int i=n;i>=1;i--){
        ll minn=INF+5,cmin=INF+5,c1=0,c2=0;
        auto it=s.lower_bound(pir(h[i],i));
        it++;
        vg.clear();
        for(int j=1;j<=4;j++){
            vg.push_back(*it);
            it--;
        }
        for(int j=3;j>=0;j--){
            pir p=vg[j];
            ll dis=abs(p.first-h[i]);
            if(dis<minn){
                cmin=minn;
                minn=dis;
                c2=c1;
                c1=p.second;
            }else if(dis<cmin){
                cmin=dis;
                c2=p.second;
            }
        }
        s.insert(pir(h[i],i));
        ga[i]=c2;
        gb[i]=c1;
    }
}

pair<ll,ll> clac(int s,int x){
    ll la=0,lb=0,p=s;
    for(int i=20;i>=0;i--){
        if(f[i][p][0]&&la+lb+da[i][p][0]+db[i][p][0]<=x){
            la+=da[i][p][0];
            lb+=db[i][p][0];
            p=f[i][p][0];
        }
    }
    return {la,lb};
}

int main(){
    read(n);
    for(int i=1;i<=n;i++){
        read(h[i]);
    }
    initg();
    for(int i=1;i<=n;i++){
        f[0][i][0]=ga[i];
        f[0][i][1]=gb[i];
        
        da[0][i][0]=abs(h[i]-h[ga[i]]);
        db[0][i][1]=abs(h[i]-h[gb[i]]);
    }
    for(int i=1;i<=20;i++){
        for(int j=1;j<=n;j++){
            for(int k=0;k<=1;k++){
                if(i==1){
                    f[1][j][k]=f[0][f[0][j][k]][1-k];
                    da[1][j][k]=da[0][j][k]+da[0][f[0][j][k]][1-k];
                    db[1][j][k]=db[0][j][k]+db[0][f[0][j][k]][1-k];
                }else{
                    f[i][j][k]=f[i-1][f[i-1][j][k]][k];
                    da[i][j][k]=da[i-1][j][k]+da[i-1][f[i-1][j][k]][k];
                    db[i][j][k]=db[i-1][j][k]+db[i-1][f[i-1][j][k]][k];
                }
            }
        }
    }
    ll ans=0;
    double dmin=INF;
    read(x0);
    for(int i=1;i<=n;i++){
        lpir p=clac(i,x0);
        ll la=p.first,lb=p.second;
        double ret=lb?la*1.0/lb:INF;
        if(ret<dmin||(ret==dmin&&h[i]>h[ans])){
            ans=i;
            dmin=ret;
        }
    }
    cout<<ans<<'\n';
    read(m);
    while (m--)
    {
        ll x,y;
        cin>>x>>y;
        pir pc=clac(x,y);
        cout<<pc.first<<" "<<pc.second<<'\n';
    }
    
    return 0;
}

