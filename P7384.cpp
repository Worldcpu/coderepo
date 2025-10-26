#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e7+15,MV=64;
int n,a[MN],val[MV],ans;
bool vis[MV];

signed main(){
    read(n);
    for(int i=1;i<=n;i++){
        read(a[i]);
        if(!a[i]){
            ans++;
            n--;
            i--;
            continue;
        }
        int qwq=__lg(a[i]);
        vis[qwq]=1;
        val[qwq]|=a[i];
    }
    for(int i=0;i<MV;i++){
        ans+=vis[i];
    }
    for(int i=MV-1;i>=0;i--){
        for(int j=i+1;j<MV;j++){
            if(val[i]&val[j]){
                ans--;
                val[i]|=val[j];
                break;
            }
        }
    }
    put(ans);

    return 0;
}