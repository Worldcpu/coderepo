#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
string st;
map<char,int> mp;


int main(){
    cin>>st;
    for(auto c:st){
        mp[c]++;
    }
    for(auto p:mp){
        if(p.second==1) cout<<p.first;
    }


    return 0;
}