#include<bits/stdc++.h>
using namespace std;
constexpr int MN=4e5+15;
int n,a[MN],ans[MN];
string st;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    cin>>st;
    st=" "+st;

    sort(a+1,a+1+n);
    for(int l=1,r=n;l<=r;){
        int w=r-l+1;
        ans[w]=(st[w]==st[w-1]?l++:r--);
    }
    for(int i=1;i<=n;i++){
        cout<<a[ans[i]]<<' '<<(((ans[i]&1)^(n&1)^(st[n]=='R'))?'R':'L')<<'\n';
    }


    return 0;
}