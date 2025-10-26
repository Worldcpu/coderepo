
#include<bits/stdc++.h>
using namespace std;
int s,a,b,x,ans;

int main(){
    cin>>s>>a>>b>>x;
    while(x>0){
        if(x<a){
            ans+=s*x;
            break;
        }
        ans+=s*a;
        x-=a+b;
    }
    cout<<ans;


    return 0;
}