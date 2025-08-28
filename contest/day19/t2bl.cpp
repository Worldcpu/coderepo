#include<bits/stdc++.h>
using namespace std;
constexpr int MN=3e5+15;
int n,a[MN],nxt[MN],pre[MN],ans[MN];
priority_queue<int,vector<int>,greater<int>> pq[MN];
vector<int> v;


int main(){
    cin>>n;
    v.push_back(0);
    for(int i=1;i<=n;i++){
        cin>>a[i];
        pq[a[i]].push(i);
        v.push_back(a[i]);
    }
    for(int i=2;i<n;i++){
        if(v[i]==v[i-1]){
            bool flag=0;
            for(int j=i+1;j<=n;j++){
                if(v[i]!=v[j]){
                    flag=1;
                    int val=v[j];
                    swap(v[i],v[j]);
                    break;
                }
            }
            if(!flag){
                cout<<-1;
                return 0;
            }
        }
    }
    if(v[n]==v[n-1]){
        int val=v[n];
        bool flag=0;
        for(int j=n-3;j>=0;j--){
            if(v[j]!=v[n-1]&&v[j+1]!=v[n-1]){
                v.pop_back();
                flag=1;
                v.insert(v.begin()+j+1,val);
                break;
            }
        }
        if(!flag){
            cout<<-1;
            return 0;
        }
    }
    for(int i=1;i<=n;i++){
        cout<<pq[v[i]].top()<<' ';
        pq[v[i]].pop();
    }


    return 0;
}