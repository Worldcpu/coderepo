#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int p[MN],n,ans;
string s;

string change(string st){
    string s;
    s.push_back('$'),s.push_back('#');
    for(int i=0;i<st.length();i++){
        s.push_back(st[i]),s.push_back('#');
    }
    s.push_back('&');
    return s;
}

void manacher(string s){
    int r=0,c=0;
    for(int i=1;i<s.length();i++){
        if(i<r) p[i]=min(p[c*2-i],r-i);
        else p[i]=1;
        while(s[i+p[i]]==s[i-p[i]]){
            p[i]++;
        }
        if(p[i]+i>r){
            if(i&1){
                for(int j=max(r,i+4);j<i+p[i];j++){
                    if(!(j-i&1)&&p[i-(j-i)/2]>(j-i)/2) ans=max(ans,(j-i));
                }
            }
            r=p[i]+i;
            c=i;
        }
    }
}

int main(){
    cin>>n>>s;
    string afts=change(s);
    manacher(afts);
    cout<<ans*2;
    return 0;
}
