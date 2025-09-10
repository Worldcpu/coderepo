#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15;
int n;
pir pos[MN];
mt19937 mt;

int getrd(int l,int r){
    return mt()%(r-l+1)+l;
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>pos[i].first>>pos[i].second;
    }
    int T=5000;
    while(T--){
        int x=getrd(1,n),y=getrd(1,n);
        while(x==y){
            y=getrd(1,n);
        }
        int a=pos[y].second-pos[x].second,b=pos[x].first-pos[y].first,c=pos[y].first*pos[x].second-pos[x].first*pos[y].second;
        int cnt=0;
        for(int i=1;i<=n;i++){
            if(a*pos[i].first+b*pos[i].second+c==0){
                cnt++;
            }
        }
        if(cnt>n/2){
            cout<<"Yes\n";
            cout<<a<<' '<<b<<' '<<c<<'\n';
            return 0;
        }
    }
    cout<<"No\n";
    return 0;
}