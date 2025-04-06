#include<iostream>
#include<cstring>
#define ll long long
using namespace std;
const int mod=1e7+7,MN=110;
ll f[MN][MN],a[MN];
ll dfs(int pos,bool limit,int cnt){
    if(!pos){
        return max(cnt,1);
    }
    if(!limit&&~f[pos][cnt]){
        return f[pos][cnt];
    }
    ll up,ret=1;
    if(limit){
        up=a[pos];
    }else up=1;
    for(int i=0;i<=up;i++){
        ret=(ret*dfs(pos-1,limit&&i==up,cnt+(i==1)))%mod;
    }
    if(!limit){
        f[pos][cnt]=ret;
    }
    return ret;
}
ll solve(ll x){
    int len=0;
    while (x>0)
    {
        a[++len]=x%2;
        x/=2;
    }
    return dfs(len,true,0);
}
int main(){
    memset(f,-1,sizeof(f));
    ll x;
    cin>>x;
    cout<<solve(x);
    return 0;
}