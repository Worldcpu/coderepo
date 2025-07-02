#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int n,m,v,a[MN],b[MN],c[MN];
string s;

bool cmp(int x,int y){
    if(b[x]==b[y]) return b[x^v]<b[y^v];
    return b[x]<b[y];
}

int main(){
    cin>>n>>s;
    m=1<<n;
    for(int i=0;i<m;i++) a[i]=i,b[i]=s[i]-'a';
    sort(a,a+m,cmp);
    for(int i=1;i<=n;i++){
        v=(1<<(i-1));
        sort(a,a+m,cmp);
        int cnt=0;
        for(int j=0;j<m;j++){
            if(j==0||cmp(a[j-1],a[j])) c[a[j]]=++cnt; 
            else c[a[j]]=cnt;
        }
        for(int j=0;j<m;j++) b[j]=c[j];
    }
    for(int i=0;i<m;i++) cout<<s[i^a[0]];
}
