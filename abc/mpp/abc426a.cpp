
#include<bits/stdc++.h>
using namespace std;
map<string,int> mp;

void init(){
    mp["Ocelot"]=1;
    mp["Serval"]=2;
    mp["Lynx"]=3;
}

int main(){
    string x,y;
    cin>>x>>y;
    init();
    if(x==y||mp[x]>mp[y]) cout<<"Yes";
    else cout<<"No";

    return 0;
}