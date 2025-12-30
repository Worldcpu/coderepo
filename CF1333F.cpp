#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n;

namespace Euler{
    int val[MN];
    vector<int> prime;
    bitset<MN> vis;

    void euler(int n){
        vis[0]=vis[1]=1;
        for(int i=2;i<=n;i++){
            if(!vis[i]){
                val[i]=1;
                prime.push_back(i);
            }
            for(auto p:prime){
                if(p*i>n) break;
                vis[i*p]=1;
                val[i*p]=i;
                if(i%p==0){
                    break;
                }
            }
        }
    }

}using namespace Euler;

int main(){
    cin>>n;
    euler(n);
    sort(val+1,val+1+n);
    for(int i=2;i<=n;i++) cout<<val[i]<<' ';
    return 0;
}