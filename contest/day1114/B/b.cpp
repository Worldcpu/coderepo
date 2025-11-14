#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e3+15;
int n,a[MN][MN];

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

namespace Ou{

    void solve(){
        for(int i=1,j=n;i<=n;i++,j--){
            a[j][i]=i;
        }
        for(int i=1,j=1,k=1;i<=n;i++){
            a[j][k]=k;
            j=(j==1?n:j-1);
            k++;
        }
        int tot=(n-2)/2;
        for(int i=2;i<=tot+1;i++){
            int num=i;
            for(int)
        }
    }

}

int main(){
    cin>>n;
    if(n&1) Ji::solve();
    else Ou::solve();

    return 0;
}