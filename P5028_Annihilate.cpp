#include<bits/stdc++.h>
using namespace std;
constexpr int MN=3e6+15,MK=55;
int n,pos[MN],minn[MK],ans[MK][MK];
vector<int> str;

namespace SA{
    int len,sa[MN],x[MN],y[MN],rk[MN],c[MN],ht[MN];

    void getsa(vector<int> s){
        int m=40000,p=0;
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

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        for(auto c:s){
            str.push_back(c);
            pos[str.size()]=i;
        }
        str.push_back(1000+i);
    }
    getsa(str);
    for(int i=2;i<=len;i++){
        for(int j=1;j<=n;j++) minn[j]=min(minn[j],ht[i]);
        minn[pos[sa[i-1]]]=ht[i];
        for(int j=1;j<=n;j++){
            ans[pos[sa[i]]][j]=ans[j][pos[sa[i]]]=max(ans[pos[sa[i]]][j],minn[j]);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i!=j) cout<<ans[i][j]<<" ";
        }
        cout<<'\n';
    }
    return 0;
}
