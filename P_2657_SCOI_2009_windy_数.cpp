#include<iostream>
#include<cstring>
#define ll long long
using namespace std;
const int MN=15,INF=1e9+7;
int f[MN][MN],a[MN];
//f[pos,last]表示[pos+1,len]都已经填写，且pos+1位填写的是last
//的windy数数量，即以last开头的windy数的数量
ll dfs(int pos,bool limit,bool lead0,int last){
    if(!pos) return 1;
    if(!limit&&last!=INF&&~f[pos][last]){
        return f[pos][last];
    }
    int up,ret=0;
    if(limit){
        up=a[pos];
    }else up=9;
    for(int i=0;i<=up;i++){
        if(lead0){//如果是前导0表示还没填数，不能约束下一个数！
            ret=ret+dfs(pos-1,limit&&i==up,lead0&&i==0,i==0 ? last : i);
        }else if(abs(last-i)>=2){
            ret=ret+dfs(pos-1,limit&&i==up,0,i);
        }
    }
    if(!limit&&last!=INF){
        f[pos][last]=ret;
    }
    return ret;
}
int solve(ll x){
    int len=0;
    while (x>0)
    {
        a[++len]=x%10;
        x/=10;
    }
    return dfs(len,1,1,INF);
}
int main(){
    memset(f,-1,sizeof(f));
    ll l,r;
    cin>>l>>r;
    cout<<solve(r)-solve(l-1);
    return 0;
}