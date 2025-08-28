#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2000;
int a[MN],n,ret;


int main(){
    
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        a[i]--;
    }
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            for(int k=i;k<=j;k++){
                a[k]^=1;
            }
            int len=1;
            for(int k=2;k<=n;k++){
                if(a[k]==a[k-1]) len++;
                else{
                    if(a[k-1]==0) len++;
                    else len=1;
                }
                ret=max(ret,len);
            }            
            for(int k=i;k<=j;k++){
                a[k]^=1;
            }
        }
    }
    cout<<ret;
    return 0;
}