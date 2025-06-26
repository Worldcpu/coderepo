#include<bits/stdc++.h>
using namespace std;
constexpr int MN=22000005;
int p[MN],L[MN],R[MN],ans;
string s;

string change(string st){
    string s;
    s.push_back('#');
    s.push_back('$');
    for(int i=0;i<st.length();i++){
        s.push_back(st[i]);
        s.push_back('$');
    }
    s.push_back('&');
    return s;
}

void manacher(string s){
    int r=0,c;
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
        R[i+p[i]-1]=max(R[i+p[i]-1],p[i]-1);
        L[i-p[i]+1]=max(L[i-p[i]+1],p[i]-1);
    }
}

int main(){
    cin>>s;
    string afts=change(s);
    manacher(afts);
    int n=afts.length();
    for(int i=n-1;i>=1;i-=2) R[i]=max(R[i],R[i+2]-2);
    for(int i=1;i<=n;i+=2) L[i]=max(L[i],L[i-2]-2);
    for(int i=1;i<=n;i+=2) if(L[i]&&R[i]) ans=max(ans,L[i]+R[i]);
    cout<<ans;
    return 0;
}
