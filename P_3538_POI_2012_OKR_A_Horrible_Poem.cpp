#include<iostream>
#include<vector>
#include<algorithm>
#define endl '\n'
#include<cstring>
#define ull unsigned long long
using namespace std;
const int MN=2e5+15;
const ull base=123;
string s;
int cnt,q,l,r,n,zys[MN],num[MN];
vector<int> prime;
ull h[MN],pw[MN];
void initpw(){
    pw[0]=1;
    for(int i=1;i<=n;i++){
        pw[i]=pw[i-1]*base;
    }
}
ull geth(int l,int r){
    return h[r]-h[l-1]*pw[r-l+1];
}
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int main(){
    // ios::sync_with_stdio(0);
    n=read();
    cin>>s;
    q=read();
    initpw();
    for(int i=1;i<=s.size();i++){
        h[i]=h[i-1]*base+(ull)s[i-1];
    }
    for(int i=2;i<=n;i++){
        if(!zys[i]){
            prime.push_back(i);
            zys[i]=i;
        }
        for(int j=0;j<prime.size()&&i*prime[j]<=n;j++){
            zys[i*prime[j]]=prime[j];
            if(i%prime[j]==0) break;
        }
    }
    while (q--)
    {
        /* code */
        l=read(),r=read();
        cnt=0;
        int leng=r-l+1;
        while (leng>1)
        {
            /* code */
            num[++cnt]=zys[leng];
            leng/=zys[leng];
        }
        leng=r-l+1;
        int ans;
        for(int i=1;i<=cnt;i++){
            int ll=leng/num[i];
            if(geth(l,r-ll)==geth(l+ll,r)){
                leng=ll;
            }
        }
        cout<<leng<<endl;
    }
    
    return 0;
}