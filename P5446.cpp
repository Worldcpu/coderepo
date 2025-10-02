#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e7+15;
int p[MN],f[MN];
string st,qwqs;

namespace Manacher{
    void change(){
        qwqs.push_back('$');
        qwqs.push_back('#');
        for(int i=0;i<st.length();i++){
            qwqs.push_back(st[i]);
            qwqs.push_back('#');
        }
        qwqs.push_back('&');
    }

    void manacher(string st){
        int r=0,c;
        for(int i=0;i<st.length();i++) p[i]=0;
        for(int i=1;i<st.length();i++){
            if(i<r) p[i]=min(p[c*2-i],r-i);
            while(st[i+p[i]]==st[i-p[i]]){
                p[i]++;
            }
            if(p[i]+i>r){
                r=p[i]+i;
                c=i;
            }
        }
    }
}using namespace Manacher;

void init(){
    qwqs.clear();
    for(int i=1;i<=st.length();i++){
        f[i]=0;
    }
}

void solve(){
    cin>>st;   
    init();
    if(st.size()==1){
        cout<<1<<'\n';
        return;
    }
    change();
    manacher(qwqs);
    for(int i=st.length();i>=1;i--){
        int r=p[i*2]>>1;
        if(i+r-1==st.length()) f[i]=1;
        else if(i-r+1==1) f[i]=f[i*2-1];
        else f[i]=0;
    }
    for(int i=1;i<=st.length();i++){
        if(f[i]) cout<<i<<' ';
    }
    cout<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}