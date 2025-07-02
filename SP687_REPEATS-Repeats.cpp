#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e4+15;
int n;

struct SA{
    int len,sa[MN],x[MN],y[MN],rk[MN],c[MN],ht[MN],ST[30][MN];

    void clear(){
        memset(ST,0,sizeof(ST));
        memset(sa,0,sizeof(sa));
        memset(x,0,sizeof(x));
        memset(c,0,sizeof(c));
    }

    // 接受 string 和 vector_int 输入，其他输入不保证正确性
    // ST表需要手动初始化调用initst函数
    template<typename vct>
    void getsa(vct s){
        clear();
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

    // ST表初始化
    void initst(){
        for(int i=1;i<30;i++){
            for(int j=1;j+(1<<i)-1<=len;j++){
                ST[i][j]=min(ST[i-1][j],ST[i-1][j+(1<<(i-1))]);
            }
        }
    }

    // 查询位置为 i 和 位置为 j 的后缀的 LCP
    int querylcp(int i,int j){
        if((i=rk[i])>(j=rk[j])) swap(i,j);
        int d=__lg(j-(i++));
        return min(ST[d][i],ST[d][j-(1<<d)+1]);
    }

    // 手动查询 ST 表
    int queryst(int l,int r){
        int d=__lg(r-l+1);
        return min(ST[d][l],ST[d][r-(1<<d)+1]);
    }

}A,B;

void solve(){
    cin>>n;
    string str;
    for(int i=1;i<=n;i++){
        char x;
        cin>>x;
        str.push_back(x);
    }
    A.getsa(str);
    A.initst();
    reverse(str.begin(),str.end());
    B.getsa(str);
    B.initst();
    int ans=0;
    for(int len=1;len<=n;len++){
        for(int l=len,r=len+len;r<=n;l+=len,r+=len){
            int lcs=A.querylcp(l,r),lcp=B.querylcp(n-r+1,n-l+1);
            ans=max(ans,1ll*(lcs+lcp-1)/len+1);
        }
    }
    cout<<ans<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
