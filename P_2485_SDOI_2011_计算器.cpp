#include<bits/stdc++.h>
#define int long long
using namespace std;
map<int,int> mp;

int qpow(int a,int b,int MOD){
    int ret=1;
    while(b){
        if(b&1){
            ret=ret*a%MOD;
        }
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

int BSGS(int a,int b,int p){
    mp.clear();
    b%=p;
    int t=sqrt(p)+1;
    for(int j=0;j<t;j++){
        int val=b*qpow(a,j,p)%p;
        mp[val]=j;
    }
    a=qpow(a,t,p);
    if(a==0) return b==0?1:-1;
    for(int i=0;i<t;i++){
        int val=qpow(a,i,p);
        int j=mp.find(val)==mp.end()?-1:mp[val];
        if(j>=0&&i*t-j>=0) return i*t-j;
    }
    return -1;
}

void exgcd(int a,int b,int &x,int &y){
    if(!b){
        x=1,y=0;
        return;
    }
    exgcd(b,a%b,y,x);
    y-=a/b*x;
}

void solve1(){
    int a,b,p;
    cin>>a>>b>>p;
    cout<<qpow(a,b,p)<<'\n';
}

void solve2(){
    int y,z,p,x1,y1;
    cin>>y>>z>>p;
    if(z%gcd(y,p)!=0){
        cout<<"Orz, I cannot find x!\n";
    }else{
        exgcd(y,p,x1,y1);
        int gcdd=gcd(y,p),t=p/gcdd;
        x1=(((x1*z)/gcdd)%t+t)%t;
        cout<<x1<<'\n';
    }
}

void solve3(){
    int y,z,p;
    cin>>y>>z>>p;
    int ret=BSGS(y,z,p);
    if(ret==-1) cout<<"Orz, I cannot find x!\n";
    else cout<<ret<<'\n';
}

signed main(){
    int T,k;
    cin>>T>>k;
    while(T--){
        if(k==1) solve1();
        else if(k==2) solve2();
        else solve3();
    }
    return 0;
}
