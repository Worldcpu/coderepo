#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15;
int n,pos[MN],ans[MN],w[MN];
vector<int> str;

namespace SA{
    int len,sa[MN],x[MN],y[MN],rk[MN],c[MN],ht[MN],st[30][MN];
    
    template<typename type>
    void getsa(type s){
        int m=400000,p=0;
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
            ht[rk[i]]=st[0][rk[i]]=k;
        }
    }

    void initst(){
        for(int i=1;i<30;i++){
            for(int j=1;j+(1<<i)-1<=len;j++){
                st[i][j]=min(st[i-1][j],st[i-1][j+(1<<(i-1))]);
            }
        }
    }

    int lcp(int i,int j){
        int d=__lg(j-(i++));
        return min(st[d][i],st[d][j-(1<<d)+1]);
    }

    int queryst(int l,int r){
        int d=__lg(r-l+1);
        return min(st[d][l],st[d][r-(1<<d)+1]);
    }

}using namespace SA;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        for(int j=str.size()+1;j<=str.size()+s.length();j++){
            pos[j]=i;
        }
        for(auto c:s) str.push_back(c);
        str.push_back('z'+i);
        ans[i]=s.length()*(s.length()+1)/2;  
    }
    str.pop_back();
    getsa(str);
    initst();
    for(int i=len,lst=0;i>=1;i--){
        if(pos[sa[i]]!=pos[sa[i+1]]){
            lst=i+1;
        }
        if(lst>i) w[i]=lcp(i,lst);
    }
    for(int i=1;i<=len;i++){
        ans[pos[sa[i]]]-=max(w[i],ht[i]);
    }
    for(int i=1;i<=n;i++) cout<<ans[i]<<'\n';
    return 0;
}
