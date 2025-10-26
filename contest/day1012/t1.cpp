#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e5+15;
int nxta[MN],nxtb[MN],n,q;
pir a[MN];

void initnxt(){
    for(int i=1,it=1;i<=n;i++){
        it=max(it,i);
        while(it<=n&&a[it].first==a[i].first) it++;
        nxta[i]=it;
    }
    for(int i=1,it=1;i<=n;i++){
        it=max(it,i);
        while(it<=n&&a[it].second==a[i].second) it++;
        nxtb[i]=it;
    }
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i].first>>a[i].second;
    }
    initnxt();
    for(int i=1;i<=n;i++) cerr<<nxta[i]<<' '<<nxtb[i]<<'\n';
    cin>>q;
    while(q--){
        int l,r;
        cin>>l>>r;
        if(nxta[l]>r||nxtb[l]>r){
            cout<<"0 0\n";
        }else if(a[l].second!=a[nxta[l]].second){
            cout<<l<<' '<<nxta[l]<<'\n';
        }else if(a[l].first!=a[nxtb[l]].first){
            cout<<l<<' '<<nxtb[l]<<'\n';
        }else cout<<nxta[l]<<' '<<nxtb[l]<<'\n';
    }
    return 0;
}