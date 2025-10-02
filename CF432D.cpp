#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int nxt[MN],n,f[MN];
set<int> vct;
string s;

void getnxt(){
    nxt[1]=0;
    for(int i=2,j=0;i<=n;i++){
        while(j&&s[j+1]!=s[i]) j=nxt[j];
        if(s[j+1]==s[i]) j++;
        nxt[i]=j;
    }
}

int main(){
    cin>>s;
    n=s.length();
    s=" "+s;
    getnxt();
    for(int i=nxt[n];i;i=nxt[i]){
        vct.insert(i);
    }   
    for(int i=n;i>=1;i--){
        f[i]++;
        f[nxt[i]]+=f[i];
    }
    cout<<vct.size()+1<<'\n';
    for(auto p:vct){
        cout<<p<<' '<<f[p]<<'\n';
    }
    cout<<n<<' '<<f[n];

    return 0;
}