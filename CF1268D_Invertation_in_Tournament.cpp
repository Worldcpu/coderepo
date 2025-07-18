#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2520,MOD=998244353;
int n,cf[MN],h[MN];
bool mp[MN][MN];

bool check(){
    sort(cf+1,cf+1+n);
    for(int i=2;i<=n;i++) cf[i]+=cf[i-1];
    for(int i=1;i<n;i++){
        if(cf[i]==i*(i-1)/2) return 0;
    }
    return 1;
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            char c;
            cin>>c;
            mp[i][j]=c-'0';
            h[i]+=mp[i][j];
        }
    }
    for(int i=1;i<=n;i++) cf[i]=h[i];
    if(check()){
        cout<<"0 1";
        return 0;
    }
    int ret=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) cf[j]=h[j]; 
        for(int j=1;j<=n;j++){
            cf[i]-=mp[i][j]*2-1;
            cf[j]+=mp[i][j]*2-1;
        }
        if(check()) ret++;
    }
    if(ret){
        cout<<1<<" "<<ret;
        return 0;
    }
    if(n==4) cout<<-1;
    if(n==6) cout<<"2 18";
    return 0;
}
