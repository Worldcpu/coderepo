#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e3+15;
int n;
set<int> st[MN],tmp[MN];

void doxor(int x,int y){
    for(auto p:tmp[y]){
        if(st[x].count(p)) st[x].erase(p);
        else st[x].insert(p);
    }
    if(st[x].count(y)) st[x].erase(y);
    else st[x].insert(y);
}

int main(){
    cin>>n;
    for(int i=0;i<n;i++){
    }
        for(int j=0;j<n;j++){
            cout<<"set "<<j<<" :{";
            for(auto p:st[j]) cout<<p<<' ';
            cout<<"}\n";
        }
        cout<<'\n';
    for(int i=1;i<=2*n;i++){
        cout<<"ROUND "<<i<<'\n';
        for(int j=0;j<n;j++){
            tmp[j]=st[j];
        }
        for(int j=0;j<n;j++){
            doxor(j,(j+1)%n);
        }
        for(int j=0;j<n;j++){
            cout<<"set "<<j<<" :{";
            for(auto p:st[j]) cout<<p<<' ';
            cout<<"}\n";
        }
        cout<<'\n';
    }
    
    return 0;
}