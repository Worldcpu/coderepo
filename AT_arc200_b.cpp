#include<bits/stdc++.h>
#define int long long
using namespace std;
int a1,a2,a3;

void solve(){
    cin>>a1>>a2>>a3;
    if(a3<max(a1,a2)||a3>a1+a2){
        cout<<"No\n";
        return;
    }
    cout<<"Yes\n";
    if(a3==a1+a2){
        int x=1,y=1;
        for(int i=1;i<=a1;i++) x*=10;
        for(int i=1;i<=a2;i++) y*=10;
        for(int i=1;i<=10;i++){
            for(int j=1;j<=10;j++){
                if(gcd(x-i,y-j)==1){
                    cout<<x-i<<' '<<y-j<<'\n';
                    return;
                }
            }
        }
    }else{
        string x="1",y="1";
        for(int i=1;i<a1;i++) x+="0";
        for(int i=1;i<a2;i++) y+="0";
        if(a1>a2){
            x[x.size()-(a1+a2-a3)]='1';
        }else{
            y[y.size()-(a1+a2-a3)]='1';
        }
        cout<<x<<' '<<y<<'\n';
    }

}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}