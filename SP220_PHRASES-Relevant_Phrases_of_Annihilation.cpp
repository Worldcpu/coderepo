#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e6+15;
int n,L[MN],R[MN];
string s;
vector<int> vct;

namespace SA{
    int len,sa[MN],rk[MN],ork[MN],buc[MN],id[MN],ht[MN],st[30][MN];

    void clear(){
        memset(sa,0,sizeof(sa));
        memset(rk,0,sizeof(rk));
        memset(ork,0,sizeof(ork));
        memset(buc,0,sizeof(buc));
        memset(id,0,sizeof(id));
        memset(ht,0,sizeof(ht));
        memset(st,0,sizeof(st));
    }

    void getsa(string s){
        clear();
        len=s.length();
        s=" "+s;
        int m=1<<7;
        for(int i=1;i<=len;i++) buc[rk[i]=s[i]]++;
        for(int i=1;i<=m;i++) buc[i]+=buc[i-1];
        for(int i=len;i>=1;i--) sa[buc[rk[i]]--]=i;
        for(int w=1,p=0;;m=p,p=0,w<<=1){
            for(int i=len-w+1;i<=len;i++) id[++p]=i;
            for(int i=1;i<=len;i++) if(sa[i]>w) id[++p]=sa[i]-w;
            memset(buc,0,sizeof(buc));
            memcpy(ork,rk,sizeof(rk));
            p=0;
            for(int i=1;i<=len;i++) buc[rk[id[i]]]++;
            for(int i=1;i<=m;i++) buc[i]+=buc[i-1];
            for(int i=len;i>=1;i--) sa[buc[rk[id[i]]]--]=id[i];
            for(int i=1;i<=len;i++) 
rk[sa[i]] = (ork[sa[i]] == ork[sa[i-1]] && ork[sa[i]+w] == ork[sa[i-1]+w]) ? p : ++p;
            if(p==len) break;
        }
        for(int i=1,k=0;i<=len;i++){
            if(k) k--;
            while(i+k<=len&&sa[rk[i]-1]+k<=len&&s[i+k]==s[sa[rk[i]-1]+k]) k++;
            ht[rk[i]]=k;
        }
    }
}using namespace SA;

bool check(int x){
    vct.clear();
    for(int i=1;i<=len;i++){
        if(ht[i]<x){
            bool flag=true;
            for(int j=1;j<=n;j++){
                int mn=MN,mx=0;
                for(int p:vct){
                    if(p<L[j]||p>R[j]) continue;
                    mn=min(mn,p);
                    mx=max(mx,p);
                }
                if(mx-mn<x){
                    flag=false;
                    break;
                }
            }
            if(flag) return true;
            vct.clear();
        }
        vct.push_back(sa[i]);
    }
    bool flag=true;
    for(int j=1;j<=n;j++){
        int mn=MN,mx=0;
        for(int p:vct){
            if(p<L[j]||p>R[j]) continue;
            mn=min(mn,p);
            mx=max(mx,p);
        }
        if(mx-mn<x){
            flag=false;
            break;
        }
    }
    return flag;
}

void solve(){
    cin>>n;
    s.clear();
    for(int i=1;i<=n;i++){
        string st;
        cin>>st;
        L[i]=s.length()+1;
        R[i]=s.length()+st.length();
        s+=st;
        s.push_back('#');    
    }
    getsa(s);
    int l=1,r=len,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)) ans=mid,l=mid+1;
        else r=mid-1;
    }
    cout<<ans<<'\n';
}

int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T;
    while(T--) solve();
    return 0;
}
