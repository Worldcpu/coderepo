#include<bits/stdc++.h>
using namespace std;
constexpr int MN=10;
int n,a[MN];
map<int,int> mp;

void dfs(int stp){
    if(stp>5) return;
    mp.clear();
    for(int i=1;i<=n;i++){
        mp[a[i]]++;
    }
    if(mp[a[1]]==n){
        return;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            for(int k=-10;k<=10;k++){
                if(a[i]>=k&&a[j]>=k){
                    a[i]+=k;
                    a[j]+=k;
                    dfs(stp+1);
                    a[i]-=k;
                    a[j]-=k;
                }
            }
        }
    }
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];       
    }
    dfs(0);
    for(int i=1;i<=n;i++){
        cout<<a[i]<<' ';
    }
    return 0;
}