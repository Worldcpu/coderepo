#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=3e6+15,MOD=19930726;
int n,K,ans=1,p[MN],cnt[MN];
string s;

string change(string st){
    string s;
    s.push_back('$');
    s.push_back('#');
    for(int i=0;i<st.length();i++){
        s.push_back(st[i]);
        s.push_back('#');
    }
    s.push_back('&');
    return s;
}

void manacher(string s){
    int r=1,c=0;
    for(int i=1;i<s.length();i++){
        if(i<r) p[i]=min(p[2*c-i],r-i);
        else p[i]=1;
        while(s[i-p[i]]==s[i+p[i]]) p[i]++;
        if(i+p[i]>r){
            r=i+p[i];
            c=i;
        }
        if((p[i]-1)&1) cnt[p[i]-1]++;
    }
}

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

signed main(){
    cin>>n>>K>>s;
    string afts=change(s);
    manacher(afts);
    for(int i=n,sum=0;i>=1;i--){
        if(!(i&1)) continue;
        sum+=cnt[i];
        if(K>=sum){
            ans=(ans*ksm(i,sum))%MOD;
            K-=sum;
        }else{
            ans=(ans*ksm(i,K))%MOD;
            K=0;
            break;
        }
    }
    if(K>0) cout<<-1;
    else cout<<ans;
    return 0;
}
