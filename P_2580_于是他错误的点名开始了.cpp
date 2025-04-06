#include<bits/stdc++.h>
using namespace std;
const int MN=26*1e5+15;
struct trie{
    bool repeat;
    int son[26];
    int num;
    bool isend;
}t[MN];

int cnt=1;
void insert(string s){
    int now=0;
    for(int i=0;i<s.size();i++){
        int ch=s[i]-'a';
        if(t[now].son[ch]==0){
            t[now].son[ch]=cnt++;
        }
        now=t[now].son[ch];
        t[now].num++;
    }
    t[now].isend=1;
}

int find(string s){
    int now=0;
    for(int i=0;i<s.size();i++){
        int ch=s[i]-'a';
        if(t[now].son[ch]==0) return 3;
        now=t[now].son[ch];
    }
    if(!t[now].isend) return 3;
    if(!t[now].num) return 3;
    if(t[now].repeat==0){
        t[now].repeat=1;
        return 1;
    }
    return 2;
}

int main(){
    int n;
    cin>>n;
    string s;
    while (n--)
    {
        cin>>s;
        insert(s);
    }
    cin>>n;
    while (n--)
    {
        cin>>s;
        int ret=find(s);
        if(ret==1) cout<<"OK\n";
        if(ret==2) cout<<"REPEAT\n";
        if(ret==3) cout<<"WRONG\n";
    }
    
    return 0;
}