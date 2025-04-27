#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int n,x[MN],y[MN];
bool isa=1;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>x[i]>>y[i];
        if(i>1&&x[i]!=x[i-1]) isa=0;
    }
    if(isa){
        cout<<n;
        return 0;
    }
    
    return 0;
}