#include<iostream>
#include<queue>
using namespace std;
const int MN=1e4+15;
int n,tmax,a[MN];
bool check(int k){
    priority_queue<int,vector<int>,greater<int>> q;
    for(int i=1;i<=k;i++){
        q.push(a[i]);
    }
    for(int i=k+1;i<=n;i++){
        int f=q.top();
        q.pop();
        q.push(f+a[i]);
    }
    int t;
    while (!q.empty()){
        t=q.top();
        q.pop();
    }
    return t<=tmax;
}
int main(){
    cin>>n>>tmax;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    int l=0,r=n,ret;
    while (l<r)
    {
        int mid=l+r>>1;
        if(check(mid)){
            ret=mid;
            r=mid;
        }else l=mid+1;
    }
    cout<<ret;
    return 0;
}