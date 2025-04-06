#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int MN=1e6+15;
ull h[MN],a[MN],ans;
int n,m,u[MN],v[MN];

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        a[i]=(ull)rand()*rand()*rand();
    }
    for(int i=1;i<=m;i++){
        cin>>u[i]>>v[i];
        h[u[i]]+=a[v[i]];
        h[v[i]]+=a[u[i]];

    }
    for(int i=1;i<=m;i++){
        if(h[u[i]]-a[v[i]]==h[v[i]]-a[u[i]]) ans++;
    }

    sort(h+1,h+1+n);

    for(int i=1;i<=n;i++){
        int p=i;
        while(h[p]==h[p+1])p++;
        ans+=(ull)(p-i)*(p-i+1)/2;
        i=p;
    }
    cout<<ans;
    return 0;
}