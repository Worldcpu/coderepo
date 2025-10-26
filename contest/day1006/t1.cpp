#include<bits/stdc++.h>
using namespace std;
int main(){
    int ret=0,n;
    cin>>n;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        if(ret>x) ret=x+1;
        else if(ret==x) ret++;
    }
    cout<<ret;

    return 0;
}