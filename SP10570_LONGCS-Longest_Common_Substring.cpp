#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int T,K,ans,pos[MN],cnt[MN];
deque<int> q;

namespace SA{
    int len,sa[MN],x[MN],y[MN],rk[MN],c[MN],ht[MN];

    void clear(){
        memset(sa,0,sizeof(sa));
        memset(c,0,sizeof(c));
        memset(y,0,sizeof(y));
        memset(x,0,sizeof(x));
        memset(rk,0,sizeof(rk));
        memset(ht,0,sizeof(ht));
    }

    void getsa(string s){
        clear();
        int m=256;
        len=s.size();
        s.insert(s.begin(),' ');
        for(int i=1;i<=len;i++){
            x[i]=s[i];
            ++c[x[i]];
        }
        for(int i=2;i<=m;i++) c[i]+=c[i-1];
        for(int i=len;i>=1;i--) sa[c[x[i]]--]=i;
        for(int k=1;k<=len;k<<=1){
            int num=0;
            for(int i=len-k+1;i<=len;i++) y[++num]=i;
            for(int i=1;i<=len;i++){
                if(sa[i]>k) y[++num]=sa[i]-k;
            }
            for(int i=1;i<=m;i++) c[i]=0;
            for(int i=1;i<=len;i++) c[x[i]]++;
            for(int i=2;i<=m;i++) c[i]+=c[i-1];
            for(int i=len;i>=1;i--) sa[c[x[y[i]]]--]=y[i],y[i]=0;
            swap(x,y);
            num=1,x[sa[1]]=1;
            for(int i=2;i<=len;i++){
                if(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k]) x[sa[i]]=num;
                else x[sa[i]]=++num;
            }
            if(num==len) break;
            m=num;
        }
        for(int i=1;i<=len;i++) rk[sa[i]]=i;
        for(int i=1,k=0;i<=len;i++){
            if(rk[i]==1) continue;
            if(k) k--;
            int j=sa[rk[i]-1];
            while(i+k<=len&&j+k<=len&&s[i+k]==s[j+k]) k++;
            ht[rk[i]]=k;
        }
    }
}using namespace SA;

void solve(){
    cin>>K;
    string str="";
    memset(pos,0,sizeof(pos));
    for(int i=1;i<=K;i++){
        string s;
        cin>>s;
        for(auto c:s){
            str.push_back(c);
            pos[str.length()]=i;
        }
        if(i!=K) str.push_back('z'+i);
    }
    if(K==1){
        cout<<str.length()<<'\n';
        return;
    }
    getsa(str);
    memset(cnt,0,sizeof(cnt));
    ans=0;
    q.clear();
    for(int i=len-K+1,r=i,sum=0;i>=1;i--){
        if(pos[sa[i]]&&!cnt[pos[sa[i]]]++){
            sum++;
        }
        while(r>=i&&sum==K&&cnt[pos[sa[r]]]>1){
            --cnt[pos[sa[r]]];
            r--;
        }
        while(!q.empty()&&q.front()>r) q.pop_front();
        if(sum==K) ans=max(ans,ht[q.empty()?0:q.front()]);
        while(!q.empty()&&ht[q.back()]>ht[i]) q.pop_back();
        q.push_back(i);
    }
    cout<<ans<<'\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
