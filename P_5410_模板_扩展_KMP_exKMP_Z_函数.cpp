#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MN=2e7+15;
string s1,s2;
ll nxt[MN],ext[MN];
ll ans=0;

void qnxt(string s){
    int len=s.length(),p=0,k=1,l;
    nxt[0]=len;
    while(p+1<len&&s[p]==s[p+1])p++;
    nxt[1]=p;
    for(int i=2;i<len;i++){
        p=k+nxt[k]-1;
        l=nxt[i-k];
        if(i+l<=p){
            nxt[i]=l;
        }else{
            int j=max(0,p-i+1);
            while(i+j<len&&s[i+j]==s[j]) j++;
            nxt[i]=j;
            k=i;
        }
    }
}

void exkmp(string a,string b){
    int lena=a.length(),lenb=b.length();
    int p=0,k=0,l;
    while(p<lena&&p<lenb&&a[p]==b[p]){
        p++;
    }
    ext[0]=p;
    for(int i=1;i<lena;i++){
        p=k+ext[k]-1;
        l=nxt[i-k];
        if(i+l<=p) ext[i]=l;
        else{
            int j=max(0,p-i+1);
            while(i+j<lena&&j<lenb&&a[i+j]==b[j]){
                j++;
            }
            ext[i]=j;
            k=i;
        }
    }
}

int main(){
    cin>>s1>>s2;
    qnxt(s2);
    exkmp(s1,s2);
    for(int i=0;i<s2.length();i++){
        ans^=(i+1)*(nxt[i]+1);
    }
    cout<<ans<<'\n';
    ans=0;
    for(int i=0;i<s1.length();i++){
        ans^=(i+1)*(ext[i]+1);
    }
    cout<<ans;
    return 0;
}