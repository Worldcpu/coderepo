#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e7+15;
int n,p[MN];

string change(string st){
    string s;
    s.clear();
    s.push_back('$'),s.push_back('#');
    for(int i=0;i<st.length();i++){
        s.push_back(st[i]);
        s.push_back('#');
    }
    s.push_back('&');
    return s;
}

void manacher(string s){
    int r=0,c;
    for(int i=1;i<s.length();i++){
        if(i<r){
            p[i]=min(p[c*2-i],r-i);
        }
        while (s[i+p[i]+1]==s[i-p[i]-1])
        {
            p[i]++;
        }
        if(p[i]+i>r){
            r=p[i]+i;
            c=i;
        }
    }
}

int main(){
    cin>>n;
    while(n--){
        string s,afts;
        cin>>s;
        afts=change(s);
        manacher(afts);
        int ans=0;
        for(int i=0;i<afts.length();i++){
            ans=max(ans,p[i]);
        }
        cout<<ans<<'\n';
    }
    return 0;
}
