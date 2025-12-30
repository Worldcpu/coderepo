#include<bits/stdc++.h>
using namespace std;
constexpr int MN=(1<<20)-1;
int n,a[MN],tmp[MN],ans;

int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    if(*max_element(a,a+n)==0){
        cout<<0<<'\n';
        return 0;
    }
    for(int i=n;i>=1;i>>=1){
        for(int j=0;j<n;j++){
            tmp[j]=a[j];
        }
        for(int j=0;j<n;j++){
            a[j]^=(tmp[(j+i)%n]);
        }
        if(*max_element(a,a+n)!=0){
            ans+=i;
        }else{
            for(int j=0;j<n;j++) a[j]=tmp[j];
        }
    }
    cout<<ans+1;
    return 0;
}