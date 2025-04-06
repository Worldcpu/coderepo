#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int MN=1145,MT=26*21*1001;
struct trie{
    int son[26];
    int num;
    bool isend;
}t[MT];
int tot,cnt=1;
string st[MN],ans[MN];

void insert(string s,int pos){
    int now=0;
    for(int i=0;i<s.size();i++){
        int ch=s[i]-'a';
        if(!t[now].son[ch]){
            t[now].son[ch]=cnt++;
        }
        now=t[now].son[ch];
        t[now].num++;
        if(i==s.size()-1){
            t[now].isend=1;
        }
    }
}

void find(string s,int pos){
    int now=0,i;
    string mpre;
    for(i=0;i<s.size();i++){
        int ch=s[i]-'a';
        now=t[now].son[ch];
        if(t[now].num==1){
            break;
        }
    }
    if(i>=s.length()){
        ans[pos]=s;
        return;
    }
    for(int j=0;j<=i;j++){
        mpre.push_back(s[j]);
    }
    ans[pos]=mpre;
}

int main(){
    //  freopen("ans.in","r",stdin);
    while (cin>>st[++tot])
    {
        // 
    }
    tot--;
    for(int i=1;i<=tot;i++){
        insert(st[i],i);
    }
    for(int i=1;i<=tot;i++){
        find(st[i],i);
        cout<<st[i]<<" "<<ans[i]<<'\n';
    }
    return 0;
}