#include<bits/stdc++.h>
#define pir pair<int,int>
#define ull unsigned long long
using namespace std;
constexpr int MN=5e5+15;
constexpr ull base=13131;
int n,m,sum[MN];
string a,b;
ull hsha[MN],hshb[MN],trans[MN],pw[MN];
vector<pir> ans;

int checksum(int l,int r){
    return sum[r]-sum[l-1];
}

ull gethsha(int l,int r){
    if(l>r) return 0;
    return hsha[r]-hsha[l-1]*pw[r-l+1];
}

ull gethshb(int l,int r){
    if(l>r) return 0;
    return hshb[r]-hshb[l-1]*pw[r-l+1];
}

void initpw(){
    pw[0]=1;
    for(int i=1;i<MN;i++) pw[i]=pw[i-1]*base;
}

int main(){
    srand(time(0));
    cin>>a>>b;
    initpw();
    n=a.length(),m=b.length();
    a=" "+a,b=" "+b;
    if(a==b){
        cout<<1<<' '<<1;
        return 0;
    }
    for(int i=0;i<=9;i++){
        trans[i]=rand();
    }
    for(int i=1;i<=n;i++){
        hsha[i]=hsha[i-1]*base+trans[a[i]-'0'];
        sum[i]=sum[i-1]+(a[i]-'0');
    }
    for(int i=1;i<=m;i++){
        hshb[i]=hshb[i-1]*base+trans[b[i]-'0'];
    }
    for(int L=1;L<=m;L++){
        if(a[L-1]!=b[L-1]) break;
        for(int len=1;len<=6&&L+len-1<=m;len++){
            int R=L+len-1,nows=0;
            for(int j=L;j<=R;j++){
                nows=nows*10+(b[j]-'0');
            }
            int l=L,r=n,retmn=n,retmx=n;
            while(l<=r){
                int mid=(l+r)>>1;
                if(checksum(L,mid)>=nows) r=mid-1,retmn=mid;
                else l=mid+1;
            }
            l=L,r=n;
            while(l<=r){
                int mid=(l+r)>>1;
                if(checksum(L,mid)<=nows) l=mid+1,retmx=mid;
                else r=mid-1;
            }
            if(checksum(L,retmx)!=nows) continue;
            if(m-len>=n-(retmx-L+1)&&m-len<=n-(retmn-L+1)){
                int ll=n+L-1-(m-len);
                if(gethsha(ll+1,n)==gethshb(L+len,m)){
                    ans.push_back(pir(L,ll));
                }
            }
        }
    }
    assert(ans.size());
    sort(ans.begin(),ans.end());
    auto qwq=ans[ans.size()-1];
    cout<<qwq.first<<' '<<qwq.second;
    return 0;
}