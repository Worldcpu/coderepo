#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e6+15;
int n,ans,a[MN],b[MN],top,tot;
pir st[MN];

struct SA{
    int len,sa[MN],x[MN],y[MN],rk[MN],c[MN],ht[MN],ST[30][MN];

    // 接受 string 和 vector_int 输入，其他输入不保证正确性
    // ST表需要手动初始化调用initst函数
    template<typename vct>
    void getsa(vct s){
        int m=400000;
        len=s.size();
        s.insert(s.begin(),0);
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

int clac(int x,int y){
    return (x+y)*(y-x+1)/2;
}

signed main(){
    vector<int> s,t;
    cin>>n;
    --n;
    for(int i=0;i<=n;i++){
        cin>>a[i];
    }
    for(int i=n;i>=1;i--){
        a[i]-=a[i-1];
        b[++tot]=a[i];
    }
    sort(b+1,b+1+tot);
    tot=unique(b+1,b+1+tot)-b-1;
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(b+1,b+1+tot,a[i])-b;
        s.push_back(a[i]);
        t.push_back(a[i]);
    }
    A.getsa(s);
    reverse(t.begin(),t.end());
    B.getsa(t);
    A.initst();
    B.initst();
    cerr<<"QWQ\n";
    int sum=0;
    for(int i=n;i>=1;i--){
        ans+=sum;
        int now=1;
        while(top&&st[top].first>=A.ht[i]){
            sum-=st[top].first*st[top].second;
            now+=st[top--].second;
        }
        st[++top]=pir(A.ht[i],now);
        sum+=now*A.ht[i];
    }
    for(int k=1;k<n;k++){
        for(int i=1;i<=n/k-1;i++){
            int x1=i*k,y1=x1+k,x2=n-y1+2,y2=n-x1+2;
            int lcs=min(k-1,B.querylcp(x2,y2)),lcp=A.querylcp(x1,y1);
            if(lcs+lcp-k+1<0) continue;
            ans-=clac(max(lcp-k+1,0ll),lcs+lcp-k+1);
        }
    }
    cout<<ans+n*(n+1)/2;

    return 0;
}
