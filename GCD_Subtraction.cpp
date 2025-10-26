#include<bits/stdc++.h>
#define int long long
using namespace std;
int a,b,ans;

void calc(int x){
    int ret=b;
    for(int i=2;i*i<=x;i++){
        if(x%i==0){
            if(a%i==b%i) ret=min(ret,a%i);
            if(a%(x/i)==b%(x/i)) ret=min(ret,a%(x/i));
        }
    }
    if(a%x==b%x){
        ret=min(ret,a%x);
    }
    a-=ret;
    b-=ret;
    ans+=ret;
}

void solve(){
    while(a>0&&b>0){
        if(a<b) swap(a,b);
        int gcdd=gcd(a,b);
        a/=gcdd,b/=gcdd;
        if(a==0||b==0) break;
        if(a==b){
            ans++;
            break;
        }
        if(a==b+1){
            ans+=b;
            break;
        }
        calc(a-b);
    }
}

signed main(){
    cin>>a>>b;
    solve();
    cout<<ans;

    return 0;
}