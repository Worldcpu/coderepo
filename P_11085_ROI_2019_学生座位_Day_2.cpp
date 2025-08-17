#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15,INF=1e18;;
int n,m,K,ans,h[MN];
pir qj[MN];
vector<int> pos[MN];

void cdq(int l,int r,int fl,int fr){
    if(l>r) return;
    int mid=(l+r)>>1;
    int pre=0,suf=0,ql=0,qr=0,nxtl=0,nxtr=pos[mid].size(),fmid=fl,ret=INF;
    for(auto p:pos[mid]) suf+=p;
    for(int i=fl;i<=fr;i++){
        if(qj[i].second<=qj[i-1].second) continue;
        while(ql<pos[mid].size()&&pos[mid][ql]<=qj[i].first){
            pre+=pos[mid][ql];
            ql++;
            nxtl++;
        }
        while(qr<pos[mid].size()&&pos[mid][qr]<qj[i].second){
            suf-=pos[mid][qr];
            qr++;
            nxtr--;
        }
        int tmp=suf-qj[i].second*nxtr+qj[i].first*nxtl-pre;
        if(tmp<ret){
            fmid=i;
            ret=tmp;
        }
    }
    ans+=ret;
    cdq(l,mid-1,fl,fmid);
    cdq(mid+1,r,fmid,fr);
}

signed main(){
    cin>>m>>n>>K;
    for(int i=1;i<=K;i++){
        cin>>qj[i].first>>qj[i].second;
    }
    sort(qj+1,qj+1+K);
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n<<1;j++){
            cin>>h[j];
        }
        sort(h+1,h+1+(n<<1));
        for(int j=1;j<=n;j++){
            pos[j].push_back(h[j*2-1]);
            pos[j].push_back(h[j*2]);
        }
    }
    for(int i=1;i<=n;i++){
        sort(pos[i].begin(),pos[i].end());
    }
    cdq(1,n,1,K);
    cout<<ans;
    return 0;
}