#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15,INF=1e9;
int pre[MN][2],suf[MN][2],n,a[MN],L,R,ret1,ret2;


void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        char qwq;
        cin>>qwq;
        a[i]=qwq-'0';
    }
    
    for(int i=1;i<=n;i++){
        pre[i][0]=pre[i][1]=suf[i][0]=suf[i][1]=0;
    }


    for(int i=1;i<=n;i++){
        if(a[i]==1) continue;
        L=i;
        break;
    }
    for(int i=n;i>=1;i--){
        if(a[i]==1) continue;
        R=i;
        break;
    }


    for(int i=L-1;i<=R+1;i++){
        pre[i][0]=pre[i][1]=suf[i][0]=suf[i][1]=0;
    }

    for(int i=L,cnt0=0;i<=R;i++){
        if(a[i]==1){
            pre[i][0]=cnt0+pre[i-1][0];
            pre[i][1]=pre[i-1][1]+1;
            cnt0=0;
        }else{
            cnt0++;
            pre[i][0]=pre[i-1][0];
            pre[i][1]=pre[i-1][1];
        }
    }
    for(int i=R,cnt0=0;i>=L;i--){
        if(a[i]==1){
            suf[i][0]=cnt0+suf[i+1][0];
            suf[i][1]=suf[i+1][1]+1;
            cnt0=0;
        }else{
            cnt0++;
            suf[i][0]=suf[i+1][0];
            suf[i][1]=suf[i+1][1];
        }
    }

    ret1=INF;
    for(int i=L;i<=R;i++){
        ret1=min(ret1,pre[i][0]*2*(pre[i][1]>0)+pre[i][1]+(suf[i+1][0]*2*(suf[i+1][1]>0)+suf[i+1][1]));
    }
    ret1+=(L-1)+(n-R);

    for(int i=L-1;i<=R+1;i++){
        pre[i][0]=pre[i][1]=suf[i][0]=suf[i][1]=0;
    }

    // 1 cases
    L=1,R=n;
    for(int i=1;i<=n;i++){
        if(a[i]==0) continue;
        L=i;
        break;
    }
    for(int i=n;i>=1;i--){
        if(a[i]==0) continue;
        R=i;
        break;
    }
    for(int i=L,cnt0=0;i<=R;i++){
        if(a[i]==0){
            pre[i][0]=cnt0+pre[i-1][0];
            pre[i][1]=pre[i-1][1]+1;
            cnt0=0;
        }else{
            cnt0++;
            pre[i][0]=pre[i-1][0];
            pre[i][1]=pre[i-1][1];
        }
    }
    for(int i=R,cnt0=0;i>=L;i--){
        if(a[i]==0){
            suf[i][0]=cnt0+suf[i+1][0];
            suf[i][1]=suf[i+1][1]+1;
            cnt0=0;
        }else{
            cnt0++;
            suf[i][0]=suf[i+1][0];
            suf[i][1]=suf[i+1][1];
        }
    }
    ret2=INF;
    for(int i=L;i<=R;i++){
        ret2=min(ret2,pre[i][0]*2*(pre[i][1]>0)+pre[i][1]+(suf[i+1][0]*2*(suf[i+1][1]>0)+suf[i+1][1]));
    }
    ret2+=(L-1)+(n-R);
    cout<<min(ret1,ret2)<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}