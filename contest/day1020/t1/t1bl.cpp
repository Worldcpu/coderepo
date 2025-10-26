#include<bits/stdc++.h>
using namespace std;
constexpr int MN=6;
int n,a[MN],K,r;

bool dfs(){
    bool flag=1;
    for(int i=1;i<=n;i++){
        if(a[i]>0){
            flag=0;
            break;
        }
        if(a[i]<0) return 0;
    }
    if(flag) return 1;

    for(int i=1;i<=n-K+1;i++){
        bool flag=1;
        for(int j=i;j<=i+K-1;j++){
            if(a[j]==0){
                flag=0;
                break;
            }
        }
        if(flag){
            for(int j=i;j<=i+K-1;j++){
                a[j]--;
            }
            if(dfs()) return 1;
            for(int j=i;j<=i+K-1;j++){
                a[j]++;
            }
        }
    }

    for(int i=1;i<=n;i++){
        if(a[i]>=r){
            a[i]-=r;
            if(dfs()) return 1;
            a[i]+=r;
        }
    }
    return 0;
}

int main(){
    cin>>n>>K>>r;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    cout<<(dfs()?"Yes\n":"No\n");   

    return 0;
}