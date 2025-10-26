#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15;
int n,q;
map<int,vector<int>> mp;
map<pir,int> mpp;


signed main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        mp[x].push_back(i);
    }
    while(q--){
        int x,y;
        cin>>x>>y;
        if(x==y){
            int siz=mp[x].size();
            cout<<siz*(siz-1)/2<<'\n';
            continue;
        }
        if(mpp[pir(x,y)]){
            cout<<mpp[pir(x,y)]<<'\n';
            continue;
        }
        if(mp[x].size()<mp[y].size()){
            int ret=0;
            for(auto p:mp[x]){
                ret+=mp[y].end()-lower_bound(mp[y].begin(),mp[y].end(),p);
            }
            cout<<ret<<'\n';
            mpp[pir(x,y)]=ret;
        }else{
            int ret=0;
            for(auto p:mp[y]){
                ret+=lower_bound(mp[x].begin(),mp[x].end(),p)-mp[x].begin();
            }
            cout<<ret<<'\n';
            mpp[pir(x,y)]=ret;
        }
    }
    

    return 0;
}