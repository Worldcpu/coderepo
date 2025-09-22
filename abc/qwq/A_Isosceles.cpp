#include<bits/stdc++.h>
#define int long long
using namespace std;
int a,b,c;


signed main(){
    cin>>a>>b>>c;
    if(a!=b&&b!=c&&a!=c) cout<<"No\n";
    else if(a+b<=c||b+c<=a||a+c<=b) cout<<"No\n";
    else cout<<"Yes\n";
    return 0;
}