#include<iostream>
#include<cstring>
#define ll long long
using namespace std;
int T;
const ll ML=20,mod=1e9+7,MZ=9*18+5;
int a[ML],f[ML][MZ];
ll dfs(int pos,bool limit,int sum){
    if(!pos){//递归边界为0
        return sum;
    }
    if(!limit&&~f[pos][sum]){//如果没有最高限制并且有记录
        return f[pos][sum];
    }
    int up;
    if(limit){//如果有最高位限制
        up=a[pos];
    }else up=9;//baka
    ll ret=0;
    for(int i=0;i<=up;i++){
        //要求当这个位取到最高位并且limit也是1才能往下继续limit
        ret=(ret+dfs(pos-1,limit&&i==up,sum+i))%mod;
    }
    if(!limit){//如果没有最高位限制就是一般性答案，可以记录
        f[pos][sum]=ret;
    }
    return ret;
}
ll solve(ll x){
    int len=0;
    while (x>0)
    {
        a[++len]=x%10;
        x/=10;
    }
    return dfs(len,true,0);
    //先从最高位开始，肯定有limit=1不然如果出来个不是9的最高位直接炸了
}
int main(){
    memset(f,-1,sizeof(f));
    cin>>T;
    while (T--)
    {
        ll l,r;
        cin>>l>>r;
        ll ans=(solve(r)-solve(l-1)+mod)%mod;
        cout<<ans<<endl;
    }
    
    return 0;
}