#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e3+15;
int n,m,ans;
string st;
bitset<MN> bit[MN];

int gauss(int n,int m){
    int ans=-1;
    for(int i=1;i<=n;i++){
        int cur=i;
        while(cur<=m&&!bit[cur].test(i)){
            cur++;
        }
        if(cur>m) return 0;
        ans=max(ans,cur);
        if(cur!=i) swap(bit[cur],bit[i]);
        for(int j=1;j<=m;j++){
            if(i!=j&&bit[j].test(i)){
                bit[j]^=bit[i];
            }
        }
    }
    return ans;
}

int main(){
    cin>>n>>m;
    for(int i=1,x;i<=m;i++){
        cin>>st>>x;
        for(int j=0;j<n;j++) bit[i].set(j+1,st[j]=='1');
        bit[i].set(0,x);
    }
    if(ans=gauss(n,m)){
        cout<<ans<<'\n';
        for(int i=1;i<=n;i++){
            if(bit[i].test(0)){
                cout<<"?y7M#\n";
            }else cout<<"Earth\n";
        }
    }else cout<<"Cannot Determine";
    return 0;
}