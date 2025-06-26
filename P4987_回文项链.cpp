
#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int p[MN],n,len,ans;
string s;


void manacher(string s){
    int r=0,c=0;
    for(int i=1;i<s.length();i++){
        if(i<r) p[i]=min(p[c*2-i],r-i);
        else p[i]=1;
        while(s[i+p[i]]==s[i-p[i]]){
            p[i]++;
        }
        if(p[i]+i>r){
            r=p[i]+i;
            c=i;
        }
    }
}

int main(){
    cin>>n>>len>>s;
    s=s+s+s;
    manacher(s);
    for(int i=n+1;i<=2*n;i++) 
        if((p[i]*2-1)>=len) ans++;
    cout<<ans;
    return 0;
}
