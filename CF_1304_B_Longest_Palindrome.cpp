#include<bits/stdc++.h>
using namespace std;
int n,m;
map<string,int> mp;
string a,b,c;

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        string s,rs;
        cin>>s;
        rs=s;
        reverse(rs.begin(),rs.end());
        if(rs==s) b=s;
        else if(mp.find(rs)!=mp.end()){
            a+=s;
            c=rs+c;
            mp.erase(rs);
        }else mp[s]++;
    }
    cout<<a.size()+b.size()+c.size()<<'\n';
    cout<<a+b+c;
    return 0;
}
