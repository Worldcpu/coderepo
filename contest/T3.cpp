#include<bits/stdc++.h>
using namespace std;
int n,q;
string T;

string dfs(string s){
    if(s.length()==2) return s;
    int len=s.length()/3,cnt[2]{};
    string tmp;
    for(int i=1;i<=len;i++){
        cnt[0]=cnt[1]=0;
        cnt[s[3*i-2]-'A']++;
        cnt[s[3*i-1]-'A']++;
        cnt[s[3*i]-'A']++;
        tmp.push_back((cnt[0]>cnt[1]?'A':'B'));
    }
    tmp=" "+tmp;
    return dfs(tmp);
}

int main(){
    cin>>n>>q>>T;
    T=" "+T;
    for(int i=1;i<=q;i++){
        int pos;
        cin>>pos;
        T[pos]=(T[pos]=='A'?'B':'A');
        //cout<<"AFT:"<<T<<'\n';
        cout<<dfs(T)[1]<<'\n';
    }
    return 0;
}