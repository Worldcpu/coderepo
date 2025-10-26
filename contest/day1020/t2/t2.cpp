#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int h[MN],n,a,b,tot=1,ans;
priority_queue<int> q;

int main(){
    cin>>n>>a>>b;
    for(int i=1;i<=n;i++){
        cin>>h[i];
    }
    for(int i=1;i<=n;i++){
        int hh=(h[i]-1)/b,hr=h[i]%b;
        if(hr==0) hr=b;
        int stpa=(hr-1)/a+1;
        tot+=hh;
        if(tot>=stpa){
            tot-=stpa;
            ans++;
            q.push(stpa);
        }
        else if(!q.empty()&&q.top()>stpa){
            tot+=q.top()-stpa+1;
            q.pop();
            q.push(stpa);
        }else tot++;
    }
    cout<<ans;
    

    return 0;
}