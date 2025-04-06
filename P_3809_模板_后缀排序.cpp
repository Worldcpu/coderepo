#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define ull unsigned long long
const int MN=1e6+16;
const ull base=13131,mod=11451419191;
ull h[MN],pw[MN];
int pos[MN],len;
string s;
void initpw(int len){
    pw[0]=1;
    for(int i=1;i<=len;i++){
        pw[i]=pw[i-1]*base;
    }
}
ull gethash(int l,int r){
    return h[r]-h[l-1]*pw[r-l+1];
}
bool cmp(int x,int y){
    int l=-1,r=min(len-x,len-y);
    while (l<r)
    {
        int mid=(l+r+1)>>1;
        ull h1=gethash(x,x+mid),h2=gethash(y,y+mid);
        if(h1==h2) l=mid;
        else r=mid-1;
    }
    if(l>min(len-x,len-y)) return x>y;
    else return s[x+l]<s[y+l];
}
int main(){
    cin>>s;
    len=s.length();
    initpw(s.length()+1);
    for(int i=1;i<=s.length();i++){
        h[i]=h[i-1]*base+(ull)s[i-1];
        pos[i]=i;
    }
    sort(pos+1,pos+1+len,cmp);
    for(int i=1;i<=len;i++){
        cout<<pos[i]<<" ";
    }
    return 0;
}