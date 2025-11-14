#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n;

namespace Ji{
    deque<int> q;

    void solve(){
        for(int i=1;i<=n;i++){
            cout<<i<<' ';
            q.push_back(i);
        }
        cout<<'\n';
        for(int i=2;i<=n;i++){
            auto bk=q.back();
            q.pop_back();
            q.push_front(bk);
            for(auto p:q) cout<<p<<' ';
            cout<<'\n';
        }
        q.clear();
        for(int i=1;i<=n;i++){
            cout<<i<<' ';
            q.push_back(i);
        }
        cout<<'\n';
        for(int i=2;i<=n;i++){
            auto bk=q.back();
            q.pop_back();
            q.push_front(bk);
            for(auto p:q) cout<<p<<' ';
            cout<<'\n';
        }
    }

}

int main(){
    cin>>n;
    if(n&1) Ji::solve();

    return 0;
}