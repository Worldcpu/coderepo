#include<bits/stdc++.h>
using namespace std;
constexpr int MN=520;
int n,s;
int t[MN];

int main(){
    cin>>n>>s;
    for(int i=1;i<=n;i++){
        cin>>t[i];
        if(t[i]-t[i-1]>s){
            cout<<"No";
            return 0;
        }
    }
    cout<<"Yes\n";

    return 0;
}