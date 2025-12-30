#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e6+15;
int n,m;
string s1,s2;

namespace KMP{
    int nxt[MN];

    void initnxt(){
        nxt[1]=0;
        for(int i=2,j=0;i<=m;i++){
            while(j&&s2[j+1]!=s2[i]) j=nxt[j];
            if(s2[i]==s2[j+1]) j++;
            nxt[i]=j;
        }
    }

    void kmp(){
        for(int i=1,j=0;i<=n;i++){
            while(j>0&&s2[j+1]!=s1[i]) j=nxt[j]; 
            if(s2[j+1]==s1[i]) j++;
            if(j==m){
                cout<<i-j+1<<'\n';
                j=nxt[j];
            }
        }
    }

}

int main(){
    cin>>s1>>s2;
    n=s1.size(),m=s2.size();
    s1=" "+s1,s2=" "+s2;
    KMP::initnxt();
    KMP::kmp();
    for(int i=1;i<=m;i++){
        cout<<KMP::nxt[i]<<' ';
    }
    return 0;
}