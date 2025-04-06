#include<bits/stdc++.h>
using namespace std;
const int MN=1e7+15;
struct trie{
    int son[26];
    int num;
    bool isend;
}t[MN];
int cnt=1;

void insert(string s){
    int now=0;
    for(int i=0;i<s.size();i++){
        int ch=s[i]-'a';
        if(!t[now].son[ch]){
            t[now].son[ch]=cnt++;
        }
        now=t[now].son[ch];
    }
    t[now].isend=1;
}

int main(){

    return 0;
}