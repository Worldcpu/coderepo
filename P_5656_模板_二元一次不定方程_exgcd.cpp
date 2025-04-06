#include<iostream>
#include<cmath>
#define ll long long
using namespace std;
int T;
ll exgcd(ll a,ll b,ll &x,ll &y){
    if(!b){
        x=1;
        y=0;
        return a;
    }
    ll d=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return d;//这里求出的是gcd(a,b)
}
int main(){
    cin>>T;
    while (T--)
    {
        ll a,b,c,x,y;
        cin>>a>>b>>c;
        ll d=exgcd(a,b,x,y);
        if(c%d!=0){//不能整除方程无解
            cout<<-1<<endl;
            continue;
        }
        x=x*c/d,y=y*c/d;//求x0和y0
        ll tx=b/d,ty=a/d;
        ll k=ceil((1.0-x)/tx);
        x+=tx*k;
        y-=ty*k;
        if(y<=0){
            ll ansy=y+ty*(ll)1*ceil((1.0-y)/ty);
            cout<<x<<" "<<ansy<<endl;
        }else{
            cout<<(y-1)/ty+1<<" "<<x<<" "<<(y-1)%ty+1<<" "<<x+(y-1)/ty*tx<<" "<<y<<endl;
        }
    }
    
    return 0;
}