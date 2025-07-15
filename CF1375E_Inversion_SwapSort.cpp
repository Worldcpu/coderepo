#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e6+15;
int n,a[MN],b[MN];
vector<pir> op;

bool cmp(int x,int y){
    if(a[x]==a[y]) return x<y;
    return a[x]<a[y];
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        b[i]=i;
    }
    sort(b+1,b+1+n,cmp);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n-1;j++){
            if(b[j]>b[j+1]){
                op.push_back(pir(b[j+1],b[j]));
                swap(b[j+1],b[j]);
            }
        }
    }
    cout<<op.size()<<'\n';
    for(auto p:op) cout<<p.first<<" "<<p.second<<'\n';
    return 0;
}
