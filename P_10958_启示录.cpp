#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=20;
int a[MN],T;
ll f[MN][2][2];

ll dfs(int pos,bool lt1,bool lt2,bool lim){
    if(!pos) return 1;
    if(!lim&&~f[pos][lt1][lt2]) return f[pos][lt1][lt2];
    int up;
    if(lim) up=a[pos];
    else up=9;
    ll ret=0;
    for(int i=0;i<=up;i++){
        if(lt1&&lt2&&i==6) continue;
        ret+=dfs(pos-1,i==6,lt1,lim&&i==up);
    }
    if(!lim) f[pos][lt1][lt2]=ret;
    return ret;
}

ll solve(ll x){
    int len=0;
    while(x>0){
        a[++len]=x%10;
        x/=10;
    }
    return dfs(len,0,0,1);
}


int main(){
    memset(f,-1,sizeof(f));
    cin>>T;
    while(T--){
        int x;
        cin>>x;
        ll l=665,r=1e18;
        while(l+1<r){
            ll mid=(l+r)>>1;
            if(mid+1-solve(mid)<x){
                l=mid;
            }else r=mid;
        }
        cout<<l+1<<'\n';
    }
    return 0;
}