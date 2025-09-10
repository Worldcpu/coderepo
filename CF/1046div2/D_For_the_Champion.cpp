#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=150,MID=1e9;
int n,x[MN],y[MN],ma,mb,reta,retb;

int getans(char op,int k){
    cout<<"? "<<op<<' '<<k<<endl;
    cout.flush();
    int ret;
    cin>>ret;
    return ret;
}

void init(){
    ma=mb=2e9;
}

void solve(){
    cin>>n;
    init();
    for(int i=1;i<=n;i++){
        cin>>x[i]>>y[i];
        ma=min(ma,x[i]+y[i]);
        mb=min(mb,y[i]-x[i]);
    }
    getans('L',MID);
    getans('L',MID);
    getans('D',MID);
    reta=getans('D',MID);
    getans('R',MID);
    getans('R',MID);
    getans('R',MID);
    retb=getans('R',MID);
    reta=ma-reta+4*MID;
    retb=mb-retb+4*MID;
    cout<<"! "<<(reta-retb)/2<<' '<<(reta+retb)/2<<endl;
    cout.flush();
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}