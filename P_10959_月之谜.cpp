#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=150;
int a[MN];
int f[20][MN][MN][MN];

ll dfs(int pos,bool lim,int sum,ll num,ll P){
    if(!pos) return ((sum==P)&&(num==0));
    if(!lim&&~f[pos][sum][num][P]) return f[pos][sum][num][P];
    int up=lim?a[pos]:9;
    ll ret=0;
    for(int i=0;i<=up;i++){
        if(sum+i<=P){
            ret+=dfs(pos-1,lim&&(i==up),sum+i,(num*10+i)%P,P);
        }
    }
    if(!lim) f[pos][sum][num][P]=ret;
    return ret;
}

ll solve(int x){
    int len=0;
    while(x>0){
        a[++len]=x%10;
        x/=10;
    }
    ll ret=0;
    for(int i=9*len;i;i--){
        ret+=dfs(len,1,0,0,i);
    }
    return ret;
}

int main(){
    memset(f,-1,sizeof(f));
    int l,r;
    while(cin>>l>>r){
        cout<<solve(r)-solve(l-1)<<'\n';
    }
    return 0;
}