#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
int n,K[MN],g[MN],r[MN];
map<int,int> mp;


int phi(int n){

    int ans=n;

    for(int i=2;i*i<=n;i++){

        if(n%i==0){

            ans=ans/i*(i-1);

            while (n%i==0)

            {

                n/=i;

            }

        }

    }

    if(n>=2){

        ans=ans/n*(n-1);

    }

    return ans;

}

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

int exgcd(int a,int b,int &x,int &y){
    if(!b){
        x=1,y=0;
        return a;
    }
    int d=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
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
    for(int i=0;i<=t;i++){
        int val=qpow(a,i,p);
        int j=mp.find(val)==mp.end()?-1:mp[val];
        if(j>=0&&i*t-j>=0) return i*t-j;
    }
    return -1e9;
}

int exBSGS(int a,int b,int p){
    a%=p,b%=p;
    if(b==1||p==1) return 0;
    int d,ax=1,cnt=0,x,y;
    while((d=exgcd(a,p,x,y))^1){
        if(b%d) return -1;
        b/=d,p/=d;
        cnt++;
        ax=1ll*ax*(a/d)%p;
        if(ax==b) return cnt;
    }

    exgcd(ax,p,x,y);
    int inv=(x%p+p)%p;
    b=1ll*b*inv%p;
    return BSGS(a,b,p)+cnt;
}

int getjie(int m,int a){
    a%=m;
    if(__gcd(a,m)>1) return -1;
    if(a==1) return 1;
    int ret=phi(m),num=ret;
    for(int i=2;i*i<=num;i++){
        if(num%i==0){
            while(num%i==0&&qpow(a,ret/i,m)==1){
                ret/=i;
                num/=i;
            }
            while(num%i==0) num/=i;
        }
        if(num>1&&qpow(a,ret/num,m)==1) ret/=num;
        return ret;
    }
    return ret;
}

int findj(int a,int b,int MOD){
    int gcdd=__gcd(b,MOD);
    MOD/=gcdd;
    if(__gcd(a,MOD)>1) return 1e9;
    return getjie(MOD,a);
}


int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>K[i]>>g[i]>>r[i];
    }
    for(int i=1;i<)
    return 0;
}
