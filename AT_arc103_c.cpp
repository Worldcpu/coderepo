#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15;
int n,s[MN],top;
string st;
vector<pir> res;


int main(){
    cin>>st;
    n=st.length();
    st=" "+st;
    if(st[1]=='0'||st[n]=='1'){
        cout<<-1;
        return 0;
    }
    for(int i=1;i<n;i++){
        if(st[i]!=st[n-i]){
            cout<<-1;
            return 0;
        }
    }
    for(int i=1;i<n;i++){
        if(st[i]=='1'){
            for(int j=1;j<=top;j++){
                res.push_back(pir(i,s[j]));
            }
            s[top=1]=i;
        }else s[++top]=i;
    }
    res.push_back(pir(n,s[1]));
    for(auto p:res) cout<<p.first<<' '<<p.second<<'\n';

    return 0;
}