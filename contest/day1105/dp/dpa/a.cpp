#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,p[MN],d[MN],tmp[MN];
unordered_map<int,int> cnt;

int work(){
    int res=1e9;
    for(int st=0;st<(1<<n);st++){
        cnt.clear();
        for(int i=1;i<=n;i++){
            tmp[i]=p[i];
        }
        for(int i=1;i<=n;i++){
            if((st>>(i-1)&1)){
                tmp[i]=i;
                cnt[i]++;
            }else cnt[tmp[i]]++;
        }
        bool flag=1;
        for(int i=1;i<=n;i++){
            if(cnt[i]!=1){
                flag=0;
                break;
            }
        }
        if(flag){
            res=min(res,__builtin_popcount(st));
        }
    }
    return res;
}

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i];
    }
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        p[x]=0;
        cout<<work()<<' ';
    }
    cout<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}