#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15,INF=1e9;
int n,K,L,a[MN],b[MN],now,ans,taga[MN],tagb[MN];
priority_queue<pir> qab,qa,qb,qa2,qb2;

void init(){
    while(!qa.empty()) qa.pop();
    while(!qb.empty()) qb.pop();
    while(!qab.empty()) qab.pop();
    while(!qa2.empty()) qa2.pop();
    while(!qb2.empty()) qb2.pop();
    ans=0,now=K-L;
    for(int i=1;i<=n;i++){
        taga[i]=tagb[i]=0;
    }
}

void seta(int x){
    taga[x]=1;
    if(!tagb[x]) qb2.push(pir(b[x],x));
}

void setb(int x){
    tagb[x]=1;
    if(!taga[x]) qa2.push(pir(a[x],x));
}

void solve(){
    cin>>n>>K>>L;
    init();
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }

    for(int i=1;i<=n;i++){
        qa.push(pir(a[i],i));
        qb.push(pir(b[i],i));
        qab.push(pir(a[i]+b[i],i));   
    }
    qa.push(pir(-INF,0));
    qb.push(pir(-INF,0));
    qab.push(pir(-INF,0));
    qa2.push(pir(-INF,0));
    qb2.push(pir(-INF,0));
    while(K--){
        while(taga[qa.top().second]) qa.pop();
        while(tagb[qb.top().second]) qb.pop();
        while(taga[qa2.top().second]) qa2.pop();
        while(tagb[qb2.top().second]) qb2.pop();
        while(taga[qab.top().second]||tagb[qab.top().second]) qab.pop();
        auto nowa=qa.top(),nowb=qb.top(),nowab=qab.top(),nowa2=qa2.top(),nowb2=qb2.top();
        int op=1,mx=nowab.first;
        if(mx<nowa2.first+nowb2.first) mx=nowa2.first+nowb2.first,op=3;
        if(mx<nowa2.first+nowb.first) mx=nowa2.first+nowb.first,op=4;
        if(mx<nowa.first+nowb2.first) mx=nowa.first+nowb2.first,op=5;
        if(nowa.second!=nowb.second&&L&&mx<nowa.first+nowb.first) mx=nowa.first+nowb.first,op=2;
        ans+=mx;
        if(op==1){
            seta(nowab.second);
            setb(nowab.second);
        }
        if(op==2){
            seta(nowa.second);
            setb(nowb.second);
            L--;
        }
        if(op==3){
            seta(nowa2.second);
            setb(nowb2.second);
            L++;
        }
        if(op==4){
            seta(nowa2.second);
            setb(nowb.second);
        }
        if(op==5){
            seta(nowa.second);
            setb(nowb2.second);
        }
    }
    cout<<ans<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}