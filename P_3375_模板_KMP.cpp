#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
vector<int> pre;
string s1,s2;
void getpre(string s){
    int len=s.length();
    pre.resize(len);
    for(int i=1;i<len;i++){
        int j=pre[i-1];
        while (j>0&&s[i]!=s[j])
        {
            j=pre[j-1];
        }
        if(s[i]==s[j])j++;
        pre[i]=j;
    }
}
void kmp(string s1,string s2){
    int i=0,j=0;
    while (i<s1.size())
    {
        if(j==s2.length()){
            cout<<i-j+1<<endl;
            j=pre[j-1];
        }else if(j==-1||s1[i]==s2[j]){
            i++;
            j++;
        }else if(j==0){
            i++;
        }
        else j=pre[j-1];
    }
    if(j==s2.length()){
        cout<<i-j+1<<endl;
    }
}
int main(){
    cin>>s1>>s2;
    getpre(s2);
    kmp(s1,s2);
    for(int i=0;i<pre.size();i++){
        cout<<pre[i]<<" ";
    }
    return 0;
}