#include<bits/stdc++.h>
using namespace std;
const int MN=2e6+15;
int n,a[MN],ans;
deque<int> q;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        a[i+n]=a[i];
    }
    for(int i=1;i<=2*n;i++){
        while (!q.empty()&&i-q.front()>n/2)
        {
            q.pop_front();
        }
        if(!q.empty()){
            ans=max(ans,a[i]+a[q.front()]+i-q.front());
        }
        while (!q.empty()&&a[q.back()]-q.back()<=a[i]-i)
        {
            q.pop_back();
        }
        q.push_back(i);
    }
    cout<<ans;
    return 0;
}