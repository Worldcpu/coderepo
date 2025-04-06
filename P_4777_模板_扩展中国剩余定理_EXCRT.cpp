#include<iostream>
#define ll long long
using namespace std;
const int MN=1e5+15;
ll md[MN],b[MN],mt;
int n;
ll slowti(ll a,ll b,ll mod){
    ll ret=0;
    while (b>0)
    {
        if(b&1) ret=(ret+a)%mod;
        a=(a+a)%mod;
        b>>=1;
    }
    return ret;
}
ll exgcd(ll a,ll b,ll &x,ll &y){
    if(!b){
        x=1;
        y=0;
        return a;
    }
    ll ret=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return ret;
}
ll excrt(){
    //求解线性同余方程组，返回最小正整数解
    ll x,y;
    ll m1=md[1],b1=b[1];//第一个方程
    ll ans=(b1%m1+m1)%m1;//战术取模
    for(int i=2;i<=n;i++){
        ll m2=md[i],b2=b[i];//取出一个方程
        //合并为ax+by=c
        ll a=m1,b=m2,c=(b2-b1%m2+m2)%m2;
        ll d=exgcd(a,b,x,y);
        if(c%d!=0){//有裴蜀定理可知若不能整除GG
            return -1;
        }
        x=slowti(x,c/d,b/d);//由通解式求最小解x
        ans=b1+x*m1;//代回第一个原式求得特解x
        m1=m2/d*m1;//合并后的新m1
        ans=(ans%m1+m1)%m1;
        b1=ans;
        //取余
    }
    return ans;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>md[i]>>b[i];
    }
    cout<<excrt();
    return 0;
}