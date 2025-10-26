#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=520;
struct Node{
    int x,y,col;
}a[MN];
int n,cnt[3],ans=1e9;

// 0-> x 1-> y
unordered_map<int,set<pir>> mp[2];

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i].x>>a[i].y>>a[i].col;
        mp[0][a[i].x].insert(pir(a[i].y,a[i].col));
        mp[1][a[i].y].insert(pir(a[i].x,a[i].col));
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int x=a[i].x,y=a[i].y,xx=a[j].x,yy=a[j].y;
            if(x>xx) swap(x,xx);
            if(y>yy) swap(y,yy);
            for(int k=1;k<=n;k++){
                if(a[k].x)
            }
        }
    }

    return 0;
}