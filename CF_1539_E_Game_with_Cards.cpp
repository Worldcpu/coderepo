#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15,INF=1e9;
int L[2],R[2]={INF,INF},isok[2],pre[MN][2],K[MN],l[MN][2],r[MN][2],lst[2],n,m;
bool both[2];

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>K[i]>>l[i][0]>>r[i][0]>>l[i][1]>>r[i][1];
    }
    lst[0]=lst[1]=n+1;
    isok[0]=isok[1]=1;
    R[0]=R[1]=m;
    for(int i=n;i>=1;i--){
        if(K[i]>=l[i][0]&&K[i]<=r[i][0]) isok[0]&=1;
        else isok[0]&=0;
        if(K[i]>=l[i][1]&&K[i]<=r[i][1]) isok[1]&=1;
        else isok[1]&=0;
        L[0]=max(L[0],l[i][0]);
        L[1]=max(L[1],l[i][1]);
        R[0]=min(R[0],r[i][0]);
        R[1]=min(R[1],r[i][1]);
        if(isok[0]&&K[i-1]>=L[1]&&K[i-1]<=R[1]) both[0]=1;
        else both[0]=0;
        if(isok[1]&&K[i-1]>=L[0]&&K[i-1]<=R[0]) both[1]=1;
        else both[1]=0;

        if(both[0]) pre[i][0]=lst[1];
        if(both[1]) pre[i][1]=lst[0];

        if(both[0]) lst[0]=i,isok[1]=1,L[0]=0,R[0]=m;
        if(both[1]) lst[1]=i,isok[0]=1,L[1]=0,R[1]=m;
    }
    if(lst[0]>1&&lst[1]>1){
        cout<<"No";
        return 0;
    }
    cout<<"Yes\n";
    int pos=(lst[0]>1?1:0);
    for(int i=1;i<=n;i=pre[i][pos],pos^=1){
        for(int j=i;j<pre[i][pos];j++) cout<<pos<<' ';
    }

    return 0;
}