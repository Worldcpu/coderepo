#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15;
int n,p,s,a[MN],b[MN],ans,vis[MN];
priority_queue<pir> qa,qb,qba;


int main(){
    cin>>n>>p>>s;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        qa.push(pir(a[i],i));
    }
    while(p--){
        auto tp=qa.top();
        qa.pop();
        vis[tp.second]=1;
        ans+=tp.first;
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
        if(vis[i]) qba.push(pir(b[i]-a[i],i));
        else qb.push(pir(b[i],i));
    }
    while(s--){
        while(!qa.empty()&&vis[qa.top().second]) qa.pop();
        while(!qb.empty()&&vis[qb.top().second]) qb.pop();
        auto nowa=qa.top(),nowb=qb.top(),nowba=qba.top();
        if(nowb.first>nowa.first+nowba.first){
            ans+=nowb.first;
            vis[nowb.second]=2;
            qb.pop();
        }else{
            ans+=nowa.first+nowba.first;
            vis[nowa.second]=1;
            vis[nowba.second]=2;
            qba.pop();
            qba.push(pir(b[nowa.second]-a[nowa.second],nowa.second));
            qa.pop();
        }
    }
    cout<<ans<<'\n';
    for(int i=1;i<=n;i++){
        if(vis[i]==1) cout<<i<<' ';
    }
    cout<<'\n';
    for(int i=1;i<=n;i++){
        if(vis[i]==2) cout<<i<<' ';
    }

    return 0;
}