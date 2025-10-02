#include<bits/stdc++.h>
using namespace std;
constexpr int MN=15;
int n,a[MN];
set<int> s;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        s.insert(i);
    }
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(a[i]==-1) continue;
        if(!s.count(a[i])){
            cout<<"No";
            return 0;
        }else s.erase(a[i]);
    }
    cout<<"Yes\n";
    for(int i=1;i<=n;i++){
        if(a[i]==-1){
            cout<<(*s.begin())<<' ';
            s.erase(s.begin());
        }else cout<<a[i]<<' ';
    }

    return 0;
}