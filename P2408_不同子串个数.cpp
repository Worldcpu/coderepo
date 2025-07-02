#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+!5;
int n,ans;
string s;

namespace SA{
    int len,sa[MN],x[MN],y[MN],rk[MN],c[MN],ht[MN],ST[30][MN];

    // 接受 string 和 vector_int 输入，其他输入不保证正确性
    // ST表需要手动初始化调用initst函数
    template<typename vct>
    void getsa(vct &s){
        int m=400000;
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
            ht[rk[i]]=ST[0][rk[i]]=k;
        }
    }
}using namespace SA;

int main(){
    cin>>n>>s;
    getsa(s);
    ans=n*(n+1)/2;
    for(int i=1;i<=n;i++){
        ans-=ht[rk[i]];
    }
    cout<<ans;
    return 0;
}
